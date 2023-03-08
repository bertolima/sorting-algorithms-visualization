#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "random.hpp"
#include <vector>
#include <map>
#include "Button.hpp"

class Screen{
    private:
        //window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;
        sf::Clock* clock;
        sf::RectangleShape* bg;

        //mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosFloat;

        //vector
        std::vector<sf::RectangleShape> lines;

        //buttons
        std::map<std::string, Button*> buttons;

        //font
        sf::Font font;

        //control variables
        bool ordered;
        bool quicksort;


        //private functions
        void initVariables();
        void initWindow();
        void initVector();
        void initButtons();
        

        
    public:
        //cosntructor and destructor
        Screen();
        virtual ~Screen();

        //access
        const bool running() const;

        //functions
        void pollEvent();
        void updateMousePos();
        void updateVector();
        void updateButtons();

        void update();

        void renderVector();
        void renderButtons();

        void render();

        void QuickSort(std::vector<sf::RectangleShape>&, int, int);
        int Partition(std::vector<sf::RectangleShape>&, int, int);


};

