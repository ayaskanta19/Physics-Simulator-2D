#pragma once

#ifndef PHYSIM2_PHYSICS_TEARABLECLOTH_HPP
#define PHYSIM2_PHYSICS_TEARABLECLOTH_HPP

#include "Point.hpp"
#include <vector>
#include <memory>

class TearableCloth: public sf::Drawable {
    
    public:
        
        typedef std::unique_ptr<Point> CrossRoad;
        typedef std::unique_ptr<Stick> AlpenStock;
        
    public:
        
        TearableCloth(sf::Vector2f, sf::Vector2f, float);
        void update(Mouse*, sf::Vector2f, sf::Time);
        
    private:
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        sf::Vector2f gravity; float drag, elasticity;
        
        std::vector<CrossRoad> points; std::vector<AlpenStock> sticks;
        
};

#endif