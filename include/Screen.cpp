#include "Screen.hpp"

//control variables
void Screen::initVariables(){
    this->window = nullptr;
    this->clock = new sf::Clock;
    
}

//init window
void Screen::initWindow(){
    this->videoMode.height = 576;
    this->videoMode.width = 1024;
    this->window = new sf::RenderWindow(this->videoMode, "Sorting Algorithms", sf::Style::Titlebar | sf::Style::Close);
    this->bg = new sf::RectangleShape(sf::Vector2f(this->videoMode.width, this->videoMode.height));
    this->window->setFramerateLimit(144);
}

//init vector

void::Screen::initVector(){
    for (int i =0;i<128;i++){
        this->lines.push_back(sf::RectangleShape(sf::Vector2f(8, generateNumber(1,576))));
        this->lines.back().setFillColor(sf::Color::White);
        this->lines.back().setOutlineColor(sf::Color::Magenta);
        this->lines.back().setOutlineThickness(1.f);
        this->lines.back().setPosition((i*8), 576-this->lines.back().getSize().y);
    }
}

//constructor and destructor
Screen::Screen(){
    this->initVariables();
    this->initWindow();
    this->initVector();
}

Screen::~Screen(){
    delete this->window;
}

//access
const bool Screen::running() const{
    return this->window->isOpen();
}

//on screen events
void Screen::pollEvent(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    window->close();
                if (this->ev.key.code == sf::Keyboard::Enter)
                    this->updateVector();
                break;
        }
    }
}

//get mouse positions

void Screen::updateMousePos(){
    this->mousePosWindow = sf::Mouse::getPosition();
    this->mousePosFloat = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Screen::updateVector(){
    this->QuickSort(this->lines, 0, static_cast<int>(this->lines.size()-1));
    for (int i=0;i<this->lines.size();i++){
        this->lines[i].setPosition((i*8), 576-this->lines[i].getSize().y);
        std::cout<< this->lines[i].getSize().y << std::endl;
    }
    this->window->display();
}

void Screen::update(){
    this->pollEvent();
    this->updateMousePos();
    this->updateVector();
}


void Screen::renderVector(){
    for(auto it : this->lines){
        this->window->draw(it);
    }
}


void Screen::render(){
    //clear old frames
    this->window->clear();

    this->renderVector();
    

    //show new frames
    this->window->display();
}


int Screen::Partition(std::vector<sf::RectangleShape> &v, int low, int high){
    int i = low-1;
    int pivot=v[high].getSize().y;
    for (int j = low; j < high; j++){
        if (v[j].getSize().y <= pivot){
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i+1], v[high]);
    return i+1;
}

void Screen::QuickSort(std::vector<sf::RectangleShape> &v, int low , int high){
    if (low < high){
        int p = Partition(v, low, high);
        if(this->clock->getElapsedTime().asMilliseconds() > 1000.f){
            QuickSort(v, low, p-1);
            this->window->clear();
            this->renderVector();
            this->window->display();
            this->clock->restart();
        }
        if(clock->getElapsedTime().asMilliseconds() > 1000.f){
            QuickSort(v, p+1, high);
            this->window->clear();
            this->renderVector();
            this->window->display();
            this->clock->restart();
        }
    }
}

