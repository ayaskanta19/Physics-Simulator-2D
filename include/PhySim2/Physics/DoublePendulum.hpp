#pragma once

#ifndef PHYSIM2_PHYSICS_DOUBLEPENDULUM_HPP
#define PHYSIM2_PHYSICS_DOUBLEPENDULUM_HPP

#include "Pendulum.hpp"
#include <SFML/System/Time.hpp>

class DoublePendulum: public sf::Drawable {
    
    public:
        
        DoublePendulum(Pendulum::Attributes&, Pendulum::Attributes&);
        
        void reset();
        void simulate(sf::Time);
        void update(const sf::Vector2f, bool);
        void initiate(const sf::Vector2f, const sf::Vector2i, int);
        
    private:
        
        void rungeKutta4(sf::Time);
        void explicitEuler(sf::Time);
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        Pendulum pendulum_1, pendulum_2; sf::Color color;
        
        float gravity, damping_coefficient; int trace_count; std::vector<sf::Vector2f> position_trace;
        
};

#endif