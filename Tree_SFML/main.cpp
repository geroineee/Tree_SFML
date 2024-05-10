#include "tree.h"
#include "button.h" 
#include <iostream>

#define TREE_SIZE 15

std::vector<double> tree_rand(int size);

/*
int main()
{
    srand(time(0));

    // Анти-алиасинг
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Создание и инициализация вашего дерева
    std::vector<double> values = tree_rand(7);

    Tree* tree = new Tree(values);

    // Создание SFML окна 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");
    window.setVerticalSyncEnabled(true);
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.display();
    }
    return 0;
}*/


int main()
{
    srand(time(0));
    sf::Font font;
    font.loadFromFile("gta.ttf");

    // Анти-алиасинг
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Создание и инициализация дерева
    std::vector<double> values = tree_rand(TREE_SIZE);
    Tree* tree = new Tree(values);

    // Создание окна SFML
    sf::RenderWindow window(sf::VideoMode(540, 320), L"Меню");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    RectButton button_vertical_print({ 400, 40 }, { 70, 50 });
    button_vertical_print.setButtonFont(font);
    button_vertical_print.setButtonLable(L"Вертикальная печать", sf::Color::White, 30);

    RectButton button_horizontal_print({ 400, 40 }, { 70, 100 });
    button_horizontal_print.setButtonFont(font);
    button_horizontal_print.setButtonLable(L"Горизонтальная печать", sf::Color::White, 30);

    RectButton button_tree_traversal({ 400, 40 }, { 70, 150 });
    button_tree_traversal.setButtonFont(font);
    button_tree_traversal.setButtonLable(L"Обходы дерева", sf::Color::White, 30);

    RectButton button_add_node({ 400, 40 }, { 70, 200 });
    button_add_node.setButtonFont(font);
    button_add_node.setButtonLable(L"Добавить узел", sf::Color::White, 30);

    RectButton button_delete_node({ 400, 40 }, { 70, 250 });
    button_delete_node.setButtonFont(font);
    button_delete_node.setButtonLable(L"Удалить узел", sf::Color::White, 30);


    while (window.isOpen())
    {
        sf::Event event;

        button_vertical_print.getButtonStatus(window, event);
        button_horizontal_print.getButtonStatus(window, event);
        button_tree_traversal.getButtonStatus(window, event);
        button_add_node.getButtonStatus(window, event);
        button_delete_node.getButtonStatus(window, event);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (button_vertical_print.isPressed)
                    {
                        tree->draw(L"Вертикальная печать");
                    }
                    if (button_horizontal_print.isPressed)
                    {
                        tree->draw(L"Горизонтальная печать", true);
                    }
                    if (button_tree_traversal.isPressed)
                    {
                        tree->showTraversals();
                    }
                }
            }
        }
        window.clear(sf::Color::White);

        button_vertical_print.draw(window);
        button_horizontal_print.draw(window);
        button_tree_traversal.draw(window);
        button_add_node.draw(window);
        button_delete_node.draw(window);

        window.display();
    }
    return 0;
}

std::vector<double> tree_rand(int size)
{
    std::vector<double> vect;
    for (int i = 0; i < size; i++)
    {
        double element = rand() % 100;
        vect.push_back(element / 10.0);
    }
    return vect;
}