#include "tree.h"


int main()
{
    // Анти-алиасинг
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Создание и инициализация вашего дерева
    std::vector<double> values = {10.0, 3.0, 7.0, 2.0, 155.0, 6.0, 8.0 };

    Tree* tree = new Tree(values);

    // Создание окна SFML
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
        drawTree(window, tree, 400, 50, 5); // root - корень вашего дерева
        
        RectangleShape rect(Vector2f(150, 150));
        rect.setPosition(Vector2f(200, 200));
        rect.setOutlineThickness(1);
        rect.setOutlineColor(Color(0, 0, 0));
        rect.setFillColor(Color(255, 255, 0));
        rect.setRotation(0);

        window.draw(rect);
        window.display();
    }
    return 0;
}

/*
int main()
{
    // Создание окна SFML
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
        window.display();
    }
    return 0;
}
*/