#pragma once

#ifndef PHYSIM2_SIMULATOR_MAINMENUSTATE_HPP
#define PHYSIM2_SIMULATOR_MAINMENUSTATE_HPP

#include "PhySim2/Interface/State.hpp"
#include "PhySim2/Interface/Container.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MainMenuState: public State {
    
    public:
        
        MainMenuState(StateStack&, Context);
        
        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event&);
        
    private:
        
        sf::Sprite mBackgroundSprite; sf::Text mDisplayText, mCaptionText; GUI::Container mGUIContainer;
        
};

#endif