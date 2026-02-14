#pragma once

#ifndef PHYSIM2_INTERFACE_CONTAINER_HPP
#define PHYSIM2_INTERFACE_CONTAINER_HPP

#include "Component.hpp"
#include <vector>

namespace sf { class RenderWindow; }

namespace GUI {
    
    class Container: public Component {
        
        public:
            
            typedef std::shared_ptr<Container> Ptr;
            
        public:
            
            Container(sf::RenderWindow&);
            
            void pack(Component::Ptr);
            void selectOption(std::size_t);
            
            int nextOption();
            int finalOption();
            int previousOption();
            int selectedOption();
            
            bool hasActivation() const;
            
            virtual bool isSelectable() const;
            virtual void handleEvent(const sf::Event&);
            
        private:
            
            void selectNext();
            void selectPrevious();
            void select(std::size_t);
            void mouseEvent(sf::Vector2i, bool);
            
            bool hasSelection() const;
            
            virtual sf::FloatRect getBounds() const;
            virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
            
        private:
            
            sf::RenderWindow &mWindow; int mSelectedChild;
            
            std::vector<Component::Ptr> mChildren;
            
    };
    
}

#endif