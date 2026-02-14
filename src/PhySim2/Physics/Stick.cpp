#include "PhySim2/Physics/Stick.hpp"
#include "PhySim2/Physics/Point.hpp"
#include <cmath>

Stick::Stick(Point &start_point, Point &end_point, float length): start_point(start_point), end_point(end_point), length(length), active(true), selected(false), default_color(sf::Color::White), selected_color(sf::Color::Red) {}

void Stick::snap() { active = false; }

void Stick::update() {
    
    if(!active) return; sf::Vector2f point_1 = start_point.getPosition(), point_2 = end_point.getPosition(), stick_vector = point_2 - point_1;
    
    float stick_length = std::sqrt(stick_vector.x * stick_vector.x + stick_vector.y * stick_vector.y), difference_factor = (length - stick_length) / stick_length;
    
    stick_vector *= difference_factor / 2.f; start_point.setPosition(point_1 - stick_vector); end_point.setPosition(point_2 + stick_vector);
    
}

void Stick::setSelection(bool selected) { this->selected = selected; }

void Stick::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    if(!active) return; sf::Color color = selected ? selected_color : default_color; sf::Vertex line[] = { sf::Vertex(start_point.getPosition(), color), sf::Vertex(end_point.getPosition(), color) }; target.draw(line, 2, sf::Lines);
    
}