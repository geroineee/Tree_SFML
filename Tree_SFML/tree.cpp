#include "tree.h"
#include <cmath>


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
    sf::Text text(std::to_string(node->getData()), font);
    text.setCharacterSize(font_size);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(x - 30, y - 20);

    if (node->getParent() != nullptr)
    {
        drawLine(window, node->getNodeRadius(), node->getParent()->getPosition(), node->getPosition());
    }
    window.draw(circle);
    window.draw(text);
    

    // Рекурсивные вызовы для левого и правого потомка узла
    if (node->getLeft() != nullptr)
    {
        drawTree(window, node->getLeft(), x - shift_x * level, y + shift_y, level - 1);
    }

    if (node->getRight() != nullptr)
    {
        drawTree(window, node->getRight(), x + shift_x * level, y + shift_y, level - 1);
    }
}