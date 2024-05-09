#include "tree.h"

std::vector<double> tree_rand(int size)
{
    std::vector<double> vect;
    for (int i = 0; i < size; i++)
    {
        double element = rand() % 100;
        vect.push_back(element/10.0);
    }
    return vect;
}

int main()
{
    srand(time(0));

    // ����-��������
    ContextSettings settings;
    //settings.antialiasingLevel = 8;

    // �������� � ������������� ������ ������
    std::vector<double> values = tree_rand(7);

    Tree* tree = new Tree(values);

    // �������� ���� SFML
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
        drawTree(window, tree, 400, 50, 5); // ��������� ������
        
        window.display();
    }
    return 0;
}

/*
int main()
{
    // �������� ���� SFML
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