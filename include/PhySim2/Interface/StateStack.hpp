#pragma once

#ifndef PHYSIM2_INTERFACE_STATESTACK_HPP
#define PHYSIM2_INTERFACE_STATESTACK_HPP

#include "State.hpp"
#include "SFML/System/NonCopyable.hpp"
#include <functional>
#include <vector>
#include <map>

namespace sf { class Event; }

class StateStack: private sf::NonCopyable {
    
    public:
        
        enum Action { Push, Pop, Clear };
        
    public:
        
        explicit StateStack(State::Context);
        
        template<typename T> void registerState(States::ID);
        
        void draw();
        void update(sf::Time);
        void handleEvent(const sf::Event&);
        
        void pushState(States::ID);
        void popState();
        void clearStates();
        
        bool isEmpty() const;
        
    private:
        
        void applyPendingChanges();
        
        State::Ptr createState(States::ID);
        
    private:
        
        struct PendingChange {
            
            explicit PendingChange(Action, States::ID state = States::None);
            
            Action action; States::ID stateID;
            
        };
        
    private:
        
        State::Context mContext;
        
        std::vector<State::Ptr> mStack; std::vector<PendingChange> mPendingList;
        
        std::map<States::ID, std::function<State::Ptr()>> mFactories;
        
};

template<typename T>
void StateStack::registerState(States::ID stateID) { mFactories[stateID] = [this] () { return State::Ptr(new T(*this, mContext)); }; }

#endif