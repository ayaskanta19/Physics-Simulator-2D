#include "PhySim2/Physics/MinimalPendulum.hpp"

MinimalPendulum::MinimalPendulum(Attributes &attributes): attributes(attributes), pendulum_rod(sf::Vector2f(attributes.length, attributes.width)) { pendulum_rod.setOrigin(0.f, attributes.width / 2.f); }

void MinimalPendulum::setColor(sf::Color color) { pendulum_rod.setFillColor(color); }

void MinimalPendulum::update(const sf::Vector2f position, float theta) { pendulum_rod.setPosition(position); pendulum_rod.setRotation(theta); }

void MinimalPendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(pendulum_rod); }