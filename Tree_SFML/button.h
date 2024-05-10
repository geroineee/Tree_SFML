#pragma once

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const sf::Color defaultHovered = sf::Color(145, 145, 145); // цвет кнопки по умолчанию
const sf::Color defaultPressed = sf::Color(100, 100, 100); // цвет кнопки при нажатии

class Button
{
public:
	virtual void getButtonStatus(sf::RenderWindow&, sf::Event&) = 0; //статус кнопки
	virtual void draw(sf::RenderWindow&) = 0; //отображение кнопки
	virtual void setButtonFont(sf::Font&); //шрифт текста на кнопке
	virtual void setButtonLable(std::wstring, const sf::Color&, float) = 0; //установка надписи на кнопке
	bool isHover = false; // наведения курсора
	bool isPressed = false; // нажатия кнопки
	bool isActive = true; // доступность для нажатия
	 
protected:
	sf::Text buttonLabel; // надпись на кнопке
	sf::Vector2i mousePosWindow; // позиция мыши
	sf::Vector2f buttonPos; // позиция кнопки
	std::wstring label;//надпись

	sf::Vector2f mousePosView; // ------------------------------------------------------------------------------------------------------------------
	sf::FloatRect labelRect; // --------------------------------------------------------------------------------------------------------------------

};

class RectButton : public Button // подкласс прямоугольных кнопок
{
public:
	RectButton(const sf::Vector2f = sf::Vector2f(0, 0));
	RectButton(const sf::Vector2f = sf::Vector2f(0, 0), const sf::Vector2f = sf::Vector2f(0, 0));
	~RectButton();

	void getButtonStatus(sf::RenderWindow&, sf::Event&); // получение статуса нажатия кнопки
	void draw(sf::RenderWindow&); // отрисовка кнопки
	void setButtonLable(std::wstring, const sf::Color&, float); // отрисовка надписи
	sf::RectangleShape button;
	 
private:
	sf::FloatRect buttonRect;
};

#endif