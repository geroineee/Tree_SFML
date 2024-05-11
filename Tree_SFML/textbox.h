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
			Text(sf::String, float, float); //�����������, ������ �������� - ��������� ������, ������ - ������� x, ������ - ������� y
				sf::Text get(); //���������� ����� sf::Text, ������� ����� ����������
			void setText(sf::String); //��������� ������
			void setPosition(float, float); //������� ������
			void setSize(unsigned int); //������ ������
		};
		TextBox(); //�����������
		TextBox(float, float, float, float, float); //������ ��� ��������� ������ ������, ������ ��� - ���������, � ��������� - �������
			void draw(sf::RenderWindow&); //���������
		void handleEvent(sf::Event&); //������������ ���� ������
		sf::String getCurrentText(); //������� ��, ��� � ��������� ����
	public:
		void setSize(float, float); //������ ���� ���������� - ������ �������� ��� x, ������ ��� y
		void setPosition(float, float); //������ ������� (x,y)
		void setBorder(float); //������ ������� �������
	private:
		Text inpText;
	};
}
