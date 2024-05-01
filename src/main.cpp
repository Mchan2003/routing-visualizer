#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::CircleShape shape1(50.f);
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition(100,100);

    sf::CircleShape shape2(50.f);
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition(200,400);

    sf::CircleShape shape3(50.f);
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition(300,200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape1);
        window.draw(shape2);
        window.draw(shape3);
        window.display();
    }

    return 0;
}