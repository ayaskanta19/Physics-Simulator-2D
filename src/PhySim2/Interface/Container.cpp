#include "PhySim2/Interface/Container.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI {
    
    Container::Container(sf::RenderWindow &window): mWindow(window), mSelectedChild(-1), mChildren() {}
    
    void Container::pack(Component::Ptr component) { mChildren.push_back(component); if(!hasSelection() && component->isSelectable()) select(mChildren.size() - 1); }
    
    void Container::selectOption(std::size_t index) { select(index); }
    
    int Container::nextOption() { selectNext(); return mSelectedChild; }
    
    int Container::finalOption() { return mChildren.size() - 1; }
    
    int Container::previousOption() { selectPrevious(); return mSelectedChild; }
    
    int Container::selectedOption() { return mSelectedChild; }
    
    bool Container::hasActivation() const { for(const Component::Ptr &child: mChildren) if(child->isActive()) return true; return false; }
    
    bool Container::isSelectable() const { return false; }
    
    void Container::handleEvent(const sf::Event &event) {
        
        if(hasSelection() && mChildren[mSelectedChild]->isActive()) { mChildren[mSelectedChild]->handleEvent(event); return; }
        
        if(event.type == sf::Event::MouseMoved) { mouseEvent(sf::Mouse::getPosition(mWindow), false); return; }
        
        else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { mouseEvent(sf::Mouse::getPosition(mWindow), true); return; }
        
        if(event.type == sf::Event::KeyPressed) {
            
            if(event.key.code == sf::Keyboard::Up) selectPrevious();
            
            else if(event.key.code == sf::Keyboard::Down) selectNext();
            
            else if(event.key.code == sf::Keyboard::Return) if(hasSelection()) mChildren[mSelectedChild]->activate();
            
        }
        
    }
    
    void Container::selectNext() {
        
        if(!hasSelection()) return;
        
        int next = mSelectedChild;
        
        do next = (next + 1) % mChildren.size(); while(!mChildren[next]->isSelectable());
        
        select(next);
        
    }
    
    void Container::selectPrevious() {
        
        if(!hasSelection()) return;
        
        int prev = mSelectedChild;
        
        do prev = (prev + mChildren.size() - 1) % mChildren.size(); while(!mChildren[prev]->isSelectable());
        
        select(prev);
        
    }
    
    void Container::select(std::size_t index) { if(hasSelection()) { mChildren[mSelectedChild]->deselect(); mChildren[mSelectedChild]->deactivate(); } mChildren[index]->select(); mSelectedChild = index; }
    
    void Container::mouseEvent(sf::Vector2i mousePosition, bool mouseClicked) {
        
        for(std::vector<Component::Ptr>::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
            
            Component *child = it->get();
            
            if(child->isSelectable()) {
                
                sf::FloatRect bounds = child->getBounds();
                
                if(mousePosition.x >= bounds.left && mousePosition.x <= bounds.left + bounds.width && mousePosition.y >= bounds.top && mousePosition.y <= bounds.top + bounds.height) {
                    
                    if(mouseClicked) child->activate(); else select(std::distance(mChildren.begin(), it)); break;
                    
                }
                
            }
            
        }
        
    }
    
    bool Container::hasSelection() const { return mSelectedChild >= 0; }
    
    sf::FloatRect Container::getBounds() const { return mChildren[mSelectedChild]->getBounds(); }
    
    void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const { states.transform *= getTransform(); for(const Component::Ptr &child: mChildren) target.draw(*child, states); }
    
}