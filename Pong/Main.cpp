#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define calulateAonH(h) (2*h)/1.73205080757
sf::VertexArray triangle(sf::Triangles, 3);
int fps = 2400;

/*
Rules of triangle using chaos:
    1. Take three points in a plane to form a triangle.
    2. Randomly select any point inside the triangle and consider that your current position.
    3. Randomly select any one of the three vertex points.
    4. Move half the distance from your current position to the selected vertex.
    5. Plot the current position.
    6. Repeat from step 3.

The defintion of "calculateAonH is a function used to calculate the sides of the triangle
based on its height. The maths goes something like this. Consider a equilateral triangle
with sides of length "a" and height of length "h". This triangle can be dived into two
right angled triangle with sides "a", "a/2", and "h". The lenth of "a" using this divided
triangle can then be calculated using pythagorean theorem where h^2 = a^2 - (0.5a)^2
this can simplified too h^2 = a^2 (1 - 1/4) now square rooting bothsides yields
h = a sqrt(3)/2 this can finally be rearranged for a yielding a = 2h/sqrt(3)
sqrt(3) can be precalculated to help optimise this small function.
*/

/*Recursive functions to calculate new points*/
std::vector<sf::Vector2f>* calculateNewPosition(int depth, std::vector<sf::Vector2f>* pointVec) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    sf::Vector2f newCoords;
    --depth;
    int randomVertex = dist(gen);
    newCoords.x = (pointVec->back().x + triangle[randomVertex].position.x) / 2;
    newCoords.y = (pointVec->back().y + triangle[randomVertex].position.y) / 2;
    pointVec->push_back(newCoords);
    if (depth == 0) {
        return pointVec;
    }
    calculateNewPosition(depth, pointVec);

}

int main()
{

    /*Setting up window and point shape*/
    sf::Vector2f screenDim(800, 800);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Sierpinski triangle", sf::Style::Default, settings);
    window.setFramerateLimit(fps);
    sf::CircleShape point(1.f);
    point.setFillColor(sf::Color::Black);

    /*Setting up text to display how many points have been drawn*/
    std::ostringstream ss;
    ss << 0;

    sf::Font font;
    if (!font.loadFromFile("RobotoMono-Bold.ttf")) { return -1; }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setString(ss.str());
    text.setPosition(sf::Vector2f((text.getLocalBounds().width * 0.1), text.getLocalBounds().height * 0.1));

    /*Calculate triangle dimensions*/
    int a = calulateAonH(screenDim.y - (2 * (screenDim.y * 0.05)));    
    triangle[0].position = sf::Vector2f(1200 / 2, 800 * 0.05);
    triangle[1].position = sf::Vector2f(1200 / 2 + (a / 2), 800 * 0.95);
    triangle[2].position = sf::Vector2f(1200 / 2 - (a / 2), 800 * 0.95);
    triangle[0].color = sf::Color(255, 0, 0);
    triangle[1].color = sf::Color(0, 255, 0);
    triangle[2].color = sf::Color(0, 0, 255);

    /*Create points vector to store points from rule 5*/
    std::vector<sf::Vector2f>* pointVec = new std::vector<sf::Vector2f>();
    pointVec->push_back(sf::Vector2f(1200/2, 800 / 2));
    std::vector<sf::Vector2f>* points;
    points = calculateNewPosition(2, pointVec);         //change first number to precalculate some points
    
    /*Some maths to change triangle color*/
    float rad = 0;
    float deltaRad = 0.5;

    while (window.isOpen()){
        rad += deltaRad * 1 / fps;
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        /*change the triangle color*/
        //triangle[0].color = sf::Color(255 * fabsf(sin(rad)), 0, 0);
        //triangle[1].color = sf::Color(0  , 255 * fabsf(cos(rad)), 0);
        //triangle[2].color = sf::Color(0  , 0  , 255 * (fabsf(cos(rad)) + fabsf(sin(rad)))/1.414);
        window.draw(triangle);

        /*Iterate through all points and draw them*/
        for (auto& pos : *points) {
            point.setPosition(pos);
            window.draw(point);
        }
        points = calculateNewPosition(2, points);

        /*Print number of points drawn*/
        std::ostringstream ss;
        ss << points->size();
        text.setString(ss.str());
        window.draw(text);

        window.display();
    }
    delete points, pointVec;
    return 0;
}