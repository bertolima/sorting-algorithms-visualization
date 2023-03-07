#include "Screen.hpp"

//control variables
void Screen::initVariables(){
    this->window = nullptr;
}

//init window
void Screen::initWindow(){
    this->videoMode.height = 576;
    this->videoMode.width = 1024;
    this->window = new sf::RenderWindow(this->videoMode, "Sorting Algorithms", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

//init vector

void::Screen::initVector(){
    for (int i =0;i<10;i++){
        this->lines.emplace_back(sf::RectangleShape(sf::Vector2f(1, generateNumber(1,576))));
        this->lines.back().setFillColor(sf::Color::Green);
        this->lines.back().setPosition(i, 576-this->lines.back().getSize().y);
        // this->v[i]->setSize(sf::Vector2f(1, generateNumber(1,576)));
        // this->v.back()->setFillColor(sf::Color(generateNumber(1,255),generateNumber(1,255), generateNumber(1,255)));
        // this->v.back()->setPosition(1024, 576-this->v.back()->getSize().y);
         
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
                break;
        }
    }
}

//get mouse positions

void Screen::updateMousePos(){
    this->mousePosWindow = sf::Mouse::getPosition();
    this->mousePosFloat = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Screen::update(){
    this->pollEvent();
    this->updateMousePos();
}


void Screen::renderVector(){
    for(auto it : this->lines){
        this->window->draw(it);
    }
}

void Screen::render(){
    //clear old frames
    this->window->clear();

    //here we draw objects
    this->renderVector();


    //show new frames
    this->window->display();
}