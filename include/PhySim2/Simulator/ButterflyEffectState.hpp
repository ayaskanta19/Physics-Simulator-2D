#pragma once

#ifndef PHYSIM2_SIMULATOR_BUTTERFLYEFFECTSTATE_HPP
#define PHYSIM2_SIMULATOR_BUTTERFLYEFFECTSTATE_HPP

#include "PhySim2/Physics/ChaosPendulum.hpp"
#include "PhySim2/Interface/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

class ButterflyEffectState: public State {
    
    public:
        
        typedef std::unique_ptr<ChaosPendulum> ChronoScope;
        
    public:
        
        ButterflyEffectState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        void setColor();
        void reset(float, float);
        
        float initiate(const sf::Vector2f, const sf::Vector2i);
        
    private:
        
        sf::RenderWindow &window; sf::Vector2f window_center, fulcrum_position; sf::Text instruction_text;
        
        float theta; int mouse_click; bool paused; std::array<ChronoScope, 10000> double_pendulums;
        
};

#endif