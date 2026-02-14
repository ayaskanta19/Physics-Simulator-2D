#include "PhySim2/Interface/Utility.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>

void centerOrigin(sf::RectangleShape &shape) { sf::FloatRect bounds = shape.getLocalBounds(); shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f)); }

void centerOrigin(sf::Text &text) { sf::FloatRect bounds = text.getLocalBounds(); text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f)); }