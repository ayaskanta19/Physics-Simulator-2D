#include "PhySim2/Simulator/DoublePendulumState.hpp"

DoublePendulumState::DoublePendulumState(StateStack &stack, Context context): State(stack, context), window(*context.window), window_center(), fulcrum_position(), instruction_text(), double_pendulum(nullptr), mouse_click(0), paused(true) {
    
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
    
    Pendulum::Attributes attributes_1, attributes_2;
    
    attributes_1.width = 3.f; attributes_1.length = 150.f; attributes_1.mass = 10.f; attributes_1.radius = 10.f; attributes_1.alpha = 0.f; attributes_1.omega = 0.f; attributes_1.theta = 0.f; attributes_1.position = sf::Vector2f(0.f, 0.f);
    
    attributes_2.width = 3.f; attributes_2.length = 150.f; attributes_2.mass = 10.f; attributes_2.radius = 10.f; attributes_2.alpha = 0.f; attributes_2.omega = 0.f; attributes_2.theta = 0.f; attributes_2.position = sf::Vector2f(0.f, 0.f);
    
    double_pendulum = std::unique_ptr<DoublePendulum>(new DoublePendulum(attributes_1, attributes_2));
    
}

void DoublePendulumState::draw() { window.setView(window.getDefaultView()); window.draw(*double_pendulum); window.draw(instruction_text); }

bool DoublePendulumState::update(sf::Time deltaTime) { if(!paused) double_pendulum->simulate(deltaTime * 20.f); double_pendulum->update(window_center, paused); return true; }

bool DoublePendulumState::handleEvent(const sf::Event &event) {
    
    switch(event.type) {
        
        case sf::Event::KeyPressed:
            
            if(event.key.code == sf::Keyboard::Return) {
                
                if(paused && mouse_click > 0) { paused = false; mouse_click = 5; }
                
                else paused = true;
                
            }
            
            else if(event.key.code == sf::Keyboard::Space) { mouse_click = 0; paused = true; double_pendulum->reset(); double_pendulum->update(window_center, paused); }
            
            else if(event.key.code == sf::Keyboard::Escape) { requestStackPop(); requestStackPush(States::Main_Menu); }
            
            break;
            
        case sf::Event::MouseMoved:
            
            if(paused && mouse_click <= 2) {
                
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                
                if(mouse_click == 1) { double_pendulum->initiate(window_center, mouse_position, mouse_click); fulcrum_position = sf::Vector2f(mouse_position); }
                
                else if(mouse_click == 2) double_pendulum->initiate(fulcrum_position, mouse_position, mouse_click);
                
                double_pendulum->update(window_center, paused);
                
            }
            
            break;
            
        case sf::Event::MouseButtonPressed: if(event.mouseButton.button == sf::Mouse::Left) mouse_click++; break;
        
    }
    
    return true;
    
}