#include "tree.h"

Tree::Tree() {}

Tree::Tree(double value)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    data = value;
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

Tree* Tree::createTree(const std::vector<double>& values)
{
    if (values.empty()) {
        return nullptr;
    }

    Tree* root = new Tree(values[0]);

    for (size_t i = 1; i < values.size(); i++) {
        root->insert(values[i]);
    }

    return root;
}

void drawTree(sf::RenderWindow& window, Tree* node, int x, int y, int level)
{
    if (node == nullptr)
        return;

    int radius = 30; // Размер окружности узла

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

    // Рекурсивный вызов для левого и правого потомка
    if (node->left != nullptr) {
        drawTree(window, node->left, x - shift_x * level, y + shift_y, level - 1);
    }

    if (node->right != nullptr) {
        drawTree(window, node->right, x + shift_x * level, y + shift_y, level - 1);
    }
}