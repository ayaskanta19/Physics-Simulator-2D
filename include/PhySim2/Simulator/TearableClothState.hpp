#pragma once

#ifndef PHYSIM2_SIMULATOR_TEARABLECLOTHSTATE_HPP
#define PHYSIM2_SIMULATOR_TEARABLECLOTHSTATE_HPP

#include "PhySim2/Physics/TearableCloth.hpp"
#include "PhySim2/Physics/Mouse.hpp"
#include "PhySim2/Interface/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>

class TearableClothState: public State {
    
    public:
        
        TearableClothState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        void reset();
        
    private:
        
        sf::RenderWindow &window; sf::Vector2f dimensions; std::unique_ptr<TearableCloth> cloth; std::unique_ptr<Mouse> mouse;
        
        bool paused; std::vector<sf::Text> info_texts;
        
};

template<typename T> std::string toString(const T &value) { std::stringstream stream; stream << value; return stream.str(); }

#endif