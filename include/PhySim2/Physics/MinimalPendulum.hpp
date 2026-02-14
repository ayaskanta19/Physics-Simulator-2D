#pragma once

#ifndef PHYSIM2_PHYSICS_MINIMALPENDULUM_HPP
#define PHYSIM2_PHYSICS_MINIMALPENDULUM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MinimalPendulum: public sf::Drawable {
    
    public:
        
        struct Attributes { float width, length, mass; float alpha, omega, theta; sf::Vector2f position; };
        
        Attributes attributes;
        
    public:
        
        MinimalPendulum(Attributes&);
        
        void setColor(sf::Color);
        void update(const sf::Vector2f, float);
        
    private:
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        sf::RectangleShape pendulum_rod;
        
};

#endif