#pragma once

#ifndef PHYSIM2_SIMULATOR_APPLICATION_HPP
#define PHYSIM2_SIMULATOR_APPLICATION_HPP

#include "PhySim2/Interface/StateStack.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application {
    
    public:
        
        Application();
        void run();
        
    private:
        
        void render();
        void processInput();
        void registerStates();
        void update(sf::Time);
        void updateStatistics(sf::Time);
        
    private:
        
        static const sf::Time TimePerFrame;
        
        sf::ContextSettings mSettings;
        sf::RenderWindow mWindow;
        sf::Texture mTexture;
        sf::Font mButtonFont, mTextFont;
        
        StateStack mStateStack;
        
        sf::Text mStatisticsText;
        sf::Time mStatisticsUpdateTime;
        
        std::size_t mStatisticsNumFrames;
        
        bool mIsPaused;
        
};

#endif