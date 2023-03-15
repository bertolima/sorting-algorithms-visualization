#include "Screen.hpp"

//control variables
void Screen::initVariables(){
    this->window = nullptr;
    this->clock = new sf::Clock;
    this->font.loadFromFile("./include/fonts/The Hoca.ttf");

    this->runningSort = true;

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
    this->buttons["QuickSort"] = new Button(this->window->getSize().x/2.f - 75.f, 50, 150, 50,
    &this->font, "QuickSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["BubbleSort"] = new Button(this->window->getSize().x/2.f - 75.f, 150, 150, 50,
    &this->font, "BubbleSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    
    this->buttons["MergeSort"] = new Button(this->window->getSize().x/2.f - 75.f, 250, 150, 50,
    &this->font, "MergeSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["SelectionSort"] = new Button(this->window->getSize().x/2.f - 75.f, 350, 150, 50,
    &this->font, "SelectionSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["HeapSort"] = new Button(this->window->getSize().x/2.f - 75.f, 450, 150, 50,
    &this->font, "HeapSort",
     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->control_buttons["RETURN"] = new Button(20.f, 20.f, 150, 50,
    &this->font, "Return",
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
                this->runningSort = false;
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    window->close();
                    this->runningSort = false;
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
        this->vector->update();
            for(int l=0;l<this->vector->getSize();l++){
                    this->window->draw(this->vector->getElement(l));
            }                     
            break;
        case STATE_QUICK:
            this->QuickSort(*this->vector,0 , static_cast<int>(this->vector->getSize()-1));
            this->sort_state = STATE_NONE;
            break;
        case STATE_BUBBLE:
            this->BubbleSort(*this->vector, static_cast<int>(this->vector->getSize()-1));
            this->sort_state = STATE_NONE;
            break;
        case STATE_MERGE:
            this->MergeSort(*this->vector,0 , static_cast<int>(this->vector->getSize()-1));
            this->sort_state = STATE_NONE;
            break;
        case STATE_SELECTION:
            this->SelectionSort(*this->vector, static_cast<int>(this->vector->getSize()-1));
            this->sort_state = STATE_NONE;
            break;
        case STATE_HEAP:
            this->HeapSort(*this->vector, static_cast<int>(this->vector->getSize()));
            this->sort_state = STATE_NONE;
            break;
    }  
}

void Screen::updateButtons(){
    for (auto &it : this->buttons){
        it.second->update(this->mousePosFloat);
    }

    for (auto &it : this->control_buttons){
        it.second->update(this->mousePosFloat);
    }

    if(this->buttons["QuickSort"]->isPressed()){
        this->sort_state = STATE_QUICK;
    }
    if(this->buttons["BubbleSort"]->isPressed()){
        this->sort_state = STATE_BUBBLE;
    }

    if(this->buttons["MergeSort"]->isPressed()){
        this->sort_state = STATE_MERGE;
    }

    if(this->buttons["SelectionSort"]->isPressed()){
        this->sort_state = STATE_SELECTION;
    }

    if(this->buttons["HeapSort"]->isPressed()){
        this->sort_state = STATE_HEAP;
    }

    if(this->control_buttons["RETURN"]->isPressed()){
        this->sort_state = STATE_ZERO;
        this->vector->reInit();
        this->initVector();
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
    std::cout << this->vector->isOrdered() << std::endl;
    if (this->sort_state == STATE_NONE && this->vector->isOrdered() == true){
        for (auto &it : this->control_buttons){
            it.second->render(this->window);
        }
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
    bool ver = false;   
    if (v.isOrdered() == true)
        ver = true;
        while (ver == false){
            this->pollEvent();
            if (this->clock->getElapsedTime().asMilliseconds() > 10.f){
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
                this->clock->restart();
                ver = true;
                v.setColor(i+1, 0);
                v.setColor(high, 0);
                return i+1;
            }
        }
    return -1;
}

void Screen::QuickSort(Vector &v, int low, int high){
    if (this->runningSort == true){
        if (v.isOrdered() == false){
            if (low < high){
                int p = Partition(v,low, high);
                if (p != -1){
                    QuickSort(v, low, p-1);
                    QuickSort(v, p+1, high);
                }
            }
        }
    }
}

void Screen::BubbleSort(Vector &v, int size){
    for (int i = 0; i < size;i++){
        if (this->vector->isOrdered() == true)
            break;
        if (this->runningSort == false)
            break;
        for (int j = 0; j < size-i;j++){
            if (this->runningSort == false)
                break;
            bool ver = false;
            if (this->vector->isOrdered() == true)
                break;
            while (ver == false){
                this->pollEvent();
                
                std::cout << this->vector->isOrdered() << std::endl;
                if (this->clock->getElapsedTime().asMicroseconds() > 10.f){
                        v.setColor(j, 1);
                        v.setColor(j+1, 1);
                        this->vector->update();
                        this->render();
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

void Screen::Merge(Vector& v, int left, int mid, int right){
    if (this->runningSort == true){
                
        if (v.isOrdered() == false){
            bool ver = false;
            while (ver == false){
                this->pollEvent();
                if (this->clock->getElapsedTime().asMilliseconds() > 100.f){

                    std::vector<sf::RectangleShape> vectorLeft;
                    std::vector<sf::RectangleShape> vectorRight;

                    auto const leftVector = mid - left + 1;
                    auto const rightVector = right - mid;

                    for (int i = 0; i < leftVector; i++){
                        vectorLeft.push_back(v.getElement(left + i));
                    }

                    for (int j = 0; j <rightVector; j++){
                        vectorRight.push_back(v.getElement(mid + 1 + j));
                    }

                    int i=0, j=0, k = left;

                    while(i < leftVector && j < rightVector){
                        if(vectorLeft[i].getSize().y <= vectorRight[j].getSize().y){
                            v.setElement(k, vectorLeft[i]);
                            i++;
                        }
                        else {
                            v.setElement(k, vectorRight[j]);
                            j++;
                            
                        }
                        v.setColor(k, 2);
                        k++;

                    }
                    

                    while (i < leftVector){
                        v.setElement(k, vectorLeft[i]);
                        i++;
                        k++;
                    }

                    while (j<rightVector){
                        v.setElement(k, vectorRight[j]);
                        j++;
                        v.setColor(k, 2);
                        k++;
                        
                    }
                    this->vector->update();
                    this->render();
                    for(int l=0;l<v.getSize();l++){
                            this->window->draw(v.getElement(l));
                    }
                    ver = true;
                    this->clock->restart();
                }
            }
        }
    }
}

void Screen::MergeSort(Vector& v, int left ,int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        MergeSort(v, left, mid);
        MergeSort(v, mid+1, right);
        Merge(v, left, mid, right);
    }

}

void Screen::SelectionSort(Vector&v , int size){

    int min;
    for (int i=0;i<size;i++){
        if (this->runningSort == false)
                break;
        min = i;
        for (int j=i+1;j<size+1;j++){
            if (this->runningSort == false)
                break;
            bool ver = false;
            while (ver == false){
                this->pollEvent();
                if (this->clock->getElapsedTime().asMicroseconds() > 500.f){
                        
                        v.setColor(i, 1);
                        if (v.getElement(j).getSize().y < v.getElement(min).getSize().y)
                            min = j;
                            v.setColor(j, 1);
                        this->vector->update();
                        this->render();
                        for(int l=0;l<v.getSize();l++){
                            this->window->draw(v.getElement(l));
                        }
                        v.setColor(i, 0);
                        v.setColor(j, 0);
                        this->clock->restart();
                        ver = true;
                }
            }
        }
        if (min != i)
            v.swap(min, i);
    }

}

void Screen::Heapify(Vector& v, int size, int i){
        bool ver = false;
        while (ver == false){
            this->pollEvent();
            if (this->clock->getElapsedTime().asMilliseconds() > 10.f){
                
                
                ver = true;
                this->clock->restart();
                int largest = i;

                int left = 2*i +1;
                int right = 2*i +2;

                if (left < size && v.getElement(left).getSize().y > v.getElement(largest).getSize().y)
                    largest = left;
                if (right < size && v.getElement(right).getSize().y > v.getElement(largest).getSize().y)
                    largest = right;
                v.setColor(largest, 1);
                v.setColor(i, 1);
                if (largest != i){
                    v.swap(i, largest);
                    Heapify(v, size, largest);
                }
                

                this->vector->update();
                this->render();
                v.setColor(i, 0);
                v.setColor(largest, 0);
            }
        }
}

void Screen::HeapSort(Vector&v, int size){
    for (int i = size/2-1;i>=0;i--){
        if (this->runningSort == false)
            break;
        Heapify(v, size, i);
    }

    for (int i = size -1;i>0;i--){
        if (this->runningSort == false)
            break;
        v.swap(0, i);
        Heapify(v, i, 0);
    }
}


