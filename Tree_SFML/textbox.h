#include<SFML/Graphics.hpp>

namespace sdx {
	class TextBox {
	private:
		sf::RectangleShape outerRect;
		sf::RectangleShape innerRect;
		sf::RectangleShape blinker;
		sf::String getPinp;
		sf::String txtInp;
		sf::Clock clock;
		sf::Time time;
		unsigned int textSize;
		unsigned int focusChar;
		float charWidth;
		float thickness;
		float posX;
		float posY;
		float height;
		float width;
		bool focus;
	public:
		class Text {
		private:
			sf::Font font;
			sf::Text text;
		public:
			Text(sf::String, float, float); //конструктор, первый параметр - текстовая строка, второй - позиция x, третий - позиция y
				sf::Text get(); //возвращает класс sf::Text, который можно отрисовать
			void setText(sf::String); //установка текста
			void setPosition(float, float); //позиция текста
			void setSize(unsigned int); //размер текста
		};
		TextBox(); //конструктор
		TextBox(float, float, float, float, float); //первые два параметра задают размер, вторые два - положение, а последний - толщину
			void draw(sf::RenderWindow&); //отрисовка
		void handleEvent(sf::Event&); //обрабатывает ввод текста
		sf::String getCurrentText(); //получаю то, что в текстовом поле
	public:
		void setSize(float, float); //размер окна обновления - первый параметр для x, второй для y
		void setPosition(float, float); //ставлю позицию (x,y)
		void setBorder(float); //ставлю толщину границы
	private:
		Text inpText;
	};
}
