
#include "Vector.hpp"


Vector::Vector(sf::Clock clock){
    this->clock = clock;
}

Vector::~Vector(){

}

bool Vector::isOrdered(){
    for(int i = 1;i<arr.size();i++){
        if (arr[i-1].getSize().y > arr[i].getSize().y){
            return false;
            break;
        }
    }
    return true;
    
}

void Vector::fill(int i){
    this->arr.push_back(sf::RectangleShape(sf::Vector2f(8, generateNumber(1,576))));
    this->arr.back().setFillColor(sf::Color::White);
    this->arr.back().setOutlineColor(sf::Color::Magenta);
    this->arr.back().setOutlineThickness(1.f);
    this->arr.back().setPosition((i*8), 576-this->arr.back().getSize().y);
}

void Vector::update(){
    for (int i=0;i<this->arr.size();i++){
            this->arr[i].setPosition((i*8), 576-this->arr[i].getSize().y);
     }

}

void Vector::render(sf::RenderTarget* target){
    for(auto it : this->arr){
            target->draw(it);
        }
}

int Vector::Partition(int low, int high, sf::RenderWindow*target){
    bool ver = false;
    
    while (ver == false){
        if (this->clock.getElapsedTime().asMilliseconds() > 250.f){
            int i = low-1;
            int pivot=this->arr[high].getSize().y;
            for (int j = low; j < high; j++){
                if (this->arr[j].getSize().y <= pivot){
                    i++;
                    std::swap(this->arr[i], this->arr[j]);
                }
            }
            std::swap(this->arr[i+1], this->arr[high]);
            this->arr[i+1].setFillColor(sf::Color::Red);
            this->arr[high].setFillColor(sf::Color::Red);

            target->clear();
            this->update();
            this->render(target);
            target->display();
            this->clock.restart();
            ver = true;
            this->arr[i+1].setFillColor(sf::Color::White);
            this->arr[i+1].setOutlineColor(sf::Color::Magenta);
            this->arr[high].setFillColor(sf::Color::White);
            this->arr[high].setOutlineColor(sf::Color::Magenta);

            return i+1;
        }
    }
    return 0;
}

void Vector::QuickSort(int low , int high, sf::RenderWindow* target){
    if (low < high){
        int p = Partition(low, high, target);
        QuickSort(low, p-1, target);
        QuickSort(p+1, high, target);
    }
}

int Vector::getSize(){
    return this->arr.size();
}

std::vector<sf::RectangleShape> &Vector::getVector(){
    return this->arr;
}

void Vector::print(){
    for (auto it : this->arr){
        std::cout << it.getSize().y << std::endl;
    }
}

sf::RectangleShape Vector::getElement(int i){
    return this->arr[i];
}

void Vector::swap(int i, int j){
    sf::RectangleShape k = this->arr[i];
    this->arr[i] = this->arr[j];
    this->arr[j] = k;
}

void Vector::setColor(int i, int j){
    switch(j){
        case 0:
            this->arr[i].setFillColor(sf::Color::White);
            this->arr[i].setOutlineColor(sf::Color::Magenta);
            break;
        case 1:
            this->arr[i].setFillColor(sf::Color::Red);
            break;
    }
    
}