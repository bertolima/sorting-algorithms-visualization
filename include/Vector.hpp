#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <random.hpp>

class Vector{
    private:
        std::vector<sf::RectangleShape> arr;
        bool ordered;
    public:
    //constructor and destructor
        Vector();
        ~Vector();
        
        //access
        bool const isOrdered() const;

        //functions
        void fill(sf::RectangleShape rec, int i);



};