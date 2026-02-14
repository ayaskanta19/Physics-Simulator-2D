#pragma once

#ifndef PHYSIM2_SIMULATOR_ELLIPTICALBILLIARDSSTATE_HPP
#define PHYSIM2_SIMULATOR_ELLIPTICALBILLIARDSSTATE_HPP

#include "PhySim2/Physics/EllipticalBilliards.hpp"
#include "PhySim2/Interface/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class EllipticalBilliardsState: public State {
    
    public:
        
        EllipticalBilliardsState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        sf::RenderWindow &window; sf::Vector2f window_center, position_1, position_2; sf::Text instructions_1, instructions_2;
        
        std::unique_ptr<EllipticalBilliards> billiards_1, billiards_2; int mouse_click; bool paused, mouse_moved;
        
};

#endif