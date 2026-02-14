#pragma once

#ifndef PHYSIM2_SIMULATOR_DOUBLEPENDULUMSTATE_HPP
#define PHYSIM2_SIMULATOR_DOUBLEPENDULUMSTATE_HPP

#include "PhySim2/Physics/DoublePendulum.hpp"
#include "PhySim2/Interface/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class DoublePendulumState: public State {
    
    public:
        
        DoublePendulumState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        sf::RenderWindow &window; sf::Vector2f window_center, fulcrum_position; sf::Text instruction_text;
        
        std::unique_ptr<DoublePendulum> double_pendulum; int mouse_click; bool paused;
        
};

#endif