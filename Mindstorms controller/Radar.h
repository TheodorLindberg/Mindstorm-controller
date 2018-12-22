#pragma once
#include <SFML/Graphics.hpp>
#include "EV3Messages.h"
using namespace sf;

void SendMessageL(char* title, bool value);
bool RadarOn = false;
bool RadarChange = false;
void OnOffFunc(Button& button)
{
	RadarChange = true;
	if (RadarOn)
	{
		SendMessageL("RadarOnOff", false);
		button.ChangeString("Turn on radar");
		RadarOn = false;
	}
	else
	{
		SendMessageL("RadarOnOff", true);
		button.ChangeString("Turn off radar");
		RadarOn = true;
	}
}
class Radar
{
public:
	Radar(Font& font)
		:
		OnOff(Button::GetNormalButton(font,sf::String("Turn on radar"),sf::Vector2f{ 500,50 }),*OnOffFunc)
	{
		for each(char& s in radar)
		{
			s = 100;
		}
	}
	void Draw(RenderWindow& window)
	{
		float width = 1;

		RectangleShape gre;
		gre.setFillColor(Color::Green);
		gre.setPosition(650, 300);
		RectangleShape obj({ 200,width });
		obj.setFillColor(Color::Red);
		obj.setPosition(650, 300);

		for (int i = 0; i < 180; i++)
		{
			char s = radar[i];
			if (s != 100)
			{
				obj.setRotation(-i);
				window.draw(obj);
			}
			gre.setSize({ float(s) * 2,width });
			gre.setRotation(-i);
			window.draw(gre);
		}
		gre.setFillColor(Color::Blue);
		gre.setRotation(CurSweepDeg);
		gre.setSize({ 200,3 });
		window.draw(gre);
		OnOff.Draw(window);
	}
	void Update(RenderWindow& window, sf::Vector2f mousepos)
	{
		OnOff.Update(window, mousepos);
		if (RadarChange)
		{
			if (!RadarOn)
			{
				CurSweepDeg = 0;

				for each(char& s in radar)
				{
					s = 100;
				}
			}
		}
		if (RadarOn)
		{
			messenger.UpdateNewMessages();
			std::vector<EV3Messages::TextMessage> emessages = messenger.GetTitleMessagesText(string("Radar"));
			for (int i = 0; i < emessages.size(); i++)
			{
				string text = emessages[i].text;
				char dis[2] = { text[0], text[1] };
				char Dis = char(stoi(string(dis)));
				if (Dis == 99)
				{
					Dis = 100;
				}
				int deg = GetDeg(text);
				deg = 180 - deg;
				if (deg > 0 && deg < 180)
				{
					radar[deg] = Dis;
					for (int f = deg; f < LastID; f++)
					{
						radar[f] = Dis;
					}
					LastID = deg;
				}
			}
			if (emessages.size() > 0)
			{
				string text = emessages[emessages.size() - 1].text;
				CurSweepDeg = 180 - -GetDeg(text);
			}
		}
	}
private:
	int GetDeg(string msg)
	{
		int num=0;
		string s;
		for (int i = 2; i < msg.size(); i++)
		{
			s += msg[i];
		}
		
		return stoi(s);
	}
	int LastID = 0;
	float CurSweepDeg = 0;
	char radar[180];
	EV3Messages messenger;
	Button OnOff;
};