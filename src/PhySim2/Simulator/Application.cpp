#include "PhySim2/Simulator/Application.hpp"
#include "PhySim2/Simulator/MainMenuState.hpp"
#include "PhySim2/Simulator/DoublePendulumState.hpp"
#include "PhySim2/Simulator/TriplePendulumState.hpp"
#include "PhySim2/Simulator/ButterflyEffectState.hpp"
#include "PhySim2/Simulator/EllipticalBilliardsState.hpp"
#include "PhySim2/Simulator/TearableClothState.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application(): mSettings(), mWindow(), mTexture(), mButtonFont(), mTextFont(), mStateStack(State::Context(mWindow, mTexture, mButtonFont, mTextFont)), mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0) {
    
    mSettings.antialiasingLevel = 16; mWindow.create(sf::VideoMode(1920, 1080), "PhySim2", sf::Style::Fullscreen, mSettings);
    
    mTexture.loadFromFile(".\\files\\textures\\Background.png");
    
    mButtonFont.loadFromFile(".\\files\\fonts\\kenvector_future_thin.ttf"); mTextFont.loadFromFile(".\\files\\fonts\\arial-black.ttf");
    
    mWindow.setVerticalSyncEnabled(true); mWindow.setKeyRepeatEnabled(false);
    
    mStatisticsText.setFont(mTextFont); mStatisticsText.setPosition(5.f, 5.f); mStatisticsText.setCharacterSize(10u);
    
    mIsPaused = false; registerStates(); mStateStack.pushState(States::Main_Menu);
    
}

void Application::run() {
    
    sf::Clock clock; sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while(mWindow.isOpen()) {
        
        sf::Time elapsedTime = clock.restart(); timeSinceLastUpdate += elapsedTime;
        
        while(timeSinceLastUpdate > TimePerFrame) { processInput(); if(!mIsPaused) update(TimePerFrame); if(mStateStack.isEmpty()) mWindow.close(); timeSinceLastUpdate -= TimePerFrame; }
        
        updateStatistics(elapsedTime); render();
        
    }
    
}

void Application::render() { mWindow.clear(); mStateStack.draw(); mWindow.setView(mWindow.getDefaultView()); mWindow.draw(mStatisticsText); mWindow.display(); }

void Application::processInput() {
    
    sf::Event event;
    
    while(mWindow.pollEvent(event)) {
        
        mStateStack.handleEvent(event);
        
        switch(event.type) {
            
            case sf::Event::GainedFocus: mIsPaused = false; break;
            
            case sf::Event::LostFocus: mIsPaused = true; break;
            
            case sf::Event::Closed: mWindow.close(); break;
            
        }
        
    }
    
}

void Application::registerStates() {
    
    mStateStack.registerState<MainMenuState>(States::Main_Menu);
    mStateStack.registerState<DoublePendulumState>(States::Double_Pendulum);
    mStateStack.registerState<TriplePendulumState>(States::Triple_Pendulum);
    mStateStack.registerState<ButterflyEffectState>(States::Butterfly_Effect);
    mStateStack.registerState<EllipticalBilliardsState>(States::Elliptical_Billiards);
    mStateStack.registerState<TearableClothState>(States::Tearable_Cloth);
    
}

void Application::update(sf::Time deltaTime) { mStateStack.update(deltaTime); }

void Application::updateStatistics(sf::Time elapsedTime) {
    
    mStatisticsUpdateTime += elapsedTime; mStatisticsNumFrames++;
    
    if(mStatisticsUpdateTime >= sf::seconds(1.f)) {
        
        mStatisticsText.setString("Frames / Second = " + std::to_string(mStatisticsNumFrames) + " fps" + "\nTime / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + " us");
        
        mStatisticsUpdateTime -= sf::seconds(1.f); mStatisticsNumFrames = 0;
        
    }
    
}