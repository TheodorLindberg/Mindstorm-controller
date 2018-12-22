#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#define JoyStickSter 0x1;
#define MousePasSter 0x2;

void SendMessageN(char* title, float value);

using namespace sf;

void Invert(float& number)
{
	if (number > 0)
	{
		number = -number;
	}
	else
	{
		number = number - number - number;
	}
}
namespace DONT
{
	bool s = false;
}
void ChangeTypeFunc(Button& button)
{
	DONT::s = true;
}

class JoytickStearing
{
private:
	class MainJoyStick
	{
	public:
		MainJoyStick(Font& font)
		{
			ChangeType = new Button{ Button::GetNormalButton(font,sf::String("Mouse Pad"),sf::Vector2f{50,50}),*::ChangeTypeFunc };
			rad = 20;
			BG = RectangleShape{ sf::Vector2f(200 + rad * 2, 200 + rad * 2) };
			BG.move(StartX - rad, StartY - rad);
			BG.setFillColor(Color(196, 196, 196));
			BG.setOutlineColor(sf::Color(88, 88, 88));
			BG.setOutlineThickness(3);
			button = CircleShape{ float(rad), 20 };
			button.setFillColor(sf::Color::Blue);
			button.setOutlineColor(sf::Color::Black);

			button.setPosition(200 - rad, 200 - rad);
		}
		~MainJoyStick()
		{
			delete ChangeType;
			ChangeType = nullptr;
		}
		void ChangeTypeFunc()
		{
			DONT::s = false;
			if (Type == 2)
			{
				if (Joystick::isConnected(0))
				{
					ChangeType->ChangeString("Change To MousePad");
					Type = 1;
				}
				else
				{
					ChangeType->ChangeString("MousePad");
				}
			}
			else if (Type == 1)
			{
				if (Joystick::isConnected(0))
				{
					ChangeType->ChangeString("Change to JoyStick");
					Type = 2;
				}
			}
		}
		void Update(Vector2i MousePos, int ScrollSinceLastFrame,RenderWindow& window)
		{
			if (DONT::s)
			{
				ChangeTypeFunc();
			}

			ChangeType->Update(window, Vector2f( MousePos));
			float cdir = 0;
			float cpow = 0;
			if(Type == 1)
			{
				if (Joystick::isConnected(0))
				{
					cdir = Joystick::getAxisPosition(0, sf::Joystick::Z);
					cpow = Joystick::getAxisPosition(0, sf::Joystick::Y);

				}
				else
				{
					Type = 2;
				}
			}
			else if (Type == 2)
			{
				if (Joystick::isConnected(0) && ChangeType->GetString() != sf::String("Mouse Pad"))
				{
					ChangeType->ChangeString("Change to JoyStick");
				}
				bool LeftPressed = false;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (leftinhib)
					{
						LeftPressed = true;
						leftinhib = false;
					}
				}
				else
				{
					leftinhib = true;
				}
				bool StudpiMadeProgram = true;

				if (!marked)
				{
					if (LeftPressed)
					{
						if (IntRect{ 80,80,240,420 }.contains(MousePos))
						{
							marked = true;
							StudpiMadeProgram = false;
						}
					}
				}
				if (marked)
				{
					if (LeftPressed && StudpiMadeProgram)
					{
						marked = false;
						ResetPos();
						marked = false;
						return;
					}
					cdir = MousePos.x - 200;
					cpow = MousePos.y - 200;
				}
			}
			KeepwidingRange(cdir, -100, 100);
			KeepwidingRange(cpow, -100, 100);

			int x = cdir + 200 - rad;
			button.setPosition(x, cpow + 200 - rad);


			Invert(cdir);
			Invert(cpow);

			if (cdir != dir)
			{
				 dir = cdir;
				SendMessageN("Dir", dir);
				msgs += 1;
			}
			if (cpow != power)
			{
				power=cpow;
				SendMessageN("Power", power);
				msgs += 1;
			}
		}
		void Draw(sf::RenderWindow& window, Text& text)
		{
			window.draw(BG);
			window.draw(button);

			ChangeType->Draw(window);

			text.setCharacterSize(50);

			text.setPosition(350, 80);
			text.setString(sf::String("Power"));
			window.draw(text);

			text.setPosition(350, 400);
			text.setString(std::to_string(msgs));
			window.draw(text);

			text.setPosition(350, 110);
			text.setString(sf::String(std::to_string(int(power))));
			window.draw(text);

			text.setPosition(80, 10);
			text.setString(sf::String("R -- to reset pos   F -- to reset dir"));
			window.draw(text);

			text.setPosition(350, 140);
			text.setString(sf::String("Direction"));
			window.draw(text);

			text.setPosition(350, 170);
			text.setString(sf::String(std::to_string(int(dir))));
			window.draw(text);
		}
	private:


		void ResetPos()
		{

			button.setPosition(200 - rad, 200 - rad);
			power = 0;
			dir = 0;
			SendMessageN("Dir", dir);
			SendMessageN("Power", power);
			msgs += 2;
		}
		void KeepwidingRange(float& variabal, float min, float max)
		{
			if (variabal < min)
			{
				variabal = min;
			}
			else if (variabal > max)
			{
				variabal = max;
			}
		}
		float times =0; 
		RectangleShape BG;
		CircleShape button;
		Button* ChangeType;
		Clock c;
		int rad;

		int Type = 2;
		
		int StartX = 100;
		int StartY = 100;

		float dir = 0;
		float power = 0;
		bool marked = false;


		int msgs = 0;
		bool leftinhib;
	};
public:
	JoytickStearing(Font& font)
		:
		mjs(font)
	{

	}
	void Update(Vector2i MousePos,int ScrollSinceLastFrame, RenderWindow& window)
	{
		mjs.Update(MousePos,ScrollSinceLastFrame,window);
	}
	void Draw(sf::RenderWindow& window, Text& text)
	{
		mjs.Draw(window,text);
	}
private:
	MainJoyStick mjs;
	
};