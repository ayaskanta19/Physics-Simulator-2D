#pragma once

#ifndef PHYSIM2_INTERFACE_STATE_HPP
#define PHYSIM2_INTERFACE_STATE_HPP

#include "StateIdentifiers.hpp"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace sf { class RenderWindow; class Texture; class Font; }

class StateStack;

class State {
    
    public:
        
        typedef std::unique_ptr<State> Ptr;
        
        struct Context {
            
            Context(sf::RenderWindow&, sf::Texture&, sf::Font&, sf::Font&);
            
            sf::RenderWindow *window; sf::Texture *texture; sf::Font *button_font; sf::Font *text_font;
            
        };
        
    public:
        
        State(StateStack&, Context);
        virtual ~State();
        
        virtual void draw() = 0;
        virtual bool update(sf::Time) = 0;
        virtual bool handleEvent(const sf::Event&) = 0;
        
    protected:
        
        void requestStackPush(States::ID);
        void requestStackPop();
        void requestStackClear();
        
        Context getContext() const;
        
    private:
        
        StateStack *mStack; Context mContext;
        
};

#endif