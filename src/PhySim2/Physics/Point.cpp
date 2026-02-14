#include "PhySim2/Physics/Point.hpp"

Point::Point(sf::Vector2f position): initial_position(position), previous_position(position), current_position(position), offset(2.f), pinned(false), selected(false), sticks() { for(Stick *stick: sticks) stick = nullptr; }

void Point::pin() { pinned = true; }

void Point::addStick(Stick *stick, int stickNum) { sticks[stickNum] = stick; }

void Point::setPosition(sf::Vector2f position) { current_position = position; }

void Point::update(sf::Time deltaTime, sf::Vector2f window_size, const sf::Vector2f acceleration, Mouse *mouse, float drag, float elasticity) {
    
    sf::Vector2f direction = current_position - mouse->getCurrentPosition(); selected = (std::abs(direction.x) < mouse->getCursorSize()) && (std::abs(direction.y) < mouse->getCursorSize());
    
    // float distance = direction.x * direction.x + direction.y * direction.y; selected = distance < mouse->getCursorSize() * mouse->getCursorSize();
    
    for(Stick *stick: sticks) if(stick) stick->setSelection(selected);
    
    if(mouse->leftButtonPressed() && selected) {
        
        if(mouse->activeBlastEffect()) {
            
            float blast_intensity = mouse->getBlastIntensity();
            
            if(blast_intensity < 0.f) previous_position = current_position - sf::Vector2f(elasticity, elasticity) * blast_intensity; else previous_position = current_position - sf::Vector2f(elasticity, -elasticity) * blast_intensity;
            
        }
        
        else {
            
            direction = mouse->getCurrentPosition() - mouse->getPreviousPosition();
            
            if(direction.x > elasticity) direction.x = elasticity; if(direction.y > elasticity) direction.y = elasticity; if(direction.x < -elasticity) direction.x = -elasticity; if(direction.y < -elasticity) direction.y = -elasticity;
            
            previous_position = current_position - direction;
            
        }
        
    }
    
    if(mouse->rightButtonPressed() && selected) for(Stick *stick: sticks) if(stick) stick->snap(); if(pinned) { current_position = initial_position; return; }
    
    sf::Vector2f position = current_position + (current_position - previous_position) * (1.f - drag) + acceleration * (1.f - drag) * deltaTime.asSeconds() * deltaTime.asSeconds();
    
    previous_position = current_position; current_position = position; restrict(window_size);
    
}

const sf::Vector2f Point::getPosition() const { return current_position; }

void Point::restrict(sf::Vector2f window_size) {
    
    if(current_position.x > window_size.x) { current_position.x = window_size.x; previous_position.x = current_position.x + offset; }
    
    else if(current_position.x < 0.f) { current_position.x = 0.f; previous_position.x = current_position.x - offset; }
    
    if(current_position.y > window_size.y) { current_position.y = window_size.y; previous_position.y = current_position.y + offset; }
    
    else if(current_position.y < 0.f) { current_position.y = 0.f; previous_position.y = current_position.y - offset; }
    
}