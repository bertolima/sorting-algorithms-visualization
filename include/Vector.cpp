
#include "Vector.hpp"


Vector::Vector(sf::Clock clock){
    this->clock = clock;
}

Vector::~Vector(){

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

void Vector::fill(int i){
    this->arr.push_back(sf::RectangleShape(sf::Vector2f(8, generateNumber(1,576))));
    this->arr.back().setFillColor(sf::Color::White);
    this->arr.back().setOutlineColor(sf::Color::Cyan);
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

int Vector::Partition(int low, int high, sf::RenderWindow*target, sf::Event* ev){
    bool ver = false;
    
    while (ver == false){
        switch(ev->type){
            case sf::Event::Closed:
                target->close();
                break;
            case sf::Event::KeyPressed:
                if (ev->key.code == sf::Keyboard::Escape)
                    target->close();
                break;
        }
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
            this->arr[i+1].setOutlineColor(sf::Color::Cyan);
            this->arr[high].setFillColor(sf::Color::White);
            this->arr[high].setOutlineColor(sf::Color::Cyan);

            return i+1;
        }
    }
}

void Vector::QuickSort(int low , int high, sf::RenderWindow* target, sf::Event* ev){
    if (low < high){
        int p = Partition(low, high, target, ev);
        QuickSort(low, p-1, target, ev);
        QuickSort(p+1, high, target, ev);
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