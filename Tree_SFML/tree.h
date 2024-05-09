#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

int font_size = 20;
int shift_x = 40;
int shift_y = 60;

class Tree
{
public:
    Tree* left;
    Tree* right;
    Tree* parent;
    double data;

    Tree();

    Tree(double value);

    void insert(double value);

    static Tree* createTree(const std::vector<double>& values);
};


// Отрисовка дерева
void drawTree(sf::RenderWindow& window, Tree* node, int x, int y, int level);
