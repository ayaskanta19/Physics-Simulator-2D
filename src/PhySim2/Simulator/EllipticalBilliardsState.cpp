#include "PhySim2/Simulator/EllipticalBilliardsState.hpp"

EllipticalBilliardsState::EllipticalBilliardsState(StateStack &stack, Context context): State(stack, context), window(*context.window), window_center(), position_1(), position_2(), instructions_1(), instructions_2(), billiards_1(nullptr), billiards_2(nullptr), mouse_click(0), paused(true), mouse_moved(true) {
    
    window_center = sf::Vector2f(window.getSize().x, window.getSize().y) / 2.f;
    
    instructions_1.setCharacterSize(10u); instructions_1.setPosition(5.f, 50.f); instructions_1.setFont(*context.text_font); instructions_2.setCharacterSize(10u); instructions_2.setPosition(5.f, 1035.f); instructions_2.setFont(*context.text_font);
    
    instructions_1.setString(
        
        "LMB CLICK#1 : ACTIVATE B1\n"
        "LMB CLICK#2 : SET B1 POSITION\n"
        "LMB CLICK#3 : SET B1 DIRECTION VECTOR\n"
        "LMB CLICK#4 : ACTIVATE B2\n"
        "LMB CLICK#5 : SET B2 POSITION\n"
        "LMB CLICK#6 : SET B2 DIRECTION VECTOR\n"
        "LEFT ARROW (<-) : SET B1 POSITION AT F1\n"
        "RIGHT ARROW (->) : SET B1 POSITION AT F2\n"
        "NUMPAD(+) : ADD B2 INTO SIM\n"
        "NUMPAD(-) : REMOVE B2 FROM SIM\n"
        "ENTER : START / PAUSE SIM\n"
        "SPACE : RESET SIM\n"
        "ESC : EXIT SIM"
        
    );
    
    instructions_2.setString(
        
        "PAUSE / RESET SIM TO ACTIVATE BILLIARD CONTROLS\n"
        "KEEP MOUSE POINTER INSIDE ELLIPSE WHILE PAUSED TO ACTIVATE MOUSE CONTROLS\n"
        "KEEP MOUSE POINTER INSIDE ELLIPSE WHILE PAUSED TO ACTIVATE <START SIM> FUNCTION"
        
    );
    
    EllipticalBilliards::Attributes attributes; attributes.semi_majoris = 700.f; attributes.semi_minoris = 500.f; attributes.radius = 5.f; attributes.velocity = 10.f; attributes.point_count = 3600; attributes.center = window_center; attributes.color = sf::Color(255, 70, 125);
    
    billiards_1 = std::unique_ptr<EllipticalBilliards>(new EllipticalBilliards(attributes));
    
}

void EllipticalBilliardsState::draw() { window.setView(window.getDefaultView()); if(billiards_2) window.draw(*billiards_2); window.draw(*billiards_1); window.draw(instructions_1); window.draw(instructions_2); }

bool EllipticalBilliardsState::update(sf::Time deltaTime) {
    
    if(!paused) { billiards_1->simulate(deltaTime * 60.f); if(billiards_2) billiards_2->simulate(deltaTime * 60.f); }
    
    return true;
    
}

bool EllipticalBilliardsState::handleEvent(const sf::Event &event) {
    
    switch(event.type) {
        
        case sf::Event::KeyPressed:
            
            if(event.key.code == sf::Keyboard::Add) {
                
                if(paused) {
                    
                    EllipticalBilliards::Attributes attributes; attributes.semi_majoris = 700.f; attributes.semi_minoris = 500.f; attributes.radius = 5.f; attributes.velocity = 10.f; attributes.point_count = 3600; attributes.center = window_center; attributes.color = sf::Color(40, 255, 255);
                    
                    billiards_2 = std::unique_ptr<EllipticalBilliards>(new EllipticalBilliards(attributes)); if(mouse_click > 3) mouse_click = 3;
                    
                }
                
            }
            
            else if(event.key.code == sf::Keyboard::Subtract) { if(paused) billiards_2 = nullptr; }
            
            else if(event.key.code == sf::Keyboard::Left) { if(paused) { billiards_2 = nullptr; billiards_1->reset(); position_1 = billiards_1->getFocus(1); position_2 = sf::Vector2f(sf::Mouse::getPosition(window)); billiards_1->position(position_1); billiards_1->initiate(position_1, position_2); mouse_click = 2; } }
            
            else if(event.key.code == sf::Keyboard::Right) { if(paused) { billiards_2 = nullptr; billiards_1->reset(); position_1 = billiards_1->getFocus(2); position_2 = sf::Vector2f(sf::Mouse::getPosition(window)); billiards_1->position(position_1); billiards_1->initiate(position_1, position_2); mouse_click = 2; } }
            
            else if(event.key.code == sf::Keyboard::Return) {
                
                if(paused && billiards_1->contains(sf::Mouse::getPosition(window)) && mouse_click >= 2) { paused = false; mouse_moved = true; if(mouse_click == 2) mouse_click++; if(billiards_2 && mouse_click < 5) billiards_2 = nullptr; }
                
                else paused = true;
                
            }
            
            else if(event.key.code == sf::Keyboard::Space) { billiards_1->reset(); if(billiards_2) billiards_2->reset(); mouse_click = 0; paused = true; }
            
            else if(event.key.code == sf::Keyboard::Escape) { requestStackPop(); requestStackPush(States::Main_Menu); }
            
            break;
            
        case sf::Event::MouseMoved:
            
            if(paused && mouse_click <= 5) {
                
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window); mouse_moved = true;
                
                if(billiards_1->contains(mouse_position)) {
                    
                    if(mouse_click == 1) { position_1 = sf::Vector2f(mouse_position); billiards_1->position(position_1); }
                    
                    else if(mouse_click == 2) { position_2 = sf::Vector2f(mouse_position); billiards_1->initiate(position_1, position_2); }
                    
                    else if(billiards_2 && mouse_click == 4) { position_1 = sf::Vector2f(mouse_position); billiards_2->position(position_1); }
                    
                    else if(billiards_2 && mouse_click == 5) { position_2 = sf::Vector2f(mouse_position); billiards_2->initiate(position_1, position_2); }
                    
                }
                
            }
            
            break;
            
        case sf::Event::MouseButtonPressed:
            
            if(event.mouseButton.button == sf::Mouse::Left) { if(paused && mouse_moved && billiards_1->contains(sf::Mouse::getPosition(window))) { mouse_click++; mouse_moved = false; } }
            
            break;
            
    }
    
    return true;
    
}