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

    this->buttons["BubbleSort"] = new Button(this->window->getSize().x/2.f - 75.f, 200, 150, 50,
    &this->font, "BubbleSort",
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
    switch(this->sort_state){
        case STATE_NONE:
            break;
        case STATE_QUICK:
            this->QuickSort(*this->vector, 0 , static_cast<int>(this->vector->getSize()-1));
            this->sort_state == STATE_NONE;
            break;
        case STATE_BUBBLE:
            this->BubbleSort(*this->vector, static_cast<int>(this->vector->getSize()-1));
            this->sort_state == STATE_NONE;
            break;
    }  
}

void Screen::updateButtons(){
    for (auto &it : this->buttons){
        it.second->update(this->mousePosFloat);
    }

    if(this->buttons["QuickSort"]->isPressed()){
        this->sort_state = STATE_QUICK;
    }
    if(this->buttons["BubbleSort"]->isPressed()){
        this->sort_state = STATE_BUBBLE;
    }
}

void Screen::update(){
    this->pollEvent();
    this->updateMousePos();
    this->updateButtons();
    this->updateVector();
}


void Screen::renderVector(){
    if (this->sort_state != STATE_ZERO){
        this->vector->render(this->window);
    }
}

void Screen::renderButtons(){
    if (this->sort_state == STATE_ZERO)
        for (auto &it : this->buttons){
            it.second->render(this->window);
        }
    
}


void Screen::render(){
    //clear old frames
    this->window->clear();


    this->renderButtons();
    this->renderVector();

    //show new frames
    this->window->display();
}


























int Screen::Partition(Vector &v, int low, int high){
    if (v.isOrdered() == false){
        bool ver = false;
        while (ver == false){
            this->pollEvent();
            if (this->clock->getElapsedTime().asMilliseconds() > 250.f){
                int i = low-1;
                int pivot = v.getElement(high).getSize().y;
                for (int j = low; j < high; j++){
                    if (v.getElement(j).getSize().y <= pivot){
                        i++;
                        v.swap(i, j);
                    }
                }
                v.swap(i+1, high);
                v.setColor(i+1, 1);
                v.setColor(high, 1);
                this->vector->update();
                this->render();
                for(int i=0;i<v.getSize();i++){
                    this->window->draw(v.getElement(i));
                }
                this->clock->restart();
                ver = true;
                v.setColor(i+1, 0);
                v.setColor(high, 0);
                return i+1;
            }
        }
    }
    
    return -1;
}


void Screen::QuickSort(Vector &v, int low, int high){
    if (low < high){
        int p = Partition(v,low, high);
        if (p != -1){
            QuickSort(v, low, p-1);
            QuickSort(v, p+1, high);
        }
    }
}

void Screen::BubbleSort(Vector &v, int size){
    for (int i = 0; i < size;i++){
        for (int j = 0; j < size-i;j++){
            bool ver = false;
            while (ver == false){
                this->pollEvent();
                if (this->clock->getElapsedTime().asMicroseconds() > 500.f){
                        v.setColor(j, 1);
                        v.setColor(j+1, 1);
                        this->vector->update();
                        this->render();
                        for(int l=0;l<v.getSize();l++){
                            this->window->draw(v.getElement(l));
                        }
                    if (v.getElement(j).getSize().y > v.getElement(j+1).getSize().y){
                        v.swap(j, (j+1));

                        this->vector->update();
                        this->render();
                        for(int l=0;l<v.getSize();l++){
                            this->window->draw(v.getElement(l));
                        }
                        
                    }
                    v.setColor(j, 0);
                    v.setColor(j+1, 0);
                    this->clock->restart();
                    ver = true;
                }
            }
        }
    }
}


