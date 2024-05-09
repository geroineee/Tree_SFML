#include "tree.h"

int main()
{
    // Создание и инициализация вашего дерева
    std::vector<double> values = {10.0, 3.0, 7.0, 2.0, 155.0, 6.0, 8.0 };

    Tree* tree = Tree::createTree(values);

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

        //window.clear(sf::Color::White);
        // Визуализация дерева
        window.clear(sf::Color::White);
        drawTree(window, tree, 400, 50, 5); // root - корень вашего дерева

        
        window.display();
    }

    return 0;
}