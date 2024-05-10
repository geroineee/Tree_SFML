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

//статус кнопки
void RectButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
	this->mousePosWindow = sf::Mouse::getPosition(window);//позиция мыши в окне
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);
	this->isHover = false; // наведение курсора
	this->isPressed = false; // нажатие кнопки

	// если кнопка активна
	if (isActive)
	{
		if (button.getGlobalBounds().contains(this->mousePosView)) //курсор наведен
		{
			this->isHover = true;
		}

		if (button.getGlobalBounds().contains(this->mousePosView)) // после 1 нажатия кнопки
		{
			this->isPressed = true; // изменение состояния нажатия кнопки
		}

		if (isHover) // при наведении курсора
		{
			button.setFillColor(defaultPressed); 
		}
		else button.setFillColor(defaultHovered); 
		
		if (isPressed) //кнопка нажата
		{
			button.setFillColor(defaultPressed); 
		}
	}
	else //обычный цвет 
	{
		button.setFillColor(defaultPressed);
	}
}
void RectButton::draw(sf::RenderWindow& window) { //отображаю кнопку в окне
	window.draw(button);//кнопка
	window.draw(buttonLabel);//надпись
}
void RectButton::setButtonLable(std::wstring label, const sf::Color& color, float charSize) // изменение надписи
{
	this->buttonLabel.setString(label); // надпись
	this->buttonLabel.setCharacterSize(charSize);//размер символов
	this->buttonLabel.setFillColor(color);//устанавливаю цвет
	this->buttonLabel.setOutlineThickness(1);
	this->label = label;//присваиваю надпись
	this->labelRect = this->buttonLabel.getLocalBounds();
	this->buttonLabel.setOrigin(this->labelRect.width / 2.0f, this->labelRect.height / 1.2f);//ставлю координаты
	this->buttonLabel.setPosition(this->buttonPos.x + (this->buttonRect.width / 2.0f),//ставлю координаты
	this->buttonPos.y + (this->buttonRect.height / 4.0f) + 7);
}

void Button::setButtonFont(sf::Font& font)
{
	buttonLabel.setFont(font);
}
