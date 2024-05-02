#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#define HASHSIZE 100

constexpr unsigned long hashFunction(const char* stringInput)
{
    unsigned long hash = 5381;
    int c = 0;
    while((c = *stringInput++)) hash = ((hash << 5) + hash) + c;

    return hash;
}

void drawGraph(int position)
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::CircleShape circle(50);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(position,position); 
        window.draw(circle);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Backspace))
        {
            window.close();
        }
    }
}

int main()
{
    std::string input;

    while (input != "exit")
    {
        std::cout << "Enter Option: " << std::endl;
        getline(std::cin, input);
        switch(hashFunction(input.c_str()))
        {
            case hashFunction("three"):
                drawGraph(300);
                break;
            case hashFunction("five"):
                drawGraph(500);
                break;
            case hashFunction("two"):
                drawGraph(200);
                break;
            case hashFunction("exit"):
                goto exit_loop;
        }
    }
    exit_loop:;
    return 0;
}