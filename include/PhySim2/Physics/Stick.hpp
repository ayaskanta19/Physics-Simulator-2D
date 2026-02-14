#pragma once

#ifndef PHYSIM2_PHYSICS_STICK_HPP
#define PHYSIM2_PHYSICS_STICK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Point;

class Stick: public sf::Drawable {
    
    public:
        
        Stick(Point&, Point&, float);
        
        void snap();
        void update();
        void setSelection(bool);
        
    private:
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        Point &start_point, &end_point; float length; bool active, selected;
        
        sf::Color default_color, selected_color;
        
};

#endif