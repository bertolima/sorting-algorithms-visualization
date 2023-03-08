#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum button_states{BTN_IDLE = 0, BNT_HOVER , BNT_ACTIVE};

class Button{
    private:
        short unsigned button_state;

        sf::RectangleShape shape;
        sf::Text text;
        sf::Font* font;

        sf::Color idle;
        sf::Color hover;
        sf::Color active;

    public:
        //cons and des
        Button(float x, float y, float width, float height,
        sf::Font* font, std::string text,
        sf::Color idle, sf::Color hover, sf::Color active);
        ~Button();

        //access
        const bool isPressed() const;

        //functions
        void update(const sf::Vector2f mousePos);
        void render(sf::RenderTarget* target);
        void setPosition(float x, float y);
        float getGlobalBounds();
};