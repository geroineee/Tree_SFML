#include "tree.h"
#include "button.h"
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <sstream>


Tree::Tree() {}

Tree::Tree(double value)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    data = value;
}

Tree::Tree(const std::vector<double>& values)
{
    if (values.empty()) { return; }

    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = values[0];

    for (size_t i = 1; i < values.size(); i++) 
    {
        this->insert(values[i]);
    }
}

int Tree::find_height()
{
    int height_left = 0, height_right = 0;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
        height_left = this->left->find_height();
    if (this->right != nullptr)
        height_right = this->right->find_height();
    return std::max(height_right, height_left)+1;
}

int Tree::find_left_lenght(int level)
{
    int lenght_left = 0, lenght_right = lenght_left;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
    {
        lenght_left += shift_x * level * 1.5;
        lenght_left += this->left->find_left_lenght(level - 1);
    }
    if (this->right != nullptr)
    {
        lenght_right -= shift_x * level * 1.5;
        lenght_right += this->right->find_left_lenght(level - 1);
    }
    return std::max(lenght_left, lenght_right);
}

int Tree::find_right_lenght(int level)
{
    int lenght_right = 0, lenght_left = lenght_right;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
    {
        lenght_left -= shift_x * level * 1.5;
        lenght_left += this->left->find_right_lenght(level - 1);
    }
    if (this->right != nullptr)
    {
        lenght_right += shift_x * level * 1.5;
        lenght_right += this->right->find_right_lenght(level - 1);
    }
    return std::max(lenght_left, lenght_right);
}

void Tree::insert(double value)
{
    if (value < data) 
    {
        if (left == nullptr) 
        {
            left = new Tree(value);
            left->parent = this;
        }
        else 
        {
            left->insert(value);
        }
    }
    else 
    {
        if (right == nullptr) 
        {
            right = new Tree(value);
            right->parent = this;
        }
        else 
        {
            right->insert(value);
        }
    }
}

void Tree::draw(const std::wstring title)
{
    int height = this->find_height();
    int lenght_left = this->find_left_lenght(height);
    int lenght_right = this->find_right_lenght(height);
    float window_width = 100 + lenght_left + lenght_right;
    float window_height = 150 + this->node_radius * 2 + shift_y * (height - 1);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), title);
    window.setActive(true);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("gta.ttf");

    RectButton button_back({150, 40}, {window_width/2 - 75, window_height - 70});
    button_back.setButtonFont(font);
    button_back.setButtonLable(L"Назад", sf::Color::White, 30);

    while (window.isOpen())
    {
        sf::Event event;

        button_back.getButtonStatus(window, event);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (button_back.isPressed == true)
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        button_back.draw(window);
        drawTree(window, this, 50+lenght_left, 50, height); // отрисовка дерева

        window.display();
    }
}

void drawLine(sf::RenderWindow& window, int radius, Vector2f pos_parent, Vector2f pos_node)
{
    float x1 = pos_parent.x, y1 = pos_parent.y+radius, x2 = pos_node.x, y2 = pos_node.y-radius;
    RectangleShape rect({1, sqrt(pow(x1-x2, 2) + pow(y2-y1, 2))});

    rect.setFillColor(Color(0, 0, 0));
    rect.setPosition({ x1, y1 });
    float angle;
    if (x1 < x2)
        angle = -90 - 57.2958 * asin((y2 - y1) / (x1 - x2));
    else
        angle = 90 - 57.2958 * asin((y2 - y1) / (x1 - x2));
    rect.setRotation(angle);

    window.draw(rect);
}

void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level)
{
    if (node == nullptr) return;

    int radius = node->getNodeRadius();
    int shift_x = node->getShiftX();
    int shift_y = node->getShiftY();
    int font_size = node->getFontSize();
    Vector2f position(x - radius, y - radius);

    node->setPosition({x, y});

    // Отображение узла как окружности
    sf::CircleShape circle(radius);
    circle.setPosition(position);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);

    // Отображение значения узла внутри окружности
    sf::Font font;
    font.loadFromFile("gta.ttf"); // шрифт

    // Форматирование значения узла
    std::ostringstream buf;
    buf << std::fixed << std::setprecision(1) << node->getData();

    sf::Text text(buf.str(), font);
    text.setCharacterSize(font_size);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(x - (font_size/2.5 * buf.str().size()/2) + 1 + (buf.str().size()), y - (font_size * 0.75) + 1);

    if (node->getParent() != nullptr)
    {
        drawLine(window, node->getNodeRadius(), node->getParent()->getPosition(), node->getPosition());
    }
    window.draw(circle);
    window.draw(text);
    

    // Рекурсивные вызовы для левого и правого потомка узла
    if (node->getLeft() != nullptr)
    {
        drawTree(window, node->getLeft(), x - shift_x * level * 1.5, y + shift_y, level - 1);
    }

    if (node->getRight() != nullptr)
    {
        drawTree(window, node->getRight(), x + shift_x * level * 1.5, y + shift_y, level - 1);
    }
}