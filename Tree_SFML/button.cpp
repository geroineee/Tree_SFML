#include "button.h"

RectButton::RectButton(const sf::Vector2f size)
{
	this->button.setSize(size);
	this->buttonRect = this->button.getLocalBounds();
}

RectButton::RectButton(const sf::Vector2f size, const sf::Vector2f position)
{
	this->button.setSize(size);
	this->button.setOutlineThickness(1);
	this->button.setOutlineColor(sf::Color::Black);
	this->button.setPosition(position);
	this->buttonPos = position;
	this->buttonRect = this->button.getLocalBounds();
}
RectButton::~RectButton() {}

//������ ������
void RectButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
	this->mousePosWindow = sf::Mouse::getPosition(window);//������� ���� � ����
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);
	this->isHover = false; // ��������� �������
	this->isPressed = false; // ������� ������

	// ���� ������ �������
	if (isActive)
	{
		if (button.getGlobalBounds().contains(this->mousePosView)) //������ �������
		{
			this->isHover = true;
		}

		if (button.getGlobalBounds().contains(this->mousePosView)) // ����� 1 ������� ������
		{
			this->isPressed = true; // ��������� ��������� ������� ������
		}

		if (isHover) // ��� ��������� �������
		{
			button.setFillColor(defaultPressed); 
		}
		else button.setFillColor(defaultHovered); 
		
		if (isPressed) //������ ������
		{
			button.setFillColor(defaultPressed); 
		}
	}
	else //������� ���� 
	{
		button.setFillColor(defaultPressed);
	}
}
void RectButton::draw(sf::RenderWindow& window) { //��������� ������ � ����
	window.draw(button);//������
	window.draw(buttonLabel);//�������
}
void RectButton::setButtonLable(std::wstring label, const sf::Color& color, float charSize) // ��������� �������
{
	this->buttonLabel.setString(label); // �������
	this->buttonLabel.setCharacterSize(charSize);//������ ��������
	this->buttonLabel.setFillColor(color);//������������ ����
	this->buttonLabel.setOutlineThickness(1);
	this->label = label;//���������� �������
	this->labelRect = this->buttonLabel.getLocalBounds();
	this->buttonLabel.setOrigin(this->labelRect.width / 2.0f, this->labelRect.height / 1.2f);//������ ����������
	this->buttonLabel.setPosition(this->buttonPos.x + (this->buttonRect.width / 2.0f),//������ ����������
	this->buttonPos.y + (this->buttonRect.height / 4.0f) + 7);
}

void Button::setButtonFont(sf::Font& font)
{
	buttonLabel.setFont(font);
}
