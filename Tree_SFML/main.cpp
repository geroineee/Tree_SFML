#include "tree.h"
#include "button.h" 
#include <iostream>

#define TREE_SIZE 10

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
    sf::RenderWindow window(sf::VideoMode(540, 700), L"Меню");

    // Установление иконки
    sf::Image icon;
    icon.loadFromFile("tree_icon.png");
    window.setIcon(512, 512, icon.getPixelsPtr());

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    CircleShape circle(40);
    circle.setPosition({230, 480});
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    
    Text text_eyes(L"0.0", font, 60);
    text_eyes.setFillColor(sf::Color::White);
    text_eyes.setOutlineColor(Color::Black);
    text_eyes.setOutlineThickness(1);
    text_eyes.setPosition({ circle.getPosition().x - 10, circle.getPosition().y - 10 });
    
    sf::Clock clock;
    float move_interval = 0.1f;

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

    RectButton button_balanced_tree({ 400, 40 }, { 70, 300 });
    button_balanced_tree.setButtonFont(font);
    button_balanced_tree.setButtonLable(L"Сбалансированное дерево", sf::Color::White, 30);

    RectButton button_find_element({ 400, 40 }, { 70, 350 });
    button_find_element.setButtonFont(font);
    button_find_element.setButtonLable(L"Найти элемент", sf::Color::White, 30);

    RectButton button_find_min({ 400, 40 }, { 70, 400 });
    button_find_min.setButtonFont(font);
    button_find_min.setButtonLable(L"Найти минимальный элемент", sf::Color::White, 30);

    RectButton button_exit({ 400, 40 }, { 70, 600 });
    button_exit.setButtonFont(font);
    button_exit.setButtonLable(L"Выход", sf::Color::White, 30);

    bool is_came = false;
    int point_start = text_eyes.getPosition().x;
    int point_finish = text_eyes.getPosition().x + 40;

    while (window.isOpen())
    {
        sf::Event event;

        button_vertical_print.getButtonStatus(window, event);
        button_horizontal_print.getButtonStatus(window, event);
        button_tree_traversal.getButtonStatus(window, event);
        button_add_node.getButtonStatus(window, event);
        button_delete_node.getButtonStatus(window, event);
        button_balanced_tree.getButtonStatus(window, event);
        button_find_element.getButtonStatus(window, event);
        button_find_min.getButtonStatus(window, event);
        button_exit.getButtonStatus(window, event);

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
                    if (button_balanced_tree.isPressed)
                    {
                        values.clear();
                        tree->LNR(&values);
                        Tree* new_tree = new Tree(values[0]);
                        for (size_t i = 1; i < values.size(); i++)
                        {
                            new_tree = insertNode(new_tree, values[i]);
                        }
                        new_tree->draw(L"Сбалансированное дерево");
                    }
                    if (button_add_node.isPressed)
                    {
                        tree->addNode();
                    }
                    if (button_delete_node.isPressed)
                    {
                        tree->delNode();
                    }
                    if (button_find_element.isPressed)
                    {
                        std::string key = getDataWindow(L"Найти элемент");
                        if (key != "")
                        {
                            Tree* founded_element = tree->find(std::stod(key));
                            if (founded_element == nullptr)
                            {
                                MessageBox(L"Элемент не найден");
                            }
                            else
                            {
                                std::wstring text = L"Элемент найден: " + std::to_wstring(founded_element->getData());
                                MessageBox(text);
                            }
                        }
                    }
                    if (button_find_min.isPressed)
                    {
                        std::vector<double> vect;
                        tree->LNR(&vect);
                        Tree* min_element = tree->find(vect[0]);
                        std::wstring text = L"Элемент найден: " + std::to_wstring(min_element->getData());
                        MessageBox(text);
                    }
                    if (button_exit.isPressed)
                    {
                        window.close();
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
        button_balanced_tree.draw(window);
        button_find_element.draw(window);
        button_find_min.draw(window);
        button_exit.draw(window);
        window.draw(circle);

        window.draw(text_eyes);

        if (clock.getElapsedTime().asSeconds() >= move_interval)
        {
            if (text_eyes.getPosition().x > point_start && is_came)
            {
                text_eyes.move(-1, 0);
                if (text_eyes.getPosition().x == point_start)
                {
                    is_came = false;
                }
            }
            if (text_eyes.getPosition().x < point_finish && !is_came)
            {
                text_eyes.move(1, 0);
                if (text_eyes.getPosition().x == point_finish)
                {
                    is_came = true;
                }
            }
            window.draw(text_eyes);
            clock.restart();
        }

        window.display();
    }
    return 0;
}

std::vector<double> tree_rand(int size)
{
    std::vector<double> vect;
    for (int i = 0; i < size; i++)
    {
        double element = rand() % 1000;
        vect.push_back(element / 10.0);
    }
    return vect;
}