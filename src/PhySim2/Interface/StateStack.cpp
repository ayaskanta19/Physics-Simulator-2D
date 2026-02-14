#include "PhySim2/Interface/StateStack.hpp"

StateStack::StateStack(State::Context context): mContext(context), mStack(), mPendingList(), mFactories() {}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID): action(action), stateID(stateID) {}

void StateStack::draw() { for(State::Ptr &state: mStack) state->draw(); }

void StateStack::update(sf::Time deltaTime) {
    
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) if(!(*itr)->update(deltaTime)) break;
    
    applyPendingChanges();
    
}

void StateStack::handleEvent(const sf::Event &event) {
    
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) if(!(*itr)->handleEvent(event)) break;
    
    applyPendingChanges();
    
}

void StateStack::pushState(States::ID stateID) { mPendingList.push_back(PendingChange(Push, stateID)); }

void StateStack::popState() { mPendingList.push_back(PendingChange(Pop)); }

void StateStack::clearStates() { mPendingList.push_back(PendingChange(Clear)); }

bool StateStack::isEmpty() const { return mStack.empty(); }

void StateStack::applyPendingChanges() {
    
    for(PendingChange change: mPendingList) {
        
        switch(change.action) {
            
            case Push: mStack.push_back(createState(change.stateID)); break;
            
            case Pop: mStack.pop_back(); break;
            
            case Clear: mStack.clear(); break;
            
        }
        
    }
    
    mPendingList.clear();
    
}

State::Ptr StateStack::createState(States::ID stateID) { auto found = mFactories.find(stateID); return found->second(); }