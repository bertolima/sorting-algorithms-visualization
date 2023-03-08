
#include "Vector.hpp"

Vector::Vector(){
}

Vector::~Vector(){
    delete this;
}

bool const Vector::isOrdered() const{
    bool ordered = false;
    for(int i = 1;i<arr.size();i++){
        if (arr[i-1].getSize().y < arr[i].getSize().y)
            ordered = true;
        else
            ordered = false;
    }
    if (ordered == true)
        return true;
    return false;
    
}

void Vector::fill(sf::RectangleShape rec, int i){
    this->arr.push_back(sf::RectangleShape(sf::Vector2f(8, generateNumber(1,576))));
    this->arr.back().setFillColor(sf::Color::White);
    this->arr.back().setOutlineColor(sf::Color::Magenta);
    this->arr.back().setOutlineThickness(1.f);
    this->arr.back().setPosition((i*8), 576-this->arr.back().getSize().y);
}