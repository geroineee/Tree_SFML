#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;



class Tree
{
private:
    int font_size = 20; // ������ ������ ������� �������� ����
    int shift_x = 40; // �������� �� x ��� ���������� ����
    int shift_y = 60; // �������� �� y ��� ���������� ����
    int node_radius = 30; // ������ ���������� ����

public:
    Tree* left;
    Tree* right;
    Tree* parent;
    double data;

    Tree();
    Tree(double value);
    // �������� ������ �� ��������� �������
    Tree(const std::vector<double>& values);

    int getFontSize() { return font_size; }
    int getShiftX() { return shift_x; }
    int getShiftY() { return shift_y; }
    int getNodeRadius() { return node_radius; }

    int setFontSize(int font_size) { this->font_size = font_size; }
    /*
    int setShiftX() { return shift_x; }
    int setShiftY() { return shift_y; }
    int setNodeRadius() { return node_radius; }
    */

    // ������� �������� � ������
    void insert(double value);


    friend void drawTree(sf::RenderWindow& window, Tree* node, int x, int y, int level);
};


// ��������� ������
void drawTree(sf::RenderWindow& window, Tree* node, int x, int y, int level);
