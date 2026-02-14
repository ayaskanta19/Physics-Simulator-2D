#pragma once

#ifndef PHYSIM2_PHYSICS_ELLIPTICALBILLIARDS_HPP
#define PHYSIM2_PHYSICS_ELLIPTICALBILLIARDS_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

struct Line { float slope, intercept; };

class EllipticalBilliards: public sf::Drawable {
    
    public:
        
        typedef std::unique_ptr<Line> Solidus;
        
    public:
        
        struct Attributes { float semi_majoris, semi_minoris, radius, velocity; std::size_t point_count; sf::Vector2f center; sf::Color color; };
        
        Attributes attributes;
        
    public:
        
        EllipticalBilliards(Attributes&);
        
        void reset();
        void simulate(sf::Time);
        void position(sf::Vector2f);
        void initiate(sf::Vector2f, sf::Vector2f);
        
        bool contains(sf::Vector2i);
        
        sf::Vector2f getFocus(int);
        
    private:
        
        std::size_t closestPoint();
        sf::Vector2f unitVector(sf::Vector2f);
        
        float distance(sf::Vector2f, sf::Vector2f);
        
        void draw(sf::RenderTarget&, sf::RenderStates) const;
        
    private:
        
        Solidus trajectory, normal;
        
        sf::ConvexShape ellipse; sf::CircleShape billiard, focus_1, focus_2; sf::Vector2f start_point, end_point, unit_vector;
        
        std::vector<sf::Vector2f> position_trace;
        
};

#endif