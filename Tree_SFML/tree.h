#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;


class Tree
{
private:
    int font_size = 20; // размер шрифта надписи значения узла
    float shift_x = 20; // смещение по x для следующего узла
    float shift_y = 60; // смещение по y для следующего узла
    int node_radius = 20; // размер окружности узла
    
    Tree* left;
    Tree* right;
    Tree* parent;
    double data;

    Vector2f position;

public:
    Tree();
    Tree(double value);
    // создания дерева из элементов вектора
    Tree(const std::vector<double>& values);

    int getFontSize() { return this->font_size; }
    float getShiftX() { return this->shift_x; }
    float getShiftY() { return this->shift_y; }
    int getNodeRadius() { return this->node_radius; }

    void setFontSize(int font_size) { this->font_size = font_size; }
    void setShiftX(float shift_x) { this->shift_x = shift_x; }
    void setShiftY(float shift_y) { this->shift_y = shift_y; }
    void setNodeRadius(int node_radius) { this->node_radius = node_radius; }

    Tree* getLeft() { return this->left; }
    Tree* getRight() { return this->right; }
    Tree* getParent() { return this->parent; }
    double getData() { return this->data; }

    void setLeft(Tree* left) { this->left = left; }
    void setRight(Tree* right) { this->right = right; }
    void setParent(Tree* parent) { this->parent = parent; }
    void setData(double data) { this->data = data; }

    Vector2f getPosition() { return this->position; }
    void setPosition(Vector2f position) { this->position = position; }

    int find_height();
    int find_left_lenght(int level);
    int find_right_lenght();

    // вставка значения в дерево
    void insert(double value);

    void draw(const std::wstring title);
};


// Отрисовка дерева
void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level);
