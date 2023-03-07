#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "QuickSort.hpp"
#include "random.hpp"
#include <iostream>

class Screen{
    private:
        //window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        //mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosFloat;

        //vector
        std::vector<sf::RectangleShape> lines;

        //private functions
        void initVariables();
        void initWindow();
        void initVector();
        
    public:
        //cosntructor and destructor
        Screen();
        virtual ~Screen();

        //access
        const bool running() const;

        //functions
        void pollEvent();
        void updateMousePos();


        void update();

        void renderVector();
        void render();


};

