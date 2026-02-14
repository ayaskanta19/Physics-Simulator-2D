#pragma once

#ifndef PHYSIM2_PHYSICS_PENDULUM_HPP
#define PHYSIM2_PHYSICS_PENDULUM_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Pendulum: public sf::Drawable {
    
    public:
        
        struct Attributes { float width, length, mass, radius; float alpha, omega, theta; sf::Vector2f position; };
        
        Attributes attributes;
        
    public:
        
        Pendulum(Attributes&);
        void update(const sf::Vector2f, float);
        
    private:
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        sf::CircleShape pendulum_mass; sf::RectangleShape pendulum_rod;
        
};

#endif