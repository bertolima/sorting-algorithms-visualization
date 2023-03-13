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
        bool const isOrdered() const;

        //functions
        void fill(int i);
        void update();
        void render(sf::RenderTarget* target);
        int Partition(int, int, sf::RenderWindow* target, sf::Event* ev);
        void QuickSort(int, int, sf::RenderWindow* target, sf::Event* ev);
        int getSize();
        std::vector<sf::RectangleShape> &getVector();
        void print();

};