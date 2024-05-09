#include "tree.h"



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

    for (size_t i = 1; i < values.size(); i++) {
        this->insert(values[i]);
    }
}

void Tree::insert(double value)
{
    if (value < data) {
        if (left == nullptr) {
            left = new Tree(value);
            left->parent = this;
        }
        else {
            left->insert(value);
        }
    }
    else {
        if (right == nullptr) {
            right = new Tree(value);
            right->parent = this;
        }
        else {
            right->insert(value);
        }
    }
}



void drawTree(sf::RenderWindow& window, Tree* node, int x, int y, int level)
{
    if (node == nullptr) return;

    int radius = node->getNodeRadius();
    int shift_x = node->getShiftX();
    int shift_y = node->getShiftY();
    int font_size = node->getFontSize();

    // Отображение узла как окружности
    sf::CircleShape circle(radius);
    circle.setPosition(x - radius, y - radius);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    window.draw(circle);

    // Отображение значения узла внутри окружности
    sf::Font font;
    font.loadFromFile("gta.ttf"); // Замените "arial.ttf" на путь к вашему шрифту
    sf::Text text(std::to_string(node->data), font);
    text.setCharacterSize(font_size);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(x - 30, y - 20);
    window.draw(text);

    // Рекурсивные вызовы для левого и правого потомка узла
    if (node->left != nullptr)
    {
        drawTree(window, node->left, x - shift_x * level, y + shift_y, level - 1);
    }

    if (node->right != nullptr)
    {
        drawTree(window, node->right, x + shift_x * level, y + shift_y, level - 1);
    }
}