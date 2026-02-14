#include "PhySim2/Simulator/TearableClothState.hpp"

TearableClothState::TearableClothState(StateStack &stack, Context context): State(stack, context), window(*context.window), dimensions(), cloth(nullptr), mouse(nullptr), paused(true), info_texts() {
    
    dimensions = sf::Vector2f(window.getSize().x, window.getSize().y); for(int i = 1; i <= 5; i++) { sf::Text text("", *context.text_font, 10u); info_texts.push_back(text); }
    
    info_texts[0].setPosition(5.f, 5.f); info_texts[1].setPosition(5.f, 40.f); info_texts[2].setPosition(5.f, 70.f); info_texts[3].setPosition(5.f, 215.f); info_texts[4].setPosition(5.f, 1065.f);
    
    info_texts[2].setString(
        
        "LMB : GRAZE CLOTH / BLAST AIR\n"
        "RMB : TEAR CLOTH\n"
        "SCROLL UP : INCREASE SELECTION AREA\n"
        "SCROLL DOWN : DECREASE SELECTION AREA\n"
        "LEFT ARROW (<-) : INCREASE LEFT BLAST INTENSITY\n"
        "RIGHT ARROW (->) : INCREASE RIGHT BLAST INTENSITY\n"
        "ENTER : START / PAUSE SIM\n"
        "SPACE : RESET SIM\n"
        "ESC : EXIT SIM"
        
    );
    
    info_texts[3].setString(
        
        "[WINDBLOWER EFFECT]\n"
        "1. INCREASE SELECTION AREA\n"
        "2. PRESS AND HOLD <LMB>\n"
        "3. SWIPE CLOTH TOWARDS BLAST DIRECTION"
        
    );
    
    info_texts[4].setString("SET BLAST INTENSITY = 0 TO ACTIVATE <GRAZE CLOTH> FUNCTION"); reset();
    
}

void TearableClothState::draw() { window.setView(window.getDefaultView()); window.draw(*cloth); for(sf::Text &text: info_texts) window.draw(text); }

bool TearableClothState::update(sf::Time deltaTime) { if(!paused) cloth->update(mouse.get(), dimensions, deltaTime); return true; }

bool TearableClothState::handleEvent(const sf::Event &event) {
    
    switch(event.type) {
        
        case sf::Event::KeyPressed:
            
            if(event.key.code == sf::Keyboard::Return) { if(paused) paused = false; else paused = true; }
            
            else if(event.key.code == sf::Keyboard::Space) { reset(); paused = true; }
            
            else if(event.key.code == sf::Keyboard::Left) { mouse->setBlastIntensity(-0.5f); info_texts[1].setString("Blast Intensity = " + toString(mouse->getBlastIntensity())); }
            
            else if(event.key.code == sf::Keyboard::Right) { mouse->setBlastIntensity(0.5f); info_texts[1].setString("Blast Intensity = " + toString(mouse->getBlastIntensity())); }
            
            else if(event.key.code == sf::Keyboard::Escape) { requestStackPop(); requestStackPush(States::Main_Menu); }
            
            break;
            
        case sf::Event::MouseMoved: mouse->update(sf::Vector2f(sf::Mouse::getPosition(window))); break;
            
        case sf::Event::MouseButtonPressed:
            
            mouse->update(sf::Vector2f(sf::Mouse::getPosition(window)));
            
            if(!mouse->leftButtonPressed() && event.mouseButton.button == sf::Mouse::Left) mouse->setLeftButtonPressed(true);
            
            else if(!mouse->rightButtonPressed() && event.mouseButton.button == sf::Mouse::Right) mouse->setRightButtonPressed(true);
            
            break;
            
        case sf::Event::MouseButtonReleased:
            
            if(mouse->leftButtonPressed() && event.mouseButton.button == sf::Mouse::Left) mouse->setLeftButtonPressed(false);
            
            else if(mouse->rightButtonPressed() && event.mouseButton.button == sf::Mouse::Right) mouse->setRightButtonPressed(false);
            
            break;
            
        case sf::Event::MouseWheelScrolled: if(event.mouseWheelScroll.delta > 0.f) mouse->setCursorSize(10.f); else if(event.mouseWheelScroll.delta < 0.f) mouse->setCursorSize(-10.f); break;
        
    }
    
    return true;
    
}

void TearableClothState::reset() {
    
    sf::Vector2f cloth_size = sf::Vector2f(140.f, 50.f); float length = 10.f; sf::Vector2f point_fix = sf::Vector2f((dimensions.x * 0.59f) - (cloth_size.x * length * 0.5f), dimensions.y * 0.04f);
    
    cloth = std::unique_ptr<TearableCloth>(new TearableCloth(cloth_size, point_fix, length)); mouse = std::unique_ptr<Mouse>(new Mouse()); info_texts[1].setString("Blast Intensity = " + toString(mouse->getBlastIntensity()));
    
}