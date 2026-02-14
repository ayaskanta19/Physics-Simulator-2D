#include "PhySim2/Interface/Button.hpp"
#include "PhySim2/Interface/Utility.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI {
    
    Button::Button(const sf::Font &font): mCallback(), mIsToggle(false), mButtonBackground(sf::Vector2f(900.f, 100.f)), mText("", font, 65u) {
        
        mButtonBackground.setOutlineThickness(2.5f); mButtonBackground.setOutlineColor(sf::Color::White); mButtonBackground.setFillColor(sf::Color(0, 0, 0, 0));
        
        centerOrigin(mButtonBackground); mText.setPosition(getPosition());
        
    }
    
    void Button::setToggle(bool flag) { mIsToggle = flag; }
    
    void Button::setCallback(Callback callback) { mCallback = std::move(callback); }
    
    void Button::setText(const std::string &text) { mText.setString(text); centerOrigin(mText); }
    
    void Button::select() { Component::select(); alterButton(sf::Color::White, 50.f, 5u); }
    
    void Button::deselect() { Component::deselect(); alterButton(sf::Color::White); }
    
    void Button::activate() { Component::activate(); if(mIsToggle) alterButton(sf::Color(100, 100, 100), 50.f, 5u); if(mCallback) mCallback(); if(!mIsToggle) deactivate(); }
    
    void Button::deactivate() { Component::deactivate(); if(mIsToggle) { if(isSelected()) alterButton(sf::Color::White, 50.f, 5u); else alterButton(sf::Color::White); } }
    
    void Button::handleEvent(const sf::Event &event) {}
    
    bool Button::isSelectable() const { return true; }
    
    sf::FloatRect Button::getBounds() const { sf::FloatRect bounds = getTransform().transformRect(mButtonBackground.getLocalBounds()); bounds.left -= bounds.width / 2.f; bounds.top -= bounds.height / 2.f; return bounds; }
    
    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const { states.transform *= getTransform(); target.draw(mButtonBackground, states); target.draw(mText, states); }
    
    void Button::alterButton(const sf::Color &color, float rectSize, int charSize) {
        
        mButtonBackground.setSize(sf::Vector2f(900.f + rectSize, 100.f + rectSize)); mText.setCharacterSize(65u + charSize);
        
        mButtonBackground.setOutlineColor(color); mText.setFillColor(color); centerOrigin(mButtonBackground); centerOrigin(mText);
        
    }
    
}