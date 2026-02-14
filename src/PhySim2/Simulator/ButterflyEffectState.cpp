#include "PhySim2/Simulator/ButterflyEffectState.hpp"
#include <cmath>

ButterflyEffectState::ButterflyEffectState(StateStack &stack, Context context): State(stack, context), window(*context.window), window_center(), fulcrum_position(), instruction_text(), theta(0.f), mouse_click(0), paused(true), double_pendulums() {
    
    window_center = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.4f);
    
    instruction_text.setCharacterSize(10u); instruction_text.setPosition(5.f, 50.f); instruction_text.setFont(*context.text_font);
    
    instruction_text.setString(
        
        "LMB CLICK#1 : ACTIVATE M1\n"
        "LMB CLICK#2 : SET M1 POSITION / ACTIVATE M2\n"
        "LMB CLICK#3 : SET M2 POSITION\n"
        "ENTER : START / PAUSE SIM\n"
        "SPACE : RESET SIM\n"
        "ESC : EXIT SIM"
        
    );
    
    MinimalPendulum::Attributes attributes_1, attributes_2;
    
    attributes_1.width = 3.f; attributes_1.length = 150.f; attributes_1.mass = 10.f; attributes_1.alpha = 0.f; attributes_1.omega = 0.f; attributes_1.theta = 0.f; attributes_1.position = sf::Vector2f(0.f, 0.f);
    
    attributes_2.width = 3.f; attributes_2.length = 150.f; attributes_2.mass = 10.f; attributes_2.alpha = 0.f; attributes_2.omega = 0.f; attributes_2.theta = 0.f; attributes_2.position = sf::Vector2f(0.f, 0.f);
    
    for(std::size_t i = 0; i < double_pendulums.size(); i++) { double_pendulums[i] = ChronoScope(new ChaosPendulum(attributes_1, attributes_2)); double_pendulums[i]->update(window_center); attributes_2.theta += 0.000001; }
    
    setColor();
    
}

void ButterflyEffectState::draw() { window.setView(window.getDefaultView()); for(std::size_t i = 0; i < double_pendulums.size(); i++) window.draw(*double_pendulums[i]); window.draw(instruction_text); }

bool ButterflyEffectState::update(sf::Time deltaTime) {
    
    for(std::size_t i = 0; i < double_pendulums.size(); i++) { if(!paused) double_pendulums[i]->simulate(deltaTime * 20.f); double_pendulums[i]->update(window_center); }
    
    return true;
    
}

bool ButterflyEffectState::handleEvent(const sf::Event &event) {
    
    switch(event.type) {
        
        case sf::Event::KeyPressed:
            
            if(event.key.code == sf::Keyboard::Return) {
                
                if(paused && mouse_click > 0) { paused = false; mouse_click = 5; }
                
                else paused = true;
                
            }
            
            else if(event.key.code == sf::Keyboard::Space) { reset(0.f, 0.f); setColor(); mouse_click = 0; paused = true; }
            
            else if(event.key.code == sf::Keyboard::Escape) { requestStackPop(); requestStackPush(States::Main_Menu); }
            
            break;
            
        case sf::Event::MouseMoved:
            
            if(paused && mouse_click <= 2) {
                
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                
                if(mouse_click == 1) { theta = initiate(window_center, mouse_position); reset(theta, 0.f); fulcrum_position = sf::Vector2f(mouse_position); }
                
                else if(mouse_click == 2) reset(theta, initiate(fulcrum_position, mouse_position));
                
            }
            
            break;
            
        case sf::Event::MouseButtonPressed: if(event.mouseButton.button == sf::Mouse::Left) mouse_click++; break;
        
    }
    
    return true;
    
}

void ButterflyEffectState::setColor() { float red = rand() % 256, green = rand() % 256, blue = rand() % 256; sf::Color color(red, green, blue, 7); for(std::size_t i = 0; i < double_pendulums.size(); i++) double_pendulums[i]->setColor(color, color); }

void ButterflyEffectState::reset(float theta_1, float theta_2) { for(std::size_t i = 0; i < double_pendulums.size(); i++) { double_pendulums[i]->reset(theta_1, theta_2); double_pendulums[i]->update(window_center); theta_2 += 0.000001; } }

float ButterflyEffectState::initiate(const sf::Vector2f fulcrum_position, const sf::Vector2i mouse_position) { return std::atan2((mouse_position.x - fulcrum_position.x), (mouse_position.y - fulcrum_position.y)); }