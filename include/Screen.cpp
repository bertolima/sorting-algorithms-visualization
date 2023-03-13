#include "Screen.hpp"

//control variables
void Screen::initVariables(){
    this->window = nullptr;
    this->clock = new sf::Clock;
    this->font.loadFromFile("./include/fonts/The Hoca.ttf");

    this->quicksort = false;
    this->ordered = false;
    this->startQuick = false;

    
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
    this->vector = new Vector(*this->clock);
    for (int i =0;i<128;i++){
        this->vector->fill(i);
    }
}

void Screen::initButtons(){
    this->buttons["QuickSort"] = new Button(this->window->getSize().x/2.f - 75.f, 100, 150, 50,
    &this->font, "QuickSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

//constructor and destructor
Screen::Screen(){
    this->initVariables();
    this->initWindow();
    this->initButtons();
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
                    this->startQuick = true;
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
    if (this->startQuick == true){
        this->vector->QuickSort(0 , static_cast<int>(this->vector->getSize()-1), this->window, &this->ev);
        this->startQuick = false;
    }
         
}

void Screen::updateButtons(){
    for (auto &it : this->buttons){
        it.second->update(this->mousePosFloat);
    }

    if(this->buttons["QuickSort"]->isPressed()){
        this->quicksort = true;
    }
}

void Screen::update(){
    std::thread t1 (&Screen::pollEvent, this);
    std::thread t2 (&Screen::updateMousePos, this);
    std::thread t3 (&Screen::updateButtons, this);
    std::thread t4 (&Screen::updateVector, this);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}


void Screen::renderVector(){
    if (this->quicksort == true){
        this->vector->render(this->window);
    }
}

void Screen::renderButtons(){
    if (quicksort == false)
        this->buttons["QuickSort"]->render(this->window);
    
}


void Screen::render(){
    //clear old frames
    this->window->clear();


    this->renderButtons();
    this->renderVector();

    //show new frames
    this->window->display();
}


