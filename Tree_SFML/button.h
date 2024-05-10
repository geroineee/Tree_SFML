#pragma once

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const sf::Color defaultHovered = sf::Color(145, 145, 145); // ���� ������ �� ���������
const sf::Color defaultPressed = sf::Color(100, 100, 100); // ���� ������ ��� �������

class Button
{
public:
	virtual void getButtonStatus(sf::RenderWindow&, sf::Event&) = 0; //������ ������
	virtual void draw(sf::RenderWindow&) = 0; //����������� ������
	virtual void setButtonFont(sf::Font&); //����� ������ �� ������
	virtual void setButtonLable(std::wstring, const sf::Color&, float) = 0; //��������� ������� �� ������
	bool isHover = false; // ��������� �������
	bool isPressed = false; // ������� ������
	bool isActive = true; // ����������� ��� �������
	 
protected:
	sf::Text buttonLabel; // ������� �� ������
	sf::Vector2i mousePosWindow; // ������� ����
	sf::Vector2f buttonPos; // ������� ������
	std::wstring label;//�������

	sf::Vector2f mousePosView; // ------------------------------------------------------------------------------------------------------------------
	sf::FloatRect labelRect; // --------------------------------------------------------------------------------------------------------------------

};

class RectButton : public Button // �������� ������������� ������
{
public:
	RectButton(const sf::Vector2f = sf::Vector2f(0, 0));
	RectButton(const sf::Vector2f = sf::Vector2f(0, 0), const sf::Vector2f = sf::Vector2f(0, 0));
	~RectButton();

	void getButtonStatus(sf::RenderWindow&, sf::Event&); // ��������� ������� ������� ������
	void draw(sf::RenderWindow&); // ��������� ������
	void setButtonLable(std::wstring, const sf::Color&, float); // ��������� �������
	sf::RectangleShape button;
	 
private:
	sf::FloatRect buttonRect;
};

#endif