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
    int font_size = 20; // ������ ������ ������� �������� ����
    float shift_x = 20; // �������� �� x ��� ���������� ����
    float shift_y = 60; // �������� �� y ��� ���������� ����
    int node_radius = 20; // ������ ���������� ����

    Tree* left;
    Tree* right;
    Tree* parent;
    double data;

    Vector2f position;

public:
    Tree();
    Tree(double value);

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

    // ��������� ������
    void draw(const std::wstring title, bool isHorosontal = false);
};

// ��������� ������
void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level, bool isHorisontal);
