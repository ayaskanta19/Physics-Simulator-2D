#pragma once

#ifndef PHYSIM2_PHYSICS_POINT_HPP
#define PHYSIM2_PHYSICS_POINT_HPP

#include "Stick.hpp"
#include "Mouse.hpp"
#include <SFML/System/Time.hpp>
#include <array>

class Point {
    
    public:
        
        Point(sf::Vector2f);
        
        void pin();
        void addStick(Stick*, int);
        void setPosition(sf::Vector2f);
        
        void update(sf::Time, sf::Vector2f, const sf::Vector2f, Mouse*, float, float);
        
        const sf::Vector2f getPosition() const;
        
    private:
        
        void restrict(sf::Vector2f);
        
    private:
        
        sf::Vector2f initial_position, previous_position, current_position; float offset; bool pinned, selected;
        
        std::array<Stick*, 2> sticks;
        
};

#endif