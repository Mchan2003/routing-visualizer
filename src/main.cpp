#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "shortest_path.h"
#include "prims.h"
#include "kruskals.h"

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

void drawSpanningTree(std::vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>> primVector)
{
    std::vector<sf::CircleShape> nodes;
    std::vector<std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>>> edges;

    std::vector<sf::CircleShape> pathNodes;
    std::vector<std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>>> pathEdges;
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

        for(auto& it : primVector)
        {
            sf::CircleShape circle1(nodeSize);
            sf::CircleShape circle2(nodeSize);
            circle1.setFillColor(sf::Color::Red);
            circle2.setFillColor(sf::Color::Red);
            circle1.setPosition(std::get<0>(it)->coords.first - nodeSize, std::get<0>(it)->coords.second - nodeSize );
            circle2.setPosition(std::get<1>(it)->coords.first - nodeSize, std::get<1>(it)->coords.second - nodeSize );
            pathNodes.push_back(circle1);
            pathNodes.push_back(circle2);
            std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> tempPEdge = {std::get<0>(it)->coords, std::get<1>(it)->coords};
            pathEdges.push_back(tempPEdge);
        }

        for(auto& it : pathEdges)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(it.first.first, it.first.second), sf::Color::Red),
                sf::Vertex(sf::Vector2f(it.second.first, it.second.second), sf::Color::Red)
            };
            window.draw(line , 2, sf::Lines);
        }

        for(auto& it : pathNodes)
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

void drawShortestPath(std::vector<graph_path> shortPath)
{
    std::vector<sf::CircleShape> nodes;
    std::vector<std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>>> edges;

    std::vector<sf::CircleShape> pathNodes;
    std::vector<std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>>> pathEdges;
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

        for(auto& it : shortPath)
        {
            sf::CircleShape circle1(nodeSize);
            sf::CircleShape circle2(nodeSize);
            circle1.setFillColor(sf::Color::Red);
            circle2.setFillColor(sf::Color::Red);
            circle1.setPosition(std::get<0>(it)->coords.first - nodeSize, std::get<0>(it)->coords.second - nodeSize );
            circle2.setPosition(std::get<1>(it)->coords.first - nodeSize, std::get<1>(it)->coords.second - nodeSize );
            pathNodes.push_back(circle1);
            pathNodes.push_back(circle2);
            std::pair< std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> tempPEdge = {std::get<0>(it)->coords, std::get<1>(it)->coords};
            pathEdges.push_back(tempPEdge);
        }

        for(auto& it : pathEdges)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(it.first.first, it.first.second), sf::Color::Red),
                sf::Vertex(sf::Vector2f(it.second.first, it.second.second), sf::Color::Red)
            };
            window.draw(line , 2, sf::Lines);
        }

        for(auto& it : pathNodes)
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

void findShortestPath()
{
    char source;
    char destination;

    std::cout << "Enter Source Node:";
    std::cin >> source;

    std::cout << "Enter Destination Node: ";
    std::cin >> destination;

    std::vector<graph_path> shortPath = shortest_path(Node::all_nodes[source], Node::all_nodes[destination]);

    
    cout << "Nodes in stortest path\n";
    for (auto i : shortPath) {
      cout << "source: " << get<0>(i)->label << " "
           << "destination: " << get<1>(i)->label << " "
           << "weight: " << get<2>(i) << "\n";
    }

    drawShortestPath(shortPath);

}

void Prim()
{
    char source;

    std::cout << "Enter Source Node: ";
    std::cin >> source;

    std::vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>> primTree = prims_algo(Node::all_nodes[source]);

    cout << "Nodes in spanning tree with prim\n";
    for (auto i : primTree) {
      cout << "source: " << get<0>(i)->label << " "
           << "destination: " << get<1>(i)->label << " "
           << "weight: " << get<2>(i) << "\n";
    }

    drawSpanningTree(primTree);

    
}

void Kuskals()
{
    char source;

    std::cout << "Enter Source Node: ";
    std::cin >> source;

    vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>> KuskalTree = kruskals_algo(Node::all_nodes[source]);
    
    cout << "Nodes in spanning tree with Kruskals\n";
    for (auto i : KuskalTree) {
      cout << "source: " << get<0>(i)->label << " "
           << "destination: " << get<1>(i)->label << " "
           << "weight: " << get<2>(i) << "\n";
    }
    drawSpanningTree(KuskalTree);
}

void spanningTrees()
{
    std::string input;
    std::cout << "Enter Spanning Tree Algorithm: ";
    getline(std::cin, input);

    if(input == "Prim")
    {
        Prim();
    }
    else if(input == "Kuskals")
    {
        Kuskals();
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
            case hashFunction("Find Shortest Path"):
                findShortestPath();
                break;
            case hashFunction("Find Spanning Tree"):
                spanningTrees();
                break;
            case hashFunction("exit"):
                goto exit_loop;
        }
    }
    exit_loop:;
    return 0;
}