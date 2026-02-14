#include "PhySim2/Interface/State.hpp"
#include "PhySim2/Interface/StateStack.hpp"

State::Context::Context(sf::RenderWindow &window, sf::Texture &texture, sf::Font &button_font, sf::Font &text_font): window(&window), texture(&texture), button_font(&button_font), text_font(&text_font) {}

State::State(StateStack &stack, Context context): mStack(&stack), mContext(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) { mStack->pushState(stateID); }

void State::requestStackPop() { mStack->popState(); }

void State::requestStackClear() { mStack->clearStates(); }

State::Context State::getContext() const { return mContext; }