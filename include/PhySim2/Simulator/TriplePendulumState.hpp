#pragma once

#ifndef PHYSIM2_SIMULATOR_TRIPLEPENDULUMSTATE_HPP
#define PHYSIM2_SIMULATOR_TRIPLEPENDULUMSTATE_HPP

#include "PhySim2/Physics/TriplePendulum.hpp"
#include "PhySim2/Interface/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class TriplePendulumState: public State {
    
    public:
        
        TriplePendulumState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        sf::RenderWindow &window; sf::Vector2f window_center, fulcrum_position_1, fulcrum_position_2; sf::Text instruction_text;
        
        std::unique_ptr<TriplePendulum> triple_pendulum; int mouse_click; bool paused;
        
};

#endif