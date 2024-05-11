#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "textbox.h"
#include "button.h"


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
    int height = 1;
    double data;

    Vector2f position;

public:
    Tree();
    Tree(double value);
    ~Tree();

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
    int getHeight()
    {
        if (this == nullptr) return 0;
        return this->height;
    }

    void setLeft(Tree* left) { this->left = left; }
    void setRight(Tree* right) { this->right = right; }
    void setParent(Tree* parent) { this->parent = parent; }
    void setData(double data) { this->data = data; }
    void setHeight(int height) { this->height = height; }

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

    //
    void delete_tree();

    // отрисовка дерева
    void draw(const std::wstring title, bool isHorosontal = false);

    int getBalance() {
        int leftHeight = (left ? left->height : 0);
        int rightHeight = (right ? right->height : 0);
        return leftHeight - rightHeight;
    }

    void updateHeight() {
        int leftHeight = (left ? left->height : 0);
        int rightHeight = (right ? right->height : 0);
        height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    Tree* rotateLeft() {
        Tree* newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        parent = newRoot;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    Tree* rotateRight() {
        Tree* newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        parent = newRoot;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    Tree* balance()
    {
        int balanceFactor = getBalance();
        if (balanceFactor > 1) {
            if (left && left->getBalance() < 0) {
                left = left->rotateLeft();
            }
            return rotateRight();
        }
        if (balanceFactor < -1) {
            if (right && right->getBalance() > 0) {
                right = right->rotateRight();
            }
            return rotateLeft();
        }
        return this;
    }

    void addNode();

};

// Отрисовка дерева
void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level, bool isHorisontal);


// сбалансированнное добавлние элемента 
Tree* insertNode(Tree* root, double data);


// окно добавления
std::string getDataWindow(std::wstring mes);