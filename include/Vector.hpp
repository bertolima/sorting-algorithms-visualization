#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "random.hpp"
#include <iostream>

class Vector{
    private:
        std::vector<sf::RectangleShape> arr;
        bool ordered;
        sf::Clock clock;
    public:
    //constructor and destructor
        Vector(sf::Clock clock);
        ~Vector();
        
        //access
        bool isOrdered();

        //functions
        void fill(int i);
        void update();
        void render(sf::RenderTarget* target);
        int Partition(int, int, sf::RenderWindow* target);
        void QuickSort(int, int, sf::RenderWindow* target);
        int getSize();
        std::vector<sf::RectangleShape> &getVector();
        sf::RectangleShape getElement(int);
        void print();
        void swap(int, int);
        void setColor(int, int);
        void setElement(int, sf::RectangleShape);

};