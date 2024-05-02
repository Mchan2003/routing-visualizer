#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "node.h"

constexpr unsigned long hashFunction(const char* stringInput)
{
    unsigned long hash = 5381;
    int c = 0;
    while((c = *stringInput++)) hash = ((hash << 5) + hash) + c;

    return hash;
}

void drawGraph()
{
    std::vector<sf::CircleShape> nodes;
    std::vector<std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>>> edges;
    int nodeSize = 30;

    for(auto i = Node::all_nodes.begin(); i != Node::all_nodes.end(); i++)
    {
        sf::CircleShape tempNode(nodeSize);
        tempNode.setFillColor(sf::Color::Green);
        tempNode.setPosition(i->second->coords.first - (nodeSize), i->second->coords.second - (nodeSize));
        nodes.push_back(tempNode);

        for(auto j = i->second->adj.begin(); j != i->second->adj.end(); j++)
        {
            std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> tempEdge = {i->second->coords, j->first->coords};
            edges.push_back(tempEdge);
        }
    }
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Graph");
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for(auto& it : edges)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(it.first.first, it.first.second), sf::Color::Green),
                sf::Vertex(sf::Vector2f(it.second.first, it.second.second), sf::Color::Green)
            };
            window.draw(line , 2, sf::Lines);
        }

        for(auto& it : nodes)
        {
            window.draw(it);
        }

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Backspace))
        {
            window.close();
        }
    }
}

void addNode ()
{
    char adjNode;
    char nodeLabel;
    uint32_t nodeXCoords;
    uint32_t nodeYCoords;
    std::pair<uint32_t, uint32_t> nodeCoords;

    std::cout << "Enter Node: ";
    std::cin >> nodeLabel;

    std::cout << "Enter X Coordinate: ";
    std::cin >> nodeXCoords;

    std::cout << "Enter Y Coordinate: ";
    std::cin >> nodeYCoords;

    nodeCoords = {nodeXCoords, nodeYCoords};
    Node::create(nodeLabel, nodeCoords);

    while(adjNode != 'z')
    {
        std::cout << "Add edge to node (z to exit): ";
        std::cin >> adjNode;
        if(adjNode == 'z')
        {
            break;
        }
        Node::all_nodes[nodeLabel]->add_edge(adjNode);
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
            case hashFunction("Display Graph"):
                drawGraph();
                break;
            case hashFunction("Add Node"):
                addNode();
                break;
            case hashFunction("exit"):
                goto exit_loop;
        }
    }
    exit_loop:;
    return 0;
}