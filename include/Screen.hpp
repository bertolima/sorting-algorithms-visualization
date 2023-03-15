#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "random.hpp"
#include "Vector.hpp"
#include <map>
#include "Button.hpp"
#include <thread>
#include <iostream>

enum sort_state{STATE_ZERO = 0, STATE_NONE, STATE_QUICK, STATE_BUBBLE, STATE_MERGE, STATE_SELECTION, STATE_HEAP};


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
        Vector *vector;

        //buttons
        std::map<std::string, Button*> buttons;
        std::map<std::string, Button*> control_buttons;

        //font
        sf::Font font;

        //control variables
        unsigned short sort_state;
        bool runningSort;



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

        void QuickSort(Vector&, int, int);
        int Partition(Vector&, int, int);
        void BubbleSort(Vector&, int);
        void Merge(Vector& v, int left, int mid, int right);
        void MergeSort(Vector& v, int left, int right);
        void SelectionSort(Vector&v , int);
        void Heapify(Vector& v, int size, int i);
        void HeapSort(Vector& v, int size);


};

