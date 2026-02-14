#include "PhySim2/Simulator/TriplePendulumState.hpp"

TriplePendulumState::TriplePendulumState(StateStack &stack, Context context): State(stack, context), window(*context.window), window_center(), fulcrum_position_1(), fulcrum_position_2(), instruction_text(), triple_pendulum(nullptr), mouse_click(0), paused(true) {
    
    window_center = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.43f);
    
    instruction_text.setCharacterSize(10u); instruction_text.setPosition(5.f, 50.f); instruction_text.setFont(*context.text_font);
    
    instruction_text.setString(
        
        "LMB CLICK#1 : ACTIVATE M1\n"
        "LMB CLICK#2 : SET M1 POSITION / ACTIVATE M2\n"
        "LMB CLICK#3 : SET M2 POSITION / ACTIVATE M3\n"
        "LMB CLICK#4 : SET M3 POSITION\n"
        "ENTER : START / PAUSE SIM\n"
        "SPACE : RESET SIM\n"
        "ESC : EXIT SIM"
        
    );
    
    Pendulum::Attributes attributes_1, attributes_2, attributes_3;
    
    attributes_1.width = 3.f; attributes_1.length = 150.f; attributes_1.mass = 10.f; attributes_1.radius = 10.f; attributes_1.alpha = 0.f; attributes_1.omega = 0.f; attributes_1.theta = 0.f; attributes_1.position = sf::Vector2f(0.f, 0.f);
    
    attributes_2.width = 3.f; attributes_2.length = 150.f; attributes_2.mass = 10.f; attributes_2.radius = 10.f; attributes_2.alpha = 0.f; attributes_2.omega = 0.f; attributes_2.theta = 0.f; attributes_2.position = sf::Vector2f(0.f, 0.f);
    
    attributes_3.width = 3.f; attributes_3.length = 150.f; attributes_3.mass = 10.f; attributes_3.radius = 10.f; attributes_3.alpha = 0.f; attributes_3.omega = 0.f; attributes_3.theta = 0.f; attributes_3.position = sf::Vector2f(0.f, 0.f);
    
    triple_pendulum = std::unique_ptr<TriplePendulum>(new TriplePendulum(attributes_1, attributes_2, attributes_3));
    
}

void TriplePendulumState::draw() { window.setView(window.getDefaultView()); window.draw(*triple_pendulum); window.draw(instruction_text); }

bool TriplePendulumState::update(sf::Time deltaTime) { if(!paused) triple_pendulum->simulate(deltaTime * 20.f); triple_pendulum->update(window_center, paused); return true; }

bool TriplePendulumState::handleEvent(const sf::Event &event) {
    
    switch(event.type) {
        
        case sf::Event::KeyPressed:
            
            if(event.key.code == sf::Keyboard::Return) {
                
                if(paused && mouse_click > 0) { paused = false; mouse_click = 7; }
                
                else paused = true;
                
            }
            
            else if(event.key.code == sf::Keyboard::Space) { mouse_click = 0; paused = true; triple_pendulum->reset(); triple_pendulum->update(window_center, paused); }
            
            else if(event.key.code == sf::Keyboard::Escape) { requestStackPop(); requestStackPush(States::Main_Menu); }
            
            break;
            
        case sf::Event::MouseMoved:
            
            if(paused && mouse_click <= 3) {
                
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                
                if(mouse_click == 1) { triple_pendulum->initiate(window_center, mouse_position, mouse_click); fulcrum_position_1 = sf::Vector2f(mouse_position); }
                
                else if(mouse_click == 2) { triple_pendulum->initiate(fulcrum_position_1, mouse_position, mouse_click); fulcrum_position_2 = sf::Vector2f(mouse_position); }
                
                else if(mouse_click == 3) triple_pendulum->initiate(fulcrum_position_2, mouse_position, mouse_click);
                
                triple_pendulum->update(window_center, paused);
                
            }
            
            break;
            
        case sf::Event::MouseButtonPressed: if(event.mouseButton.button == sf::Mouse::Left) mouse_click++; break;
        
    }
    
    return true;
    
}