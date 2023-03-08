#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
        sf::Font* font, std::string text,
        sf::Color idle, sf::Color hover, sf::Color active){

    this->button_state = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(15.f);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height/2.f) - this->text.getGlobalBounds().height/2.f
    );

    this->idle = idle;
    this->hover = hover;
    this->active = active;

    this->shape.setFillColor(this->idle);
}

Button::~Button(){
}

const bool Button::isPressed() const{
    if (this->button_state == BNT_ACTIVE)
        return true;
    return false;
}

void Button::update(const sf::Vector2f mousePos){
    this->button_state = BTN_IDLE;
    
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->button_state = BNT_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->button_state = BNT_ACTIVE;
        }
    }

    switch(button_state){
        case BTN_IDLE:
            this->shape.setFillColor(this->idle);
            break;
        case BNT_HOVER:
            this->shape.setFillColor(this->hover);
            break;
        case BNT_ACTIVE:
            this->shape.setFillColor(this->active);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }
}

void Button::render(sf::RenderTarget* target){
    target->draw(this->shape);
    target->draw(this->text);
}

void Button::setPosition(float x, float y){
    this->shape.setPosition(sf::Vector2f(x, y));
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height/2.f) - this->text.getGlobalBounds().height/2.f
    );
}

float Button::getGlobalBounds(){
    return this->shape.getGlobalBounds().width;
}