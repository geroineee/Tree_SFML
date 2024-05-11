#include "tree.h"
#include "button.h"


Tree::Tree() {}

Tree::Tree(double value)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    data = value;
}

Tree::~Tree()
{
    this->delete_tree();
}

Tree::Tree(const std::vector<double>& values)
{
    if (values.empty()) { return; }

    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = values[0];

    for (size_t i = 1; i < values.size(); i++) 
    {
        this->insert(values[i]);
    }
}

int Tree::find_height()
{
    int height_left = 0, height_right = 0;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
    {
        height_left = this->left->find_height();
        //this->height = height_left + 1;
    }
    if (this->right != nullptr)
    {
        height_right = this->right->find_height();
        //this->height = height_right + 1;
    }
    return std::max(height_right, height_left) + 1;
}

int Tree::find_left_lenght(int level)
{
    int lenght_left = 0, lenght_right = lenght_left;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
    {
        lenght_left += shift_x * level * 1.5;
        lenght_left += this->left->find_left_lenght(level - 1);
    }
    if (this->right != nullptr)
    {
        lenght_right -= shift_x * level * 1.5;
        lenght_right += this->right->find_left_lenght(level - 1);
    }
    return std::max(lenght_left, lenght_right);
}

int Tree::find_right_lenght(int level)
{
    int lenght_right = 0, lenght_left = lenght_right;
    if (this == nullptr)
        return 0;
    if (this->left != nullptr)
    {
        lenght_left -= shift_x * level * 1.5;
        lenght_left += this->left->find_right_lenght(level - 1);
    }
    if (this->right != nullptr)
    {
        lenght_right += shift_x * level * 1.5;
        lenght_right += this->right->find_right_lenght(level - 1);
    }
    return std::max(lenght_left, lenght_right);
}

void Tree::insert(double value)
{
    if (value < data) 
    {
        if (left == nullptr) 
        {
            left = new Tree(value);
            left->parent = this;
        }
        else 
        {
            left->insert(value);
        }
    }
    else 
    {
        if (right == nullptr) 
        {
            right = new Tree(value);
            right->parent = this;
        }
        else 
        {
            right->insert(value);
        }
    }
}

void Tree::draw(const std::wstring title, bool isHorisontal)
{
    int height_tree = this->find_height();
    int lenght_left = this->find_left_lenght(height_tree);
    int lenght_right = this->find_right_lenght(height_tree);
    float window_width, window_height;

    if (!isHorisontal)
    {
        window_width = 100 + lenght_left + lenght_right;
        window_height = 150 + this->node_radius * 2 + shift_y * (height_tree - 1);
    }
    else
    {
        window_width = 100 + this->node_radius * 2 + shift_y * (height_tree - 1);
        window_height = 150 + lenght_left + lenght_right;
    }

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), title);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("gta.ttf");

    RectButton button_back({ 150, 40 }, { window_width / 2 - 75, window_height - 70 });
    button_back.setButtonFont(font);
    button_back.setButtonLable(L"Назад", sf::Color::White, 30);

    while (window.isOpen())
    {
        sf::Event event;

        button_back.getButtonStatus(window, event);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (button_back.isPressed == true)
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        button_back.draw(window);

        // отрисовка дерева
        if (!isHorisontal)
            drawTree(window, this, 50 + lenght_left, 50, height_tree, isHorisontal);
        else
            drawTree(window, this, 50, 50 + lenght_right, height_tree, isHorisontal);

        window.display();
    }
}

void drawLine(sf::RenderWindow& window, int radius, Vector2f pos_start, Vector2f pos_finish)
{
    float x1 = pos_start.x, y1 = pos_start.y, x2 = pos_finish.x, y2 = pos_finish.y;
    float delta_x = fabs(x1 - x2);
    float delta_y = fabs(y1 - y2);

    float lenght = sqrt(pow(x1 - x2, 2) + pow(y2 - y1, 2));
    RectangleShape rect({ 1, lenght });

    rect.setFillColor(Color(0, 0, 0));
    rect.setPosition({ x1, y1 });
    float angle;

    if (x2 < x1 && y2 > y1)
    {
        angle = 57.2958 * asin(delta_x / lenght);
    }
    if (x2 > x1 && y2 > y1)
    {
        angle = 270 + 57.2958 * asin(delta_y / lenght);
    }
    if (x2 > x1 && y2 < y1)
    {
        angle = 180 + 57.2958 * asin(delta_x / lenght);
    }
    rect.setRotation(angle);

    window.draw(rect);
}

void drawTree(sf::RenderWindow& window, Tree* node, float x, float y, int level, bool isHorisontal)
{
    if (node == nullptr) return;

    int radius = node->getNodeRadius();
    int shift_x = node->getShiftX();
    int shift_y = node->getShiftY();
    int font_size = node->getFontSize();
    Vector2f position(x - radius, y - radius);

    node->setPosition({ x, y });

    // Отображение узла как окружности
    sf::CircleShape circle(radius);
    circle.setPosition(position);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);

    // Отображение значения узла внутри окружности
    sf::Font font;
    font.loadFromFile("gta.ttf"); // шрифт

    // Форматирование значения узла
    std::ostringstream buf;
    buf << std::fixed << std::setprecision(1) << node->getData();

    sf::Text text(buf.str(), font);
    text.setCharacterSize(font_size);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(x - (font_size / 2.5 * buf.str().size() / 2) + 1 + (buf.str().size()), y - (font_size * 0.75) + 1);

    if (node->getParent() != nullptr)
    {
        Vector2f pos_parent, pos_node;
        pos_parent = node->getParent()->getPosition();
        pos_node = node->getPosition();

        if (!isHorisontal)
        {
            pos_parent.y += radius;
            pos_node.y -= radius;
        }
        else
        {
            pos_parent.x += radius;
            pos_node.x -= radius;
        }
        //drawLine(window, node->getNodeRadius(), pos_parent, pos_node);
    }
    window.draw(circle);
    window.draw(text);


    // Рекурсивные вызовы для левого и правого потомка узла
    if (!isHorisontal)
    {
        if (node->getLeft() != nullptr)
        {
            drawTree(window, node->getLeft(), x - shift_x * level * 1.5, y + shift_y, level - 1, isHorisontal);
        }

        if (node->getRight() != nullptr)
        {
            drawTree(window, node->getRight(), x + shift_x * level * 1.5, y + shift_y, level - 1, isHorisontal);
        }
    }
    else
    {
        if (node->getLeft() != nullptr)
        {
            drawTree(window, node->getLeft(), x + shift_y, y + shift_x * level * 1.5, level - 1, isHorisontal);
        }

        if (node->getRight() != nullptr)
        {
            drawTree(window, node->getRight(), x + shift_y, y - shift_x * level * 1.5, level - 1, isHorisontal);
        }
    }
}

void Tree::showTraversals()
{
    sf::Font font;
    font.loadFromFile("gta.ttf");
    int font_size = 30;

    float window_width, window_height = 330;
    int count_node = (getNodesCnt()+1) * 3;
    if (count_node < 25)
        window_width = font_size / 2.5 * 25;
    else
        window_width = font_size / 2.5 * count_node;
    sf::RenderWindow window(sf::VideoMode(window_width + 100, window_height), L"Обходы дерева");
    window.setVerticalSyncEnabled(true);

    RectButton button_back({ 150, 40 }, { window_width / 2 - 30, window_height - 70 });
    button_back.setButtonFont(font);
    button_back.setButtonLable(L"Назад", sf::Color::White, 30);

    while (window.isOpen())
    {
        sf::Event event;

        button_back.getButtonStatus(window, event);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (button_back.isPressed == true)
                    {
                        window.close();
                    }
                }
            }
        }
        
        std::vector <double> vect;
        std::wstring text_to_show = L"";

        // прямой обход (NLR)
        text_to_show = L"";
        this->NLR(&vect);
        for (size_t i = 0; i < vect.size(); i++)
        {
            std::ostringstream buf;
            buf << std::fixed << std::setprecision(1) << vect[i];
            text_to_show = text_to_show + " " + buf.str();
        }

        sf::Text text_NLR(L"прямой обход (nlr):\n" + text_to_show, font);
        text_NLR.setCharacterSize(font_size);
        text_NLR.setPosition({50, 50});
        text_NLR.setOutlineThickness(1);
        text_NLR.setOutlineColor(Color::Black);
        vect.clear();

        // симметричный обход (LNR)
        text_to_show = L"";
        this->LNR(&vect);
        for (size_t i = 0; i < vect.size(); i++)
        {
            std::ostringstream buf;
            buf << std::fixed << std::setprecision(1) << vect[i];
            text_to_show = text_to_show + " " + buf.str();
        }

        sf::Text text_LNR(L"Симметричный обход (lnr):\n" + text_to_show, font);
        text_LNR.setCharacterSize(font_size);
        text_LNR.setPosition({ 50, 110});
        text_LNR.setOutlineThickness(1);
        text_LNR.setOutlineColor(Color::Black);
        vect.clear();

        // обратный проход (LRN)
        text_to_show = L"";
        this->LRN(&vect);
        for (size_t i = 0; i < vect.size(); i++)
        {
            std::ostringstream buf;
            buf << std::fixed << std::setprecision(1) << vect[i];
            text_to_show = text_to_show + " " + buf.str();
        }

        sf::Text text_LRN(L"Обратный проход (lrn):\n" + text_to_show, font);
        text_LRN.setCharacterSize(font_size);
        text_LRN.setPosition({ 50, 170 });
        text_LRN.setOutlineThickness(1);
        text_LRN.setOutlineColor(Color::Black);
        vect.clear();

        window.clear(sf::Color::White);

        // отрисовка виджетов
        button_back.draw(window);
        window.draw(text_NLR);
        window.draw(text_LNR);
        window.draw(text_LRN);
        window.display();
    }
}

//  прямой проход (NLR)
void Tree::NLR(std::vector<double>* vect)
{
    if (this == nullptr)
    {
        return;
    }
    vect->push_back(this->data);

    if (this->left != nullptr)
    {
        this->left->NLR(vect);
    }

    if (this->right != nullptr)
    {
        this->right->NLR(vect);
    }
}

// симметричный проход (LNR)
void Tree::LNR(std::vector<double>* vect)
{
    if (this == nullptr)
    {
        return;
    }

    if (this->left != nullptr)
    {
        this->left->LNR(vect);
    }
    vect->push_back(this->data);

    if (this->right != nullptr)
    {
        this->right->LNR(vect);
    }
    
}

// обратный проход (LRN)
void Tree::LRN(std::vector<double>* vect)
{
    if (this == nullptr)
    {
        return;
    }

    if (this->left != nullptr)
    {
        this->left->LRN(vect);
    }

    if (this->right != nullptr)
    {
        this->right->LRN(vect);
    }
    vect->push_back(this->data);
}

int Tree::getNodesCnt()
{
    int cnt = 0;

    if (this == nullptr)
    {
        return 0;
    }

    if (this->left != nullptr)
    {
        cnt += 1 + this->left->getNodesCnt();
    }

    if (this->right != nullptr)
    {
        cnt += 1 + this->right->getNodesCnt();
    }
    return cnt;
}

void Tree::balanced_tree()
{
    if (this == nullptr) return;
    this->updateHeight();
    int balanceFactor = this->getBalanceFactor();
    if (balanceFactor > 1)
    {
        if (this->left->getBalanceFactor() < 0)
        {
            this->left->rotateLeft();
        }
        this->rotateRight();
    }
    else if (balanceFactor < -1)
    {
        if (this->right->getBalanceFactor() > 0)
        {
            this->right->rotateRight();
        }
        this->rotateLeft();
    }
    else
    {
        return;
    }
    this->balanced_tree();
}

int Tree::getBalanceFactor()
{
    if (this == nullptr) return 0;
    return this->left->find_height() - this->right->find_height();
}

void Tree::delete_tree()
{
    if (this == nullptr)
    {
        return;
    }

    if (this->left != nullptr)
    {
        this->left->delete_tree();
    }

    if (this->right != nullptr)
    {
        this->right->delete_tree();
    }
    delete this;
}

void Tree::rotateLeft()
{
    Tree* newRoot = this->right;
    this->right = newRoot->left;
    if (newRoot->left != nullptr)
        newRoot->left->parent = this;
    newRoot->left = this;
    newRoot->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this->parent->left == this)
            this->parent->left = newRoot;
        else
            this->parent->right = newRoot;
    }
    this->parent = newRoot;
    this->updateHeight();
    newRoot->updateHeight();
    *this = *newRoot;
}

void Tree::rotateRight()
{
    Tree* newRoot = this->left;
    this->left = newRoot->right;
    if (newRoot->right != nullptr)
        newRoot->right->parent = this;
    newRoot->right = this;
    newRoot->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this->parent->left == this)
            this->parent->left = newRoot;
        else
            this->parent->right = newRoot;
    }
    this->parent = newRoot;
    this->updateHeight();
    newRoot->updateHeight();
    *this = *newRoot;
}

void Tree::updateHeight()
{
    if (this != nullptr)
    {
        this->height = 1 + std::max(this->left->find_height(), this->right->find_height());
    }
}
