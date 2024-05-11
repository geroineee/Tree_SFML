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
    int font_size = 20; // ������ ������ ������� �������� ����
    float shift_x = 20; // �������� �� x ��� ���������� ����
    float shift_y = 60; // �������� �� y ��� ���������� ����
    int node_radius = 20; // ������ ���������� ����

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

    // ����������� �������� ������ �� ��������� �������
    Tree(const std::vector<double>& values);
    
    // ������� � ������� ��������� �����
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

    // ���������� ������ ������
    int find_height();

    // ���������� ������������ ����� ������ | ����� �� ������� ����
    int find_left_lenght(int level);
    int find_right_lenght(int level);

    // ������� �������� � ������
    void insert(double value);

    // ���� � ��������� �� ������
    void showTraversals();

    //  ������ ����� (NLR)
    void NLR(std::vector<double>* vect);
    // ������������ ����� (LNR)
    void LNR(std::vector<double>* vect);
    // �������� ����� (LRN)
    void LRN(std::vector<double>* vect);

    // ���������� ���������� ����� ������
    int getNodesCnt();

    //
    void delete_tree();

    // ��������� ������
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

// ��������� ������
void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level, bool isHorisontal);


// ����������������� ��������� �������� 
Tree* insertNode(Tree* root, double data);


// ���� ����������
std::string getDataWindow(std::wstring mes);