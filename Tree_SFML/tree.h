#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <cmath>
#include <stdlib.h>

#include <iomanip>
#include <sstream>

#include <functional>

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

    // конструктор создания дерева из элементов вектора
    Tree(const std::vector<double>& values);

    // геттеры и сеттеры приватных полей
    void setFontSize(int font_size) { this->font_size = font_size; }
    void setShiftX(float shift_x) { this->shift_x = shift_x; }
    void setShiftY(float shift_y) { this->shift_y = shift_y; }
    void setNodeRadius(int node_radius) { this->node_radius = node_radius; }

    int getFontSize() { return this->font_size; }
    float getShiftX() { return this->shift_x; }
    float getShiftY() { return this->shift_y; }
    int getNodeRadius() { return this->node_radius; }

    void setLeft(Tree* left) { this->left = left; }
    void setRight(Tree* right) { this->right = right; }
    void setParent(Tree* parent) { this->parent = parent; }
    void setData(double data) { this->data = data; }

    Tree* getLeft() { return this->left; }
    Tree* getRight() { return this->right; }
    Tree* getParent() { return this->parent; }
    double getData() { return this->data; }

    Vector2f getPosition() { return this->position; }
    void setPosition(Vector2f position) { this->position = position; }

    // вычисление высоты дерева
    int find_height();

    // вычисление максимальной длины вправо | влево от данного узла
    int find_left_lenght(int level);
    int find_right_lenght(int level);

    // вставка значения в дерево
    void insert(double value);

    // окно с проходами по дереву
    void showTraversals();

    //  Прямой обход (NLR)
    void NLR(std::vector<double>* vect);
    // симметричный обход (LNR)
    void LNR(std::vector<double>* vect);
    // обратный обход (LRN)
    void LRN(std::vector<double>* vect);

    // нахождение количества узлов дерева
    int getNodesCnt();

    // отрисовка дерева
    void draw(const std::wstring title, bool isHorosontal = false);
};

// Отрисовка дерева
void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level, bool isHorisontal);
