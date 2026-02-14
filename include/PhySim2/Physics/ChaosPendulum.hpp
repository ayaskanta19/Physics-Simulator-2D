#pragma once

#ifndef PHYSIM2_PHYSICS_CHAOSPENDULUM_HPP
#define PHYSIM2_PHYSICS_CHAOSPENDULUM_HPP

#include "MinimalPendulum.hpp"
#include <SFML/System/Time.hpp>
#include <memory>

class ChaosPendulum: public sf::Drawable {
    
    public:
        
        ChaosPendulum(MinimalPendulum::Attributes&, MinimalPendulum::Attributes&);
        
        void simulate(sf::Time);
        void reset(float, float);
        void update(const sf::Vector2f);
        void setColor(sf::Color, sf::Color);
        
    private:
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        MinimalPendulum pendulum_1, pendulum_2; float gravity, damping_coefficient;
        
};

#endif