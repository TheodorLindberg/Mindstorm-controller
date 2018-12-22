#include <iostream>
#include "JoyStickStearing.h"
#include <SFML/Graphics.hpp>
#include "Radar.h"
#include "Button.h"
#include <conio.h>
int ShowMessageBox();
void ChangeValue(int value);
int GetValue();
bool IsConnected();
void Disconnect();
void Connect(int port);
void SendMessageN(char* title, float value);
void SendMessageT(char* title, char* value);
void SendMessageL(char* title, bool value);

bool Coneccted = false;

bool ButtonChange = false;
void Hello(Button& button)
{
	ButtonChange = true;
	if (IsConnected())
	{
		Disconnect();
		std::cout << "Disconnected" << std::endl;
	}
	else
	{
		Connect(6);
		Coneccted = true;
		std::cout << "Connected" << std::endl;
		SendMessageT("TextMailbox", "Connected");
		std::cout << IsConnected() << std::endl;
	}
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 480), "Awesome Game");

	sf::Font font;
	if (!font.loadFromFile("FontFile.ttf"))
	{
		std::cout << "Error loading file" << std::endl;

		system("pause");
	}
	JoytickStearing JoyStick(font);
	Radar radar(font);
	Button button(Button::GetNormalButton(font, sf::String("Connect"), { 900,50 }), *Hello);
	sf::Text text;
	text.setFont(font);
	while (window.isOpen())
	{
		sf::Event event;

		int scroll = 0;

		// handle all events
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

				break;
			case sf::Event::MouseWheelScrolled:
				scroll = event.mouseWheelScroll.delta;
				break;
			}
		}
		
		/*if (_kbhit)
		{
			char c = _getch();
			switch (c)
			{
			case 'q':
				SendMessageN("Dir", 0);
				SendMessageN("Power", 0);
				Disconnect();

				return EXIT_SUCCESS;
				break;
			default:
				break;
			}
		}*/
		if (ButtonChange)
		{
			ButtonChange = false;
			if (IsConnected())
			{
				button.ChangeString("Disconnect");
			}
			else
			{
				button.ChangeString("Connect");
			}


		}

		if (Coneccted)
		{
			JoyStick.Update(Vector2i(window.mapPixelToCoords(Vector2i(Mouse::getPosition(window)))), scroll, window);
			radar.Update(window, window.mapPixelToCoords(Vector2i(Mouse::getPosition(window))));
		}
		
			button.Update(window, window.mapPixelToCoords(Vector2i(Mouse::getPosition(window))));
		
		if (IsConnected())
		{
			window.clear(Color::Green);
		}
		else
		{
			window.clear(Color::Red);
		}
		if (Coneccted)
		{
			JoyStick.Draw(window, text);
			radar.Draw(window);
		}
			button.Draw(window);
		
		window.display();
	}

	SendMessageN("Dir", 0);
	SendMessageN("Power", 0);
	Disconnect();
	return EXIT_SUCCESS;
}






