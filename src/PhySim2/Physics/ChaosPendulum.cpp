#include "PhySim2/Physics/ChaosPendulum.hpp"
#include <cmath>

#define PI 3.141592653589793238462643383f

ChaosPendulum::ChaosPendulum(MinimalPendulum::Attributes &attributes_1, MinimalPendulum::Attributes &attributes_2): pendulum_1(attributes_1), pendulum_2(attributes_2), gravity(9.8f), damping_coefficient(0.99999f) {}

void ChaosPendulum::simulate(sf::Time deltaTime) {
    
    float expression_1 = -gravity * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::sin(pendulum_1.attributes.theta);
    
    float expression_2 = -pendulum_2.attributes.mass * gravity * std::sin(pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta);
    
    float expression_3 = -2.f * std::sin(pendulum_1.attributes.theta - pendulum_2.attributes.theta) * pendulum_2.attributes.mass * (pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length + pendulum_1.attributes.omega * pendulum_1.attributes.omega * pendulum_1.attributes.length * std::cos(pendulum_1.attributes.theta - pendulum_2.attributes.theta));
    
    float expression_4 = pendulum_1.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta));
    
    pendulum_1.attributes.alpha = (expression_1 + expression_2 + expression_3) / expression_4;
    
    expression_1 = 2.f * std::sin(pendulum_1.attributes.theta - pendulum_2.attributes.theta);
    
    expression_2 = pendulum_1.attributes.omega * pendulum_1.attributes.omega * pendulum_1.attributes.length * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) + gravity * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::cos(pendulum_1.attributes.theta);
    
    expression_3 = pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length * pendulum_2.attributes.mass * std::cos(pendulum_1.attributes.theta - pendulum_2.attributes.theta);
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta));
    
    pendulum_2.attributes.alpha = (expression_1 * (expression_2 + expression_3)) / expression_4;
    
    pendulum_1.attributes.omega += pendulum_1.attributes.alpha * deltaTime.asSeconds(); pendulum_2.attributes.omega += pendulum_2.attributes.alpha * deltaTime.asSeconds(); pendulum_1.attributes.theta += pendulum_1.attributes.omega * deltaTime.asSeconds(); pendulum_2.attributes.theta += pendulum_2.attributes.omega * deltaTime.asSeconds(); pendulum_1.attributes.omega *= damping_coefficient; pendulum_2.attributes.omega *= damping_coefficient;
    
}

void ChaosPendulum::reset(float theta_1, float theta_2) { pendulum_1.attributes.alpha = 0.f; pendulum_2.attributes.alpha = 0.f; pendulum_1.attributes.omega = 0.f; pendulum_2.attributes.omega = 0.f; pendulum_1.attributes.theta = theta_1; pendulum_2.attributes.theta = theta_2; }

void ChaosPendulum::update(const sf::Vector2f window_center) {
    
    pendulum_1.attributes.position.x = window_center.x + pendulum_1.attributes.length * std::sin(pendulum_1.attributes.theta); pendulum_1.attributes.position.y = window_center.y + pendulum_1.attributes.length * std::cos(pendulum_1.attributes.theta);
    
    float theta_1 = pendulum_1.attributes.theta * 180.f / PI, theta_2 = pendulum_2.attributes.theta * 180.f / PI; theta_1 = 90.f - theta_1; theta_2 = 90.f - theta_2;
    
    pendulum_1.update(window_center, theta_1); pendulum_2.update(pendulum_1.attributes.position, theta_2);
    
}

void ChaosPendulum::setColor(sf::Color color_1, sf::Color color_2) { pendulum_1.setColor(color_1); pendulum_2.setColor(color_2); }

void ChaosPendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(pendulum_2); target.draw(pendulum_1); }