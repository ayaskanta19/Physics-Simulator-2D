#include "PhySim2/Physics/Pendulum.hpp"

Pendulum::Pendulum(Attributes &attributes): attributes(attributes), pendulum_mass(attributes.radius), pendulum_rod(sf::Vector2f(attributes.length, attributes.width)) {
    
    pendulum_mass.setOrigin(sf::Vector2f(attributes.radius, attributes.radius)); pendulum_mass.setFillColor(sf::Color(40, 255, 255)); pendulum_rod.setOrigin(0.f, attributes.width / 2.f); pendulum_rod.setFillColor(sf::Color::White);
    
}

void Pendulum::update(const sf::Vector2f position, float theta) { pendulum_mass.setPosition(attributes.position); pendulum_rod.setPosition(position); pendulum_rod.setRotation(theta); }

void Pendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(pendulum_rod); target.draw(pendulum_mass); }