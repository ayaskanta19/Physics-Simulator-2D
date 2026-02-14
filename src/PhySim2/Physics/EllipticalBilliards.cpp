#include "PhySim2/Physics/EllipticalBilliards.hpp"
#include <cmath>

#define PI 3.141592653589793238462643383f

EllipticalBilliards::EllipticalBilliards(Attributes &attributes): attributes(attributes), trajectory(Solidus(new Line())), normal(Solidus(new Line())), ellipse(attributes.point_count), billiard(attributes.radius), focus_1(attributes.radius), focus_2(attributes.radius), start_point(), end_point(), unit_vector(), position_trace() {
    
    for(std::size_t i = 0; i < attributes.point_count; i++) { float theta = (360.f * i / attributes.point_count) * PI / 180.f, x = attributes.semi_majoris * std::cos(theta), y = attributes.semi_minoris * std::sin(theta); ellipse.setPoint(i, sf::Vector2f(x, y) + attributes.center); }
    
    ellipse.setFillColor(sf::Color::Transparent); ellipse.setOutlineThickness(10.f); billiard.setOrigin(attributes.radius, attributes.radius); focus_1.setOrigin(attributes.radius, attributes.radius); focus_2.setOrigin(attributes.radius, attributes.radius);
    
    focus_1.setPosition(attributes.center.x - std::sqrt(attributes.semi_majoris * attributes.semi_majoris - attributes.semi_minoris * attributes.semi_minoris), attributes.center.y); focus_2.setPosition(attributes.center.x + std::sqrt(attributes.semi_majoris * attributes.semi_majoris - attributes.semi_minoris * attributes.semi_minoris), attributes.center.y);
    
    billiard.setPosition(attributes.center); billiard.setFillColor(attributes.color);
    
}

void EllipticalBilliards::reset() { billiard.setPosition(attributes.center); start_point = sf::Vector2f(); end_point = sf::Vector2f(); unit_vector = sf::Vector2f(); position_trace.clear(); trajectory = Solidus(new Line()); normal = Solidus(new Line()); }

void EllipticalBilliards::simulate(sf::Time deltaTime) {
    
    billiard.setPosition(billiard.getPosition() + unit_vector * deltaTime.asSeconds()); position_trace.push_back(billiard.getPosition()); std::size_t i = closestPoint();
    
    if(i != -1) {
        
        sf::Vector2f reflection_point = ellipse.getPoint(i); trajectory->slope = (end_point.y - start_point.y) / (end_point.x - start_point.x); trajectory->intercept = start_point.y - trajectory->slope * start_point.x;
        
        normal->slope = (attributes.semi_majoris * attributes.semi_majoris * (reflection_point.y - attributes.center.y)) / (attributes.semi_minoris * attributes.semi_minoris * (reflection_point.x - attributes.center.x)); normal->intercept = reflection_point.y - normal->slope * reflection_point.x;
        
        float x = (-2.f * (normal->slope * start_point.x - start_point.y + normal->intercept) * normal->slope / (normal->slope * normal->slope + 1)) + start_point.x, y = (2.f * (normal->slope * start_point.x - start_point.y + normal->intercept) / (normal->slope * normal->slope + 1)) + start_point.y;
        
        end_point = sf::Vector2f(x, y), reflection_point = billiard.getPosition(); x = (-2.f * (normal->slope * reflection_point.x - reflection_point.y + normal->intercept) * normal->slope / (normal->slope * normal->slope + 1)) + reflection_point.x; y = (2.f * (normal->slope * reflection_point.x - reflection_point.y + normal->intercept) / (normal->slope * normal->slope + 1)) + reflection_point.y;
        
        start_point = sf::Vector2f(x, y), unit_vector = unitVector(end_point - start_point) * attributes.velocity;
        
    }
    
}

void EllipticalBilliards::position(sf::Vector2f billiard_position) { billiard.setPosition(billiard_position); }

void EllipticalBilliards::initiate(sf::Vector2f start_point, sf::Vector2f end_point) { this->start_point = start_point; this->end_point = end_point; unit_vector = unitVector(end_point - start_point) * attributes.velocity; }

bool EllipticalBilliards::contains(sf::Vector2i mouse_position) {
    
    float radial_distance = (((mouse_position.x - attributes.center.x) * (mouse_position.x - attributes.center.x)) / ((attributes.semi_majoris - attributes.radius) * (attributes.semi_majoris - attributes.radius))) + (((mouse_position.y - attributes.center.y) * (mouse_position.y - attributes.center.y)) / ((attributes.semi_minoris - attributes.radius) * (attributes.semi_minoris - attributes.radius)));
    
    if(radial_distance <= 1.f) return true; return false;
    
}

sf::Vector2f EllipticalBilliards::getFocus(int focus) { if(focus == 1) return focus_1.getPosition(); else return focus_2.getPosition(); }

std::size_t EllipticalBilliards::closestPoint() {
    
    sf::Vector2f billiard_position = billiard.getPosition(); std::size_t closest_point, point_count = attributes.point_count; float max_distance = std::numeric_limits<float>::max();
    
    if(billiard_position.x > attributes.center.x && billiard_position.y >= attributes.center.y) { closest_point = 0; point_count /= 4; }
    
    else if(billiard_position.x <= attributes.center.x && billiard_position.y > attributes.center.y) { closest_point = point_count / 4; point_count /= 2; }
    
    else if(billiard_position.x < attributes.center.x && billiard_position.y <= attributes.center.y) { closest_point = point_count / 2; point_count = 3 * point_count / 4; }
    
    else closest_point = 3 * point_count / 4;
    
    for(; closest_point < point_count; closest_point++) { float billiard_distance = distance(ellipse.getPoint(closest_point), billiard_position); if(billiard_distance <= attributes.radius && billiard_distance < max_distance) max_distance = billiard_distance; else if(billiard_distance >= max_distance) break; }
    
    if(max_distance == std::numeric_limits<float>::max()) closest_point = 0; return closest_point - 1;
    
}

sf::Vector2f EllipticalBilliards::unitVector(sf::Vector2f vector) { return vector / std::sqrt(vector.x * vector.x + vector.y * vector.y); }

float EllipticalBilliards::distance(sf::Vector2f start_point, sf::Vector2f end_point) { return std::sqrt((end_point.x - start_point.x) * (end_point.x - start_point.x) + (end_point.y - start_point.y) * (end_point.y - start_point.y)); }

void EllipticalBilliards::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    if(position_trace.size() > 1) for(std::size_t i = 1; i < position_trace.size(); i++) { sf::Vertex line[] = { sf::Vertex(position_trace[i - 1], attributes.color), sf::Vertex(position_trace[i], attributes.color) }; target.draw(line, 2, sf::Lines); }
    
    target.draw(ellipse); target.draw(focus_1); target.draw(focus_2); target.draw(billiard);
    
}