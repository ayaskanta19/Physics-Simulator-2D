#pragma once

#ifndef PHYSIM2_PHYSICS_MOUSE_HPP
#define PHYSIM2_PHYSICS_MOUSE_HPP

#include <SFML/System/Vector2.hpp>

class Mouse {
    
    public:
        
        Mouse();
        
        void update(sf::Vector2f);
        void setCursorSize(float);
        void setBlastIntensity(float);
        void setLeftButtonPressed(bool);
        void setRightButtonPressed(bool);
        
        bool activeBlastEffect() const;
        bool leftButtonPressed() const;
        bool rightButtonPressed() const;
        
        float getCursorSize() const;
        float getBlastIntensity() const;
        
        const sf::Vector2f getCurrentPosition() const;
        const sf::Vector2f getPreviousPosition() const;
        
    private:
        
        sf::Vector2f previous_position, current_position;
        
        float cursor_size, cursor_min, cursor_max, blast_intensity, blast_min, blast_max; bool left_button, right_button;
        
};

#endif