#pragma once

#ifndef PHYSIM2_INTERFACE_COMPONENT_HPP
#define PHYSIM2_INTERFACE_COMPONENT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>

namespace sf { class Event; }

namespace GUI {
    
    class Component: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
        
        public:
            
            typedef std::shared_ptr<Component> Ptr;
            
        public:
            
            Component();
            virtual ~Component();
            
            bool isSelected() const;
            
            virtual void select();
            virtual void deselect();
            virtual void activate();
            virtual void deactivate();
            
            virtual void handleEvent(const sf::Event&) = 0;
            
            virtual bool isActive() const;
            virtual bool isSelectable() const = 0;
            
            virtual sf::FloatRect getBounds() const = 0;
            
        private:
            
            bool mIsSelected, mIsActive;
            
    };
    
}

#endif