#pragma once
#include <SFML/Graphics.hpp>


class Button
{
public:
	class OtherButtonSettnings
	{
	public:
		OtherButtonSettnings(sf::RectangleShape base, sf::Text& text, sf::RectangleShape hover, sf::Vector2f ScreenPos)
			:
			base(base),
			text(text),
			hover(hover),
			ScreenPos(ScreenPos)
		{}

		sf::RectangleShape base;
		sf::Text text;
		sf::RectangleShape hover;
		sf::Vector2f ScreenPos;
	};
	static OtherButtonSettnings GetNormalButton(sf::Font& font, sf::String stringi, sf::Vector2f Position)
	{
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(35);
		text.setPosition(Position.x + 5, Position.y - 15);
		text.setFillColor(sf::Color::Black);
		text.setString(stringi);
		sf::Vector2f ButtonSize = { text.getLocalBounds().width - text.getLocalBounds().left + 10, text.getLocalBounds().height - text.getLocalBounds().top + 10 };
		sf::RectangleShape hover;
		hover.setSize(ButtonSize);
		hover.setFillColor(sf::Color(167, 167, 167));
		hover.setOutlineColor(sf::Color(60, 60, 60));
		hover.setOutlineThickness(2);

		sf::RectangleShape base;
		base.setSize(ButtonSize);
		base.setFillColor(sf::Color(200, 200, 200));
		base.setOutlineColor(sf::Color(60, 60, 60));
		base.setOutlineThickness(4);

		return OtherButtonSettnings{ base,text,hover,Position };
	}
public:
	Button(OtherButtonSettnings& settnings, void(&ClickFunct)(Button& button))
		:
		base(settnings.base),
		text(settnings.text),
		hover(settnings.hover),
		pos(settnings.ScreenPos),
		ClickFunct(ClickFunct)
	{
		base.setPosition(pos);
		hover.setPosition(pos);
	}
	void Draw(sf::RenderWindow& win)
	{
		if (Mousehover)
		{
			win.draw(hover);
		}
		else
		{
			win.draw(base);
		}
		win.draw(text);
	}
	void ChangeString(sf::String newS)
	{
		text.setString(newS);
		sf::Vector2f ButtonSize = { text.getLocalBounds().width - text.getLocalBounds().left + 10, text.getLocalBounds().height - text.getLocalBounds().top + 10 };
		base.setSize(ButtonSize);
		hover.setSize(ButtonSize);
	}
	sf::String GetString()
	{
		return text.getString();
	}
	void Update(sf::RenderWindow& win, sf::Vector2f mousepos)
	{
		if (base.getGlobalBounds().contains(mousepos))
		{
			Mousehover = false;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (mouseinhib)
				{
					ClickFunct(*this);
					mouseinhib = false;
				}
			}
			else
			{
				mouseinhib = true;
			}
		}
		else
		{
			Mousehover = true;
		}
	}
private:
	sf::RectangleShape base;
	sf::RectangleShape hover;
	sf::Text text;
	sf::Vector2f pos;
	bool Mousehover;
	void(&ClickFunct)(Button& Button);
	bool mouseinhib = false;
};