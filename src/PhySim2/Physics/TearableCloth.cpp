#include "PhySim2/Physics/TearableCloth.hpp"

TearableCloth::TearableCloth(sf::Vector2f cloth_size, sf::Vector2f point_fix, float length): gravity(sf::Vector2f(0.f, 981.f)), drag(0.01f), elasticity(20.f), points(), sticks() {
    
    for(std::size_t y = 0; y <= cloth_size.y; y++)
        
        for(std::size_t x = 0; x <= cloth_size.x; x++) {
            
            CrossRoad start_point = CrossRoad(new Point(point_fix + sf::Vector2f(x, y) * length));
            
            if(x != 0) { CrossRoad &end_point = points.back(); AlpenStock stick = AlpenStock(new Stick(*start_point, *end_point, length)); start_point->addStick(stick.get(), 0); end_point->addStick(stick.get(), 0); sticks.push_back(std::move(stick)); }
            
            if(y != 0) { CrossRoad &end_point = points[x + (y - 1) * (cloth_size.x + 1)]; AlpenStock stick = AlpenStock(new Stick(*start_point, *end_point, length)); start_point->addStick(stick.get(), 1); end_point->addStick(stick.get(), 1); sticks.push_back(std::move(stick)); }
            
            if(y == 0 && x % 2 == 0) start_point->pin(); points.push_back(std::move(start_point));
            
        }
        
}

void TearableCloth::update(Mouse *mouse, sf::Vector2f window_size, sf::Time deltaTime) { for(CrossRoad &point: points) point->update(deltaTime, window_size, gravity, mouse, drag, elasticity); for(AlpenStock &stick: sticks) stick->update(); }

void TearableCloth::draw(sf::RenderTarget &target, sf::RenderStates states) const { for(const AlpenStock &stick: sticks) target.draw(*stick); }