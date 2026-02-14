#include "PhySim2/Physics/TriplePendulum.hpp"
#include <cmath>

#define PI 3.141592653589793238462643383f

// SET trace_count = 0 FOR STATIC TRACE

TriplePendulum::TriplePendulum(Pendulum::Attributes &attributes_1, Pendulum::Attributes &attributes_2, Pendulum::Attributes &attributes_3): pendulum_1(attributes_1), pendulum_2(attributes_2), pendulum_3(attributes_3), color(sf::Color(255, 70, 125)), gravity(9.8f), damping_coefficient(0.99899f), trace_count(50) {}

void TriplePendulum::reset() { position_trace.clear(); pendulum_1.attributes.alpha = 0.f; pendulum_2.attributes.alpha = 0.f; pendulum_3.attributes.alpha = 0.f; pendulum_1.attributes.omega = 0.f; pendulum_2.attributes.omega = 0.f; pendulum_3.attributes.omega = 0.f; pendulum_1.attributes.theta = 0.f; pendulum_2.attributes.theta = 0.f; pendulum_3.attributes.theta = 0.f; }

void TriplePendulum::simulate(sf::Time deltaTime) {
    
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
    
    expression_1 = -gravity * (2.f * pendulum_2.attributes.mass + pendulum_3.attributes.mass) * std::sin(pendulum_2.attributes.theta);
    
    expression_2 = -pendulum_3.attributes.mass * gravity * std::sin(pendulum_2.attributes.theta - 2.f * pendulum_3.attributes.theta);
    
    expression_3 = -2.f * std::sin(pendulum_2.attributes.theta - pendulum_3.attributes.theta) * pendulum_3.attributes.mass * (pendulum_3.attributes.omega * pendulum_3.attributes.omega * pendulum_3.attributes.length + pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length * std::cos(pendulum_2.attributes.theta - pendulum_3.attributes.theta));
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_2.attributes.mass + pendulum_3.attributes.mass - pendulum_3.attributes.mass * std::cos(2.f * pendulum_2.attributes.theta - 2.f * pendulum_3.attributes.theta));
    
    pendulum_2.attributes.alpha += (expression_1 + expression_2 + expression_3) / expression_4; pendulum_2.attributes.alpha /= 2.f;
    
    expression_1 = 2.f * std::sin(pendulum_2.attributes.theta - pendulum_3.attributes.theta);
    
    expression_2 = pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length * (pendulum_2.attributes.mass + pendulum_3.attributes.mass) + gravity * (pendulum_2.attributes.mass + pendulum_3.attributes.mass) * std::cos(pendulum_2.attributes.theta);
    
    expression_3 = pendulum_3.attributes.omega * pendulum_3.attributes.omega * pendulum_3.attributes.length * pendulum_3.attributes.mass * std::cos(pendulum_2.attributes.theta - pendulum_3.attributes.theta);
    
    expression_4 = pendulum_3.attributes.length * (2.f * pendulum_2.attributes.mass + pendulum_3.attributes.mass - pendulum_3.attributes.mass * std::cos(2.f * pendulum_2.attributes.theta - 2.f * pendulum_3.attributes.theta));
    
    pendulum_3.attributes.alpha = (expression_1 * (expression_2 + expression_3)) / expression_4;
    
    pendulum_1.attributes.omega += pendulum_1.attributes.alpha * deltaTime.asSeconds(); pendulum_2.attributes.omega += pendulum_2.attributes.alpha * deltaTime.asSeconds(); pendulum_3.attributes.omega += pendulum_3.attributes.alpha * deltaTime.asSeconds();
    
    pendulum_1.attributes.theta += pendulum_1.attributes.omega * deltaTime.asSeconds(); pendulum_2.attributes.theta += pendulum_2.attributes.omega * deltaTime.asSeconds(); pendulum_3.attributes.theta += pendulum_3.attributes.omega * deltaTime.asSeconds();
    
    pendulum_1.attributes.omega *= damping_coefficient; pendulum_2.attributes.omega *= damping_coefficient; pendulum_3.attributes.omega *= damping_coefficient;
    
}

void TriplePendulum::update(const sf::Vector2f window_center, bool paused) {
    
    pendulum_1.attributes.position.x = window_center.x + pendulum_1.attributes.length * std::sin(pendulum_1.attributes.theta); pendulum_1.attributes.position.y = window_center.y + pendulum_1.attributes.length * std::cos(pendulum_1.attributes.theta);
    
    pendulum_2.attributes.position.x = pendulum_1.attributes.position.x + pendulum_2.attributes.length * std::sin(pendulum_2.attributes.theta); pendulum_2.attributes.position.y = pendulum_1.attributes.position.y + pendulum_2.attributes.length * std::cos(pendulum_2.attributes.theta);
    
    pendulum_3.attributes.position.x = pendulum_2.attributes.position.x + pendulum_3.attributes.length * std::sin(pendulum_3.attributes.theta); pendulum_3.attributes.position.y = pendulum_2.attributes.position.y + pendulum_3.attributes.length * std::cos(pendulum_3.attributes.theta);
    
    float theta_1 = pendulum_1.attributes.theta * 180.f / PI, theta_2 = pendulum_2.attributes.theta * 180.f / PI, theta_3 = pendulum_3.attributes.theta * 180.f / PI; theta_1 = 90.f - theta_1; theta_2 = 90.f - theta_2, theta_3 = 90.f - theta_3;
    
    pendulum_1.update(window_center, theta_1); pendulum_2.update(pendulum_1.attributes.position, theta_2); pendulum_3.update(pendulum_2.attributes.position, theta_3); if(paused) return;
    
    position_trace.push_back(pendulum_3.attributes.position); if(trace_count != 0 && position_trace.size() > trace_count) position_trace.erase(position_trace.begin());
    
}

void TriplePendulum::initiate(const sf::Vector2f fulcrum_position, const sf::Vector2i mouse_position, int pendulum) { float theta = std::atan2((mouse_position.x - fulcrum_position.x), (mouse_position.y - fulcrum_position.y)); if(pendulum == 1) pendulum_1.attributes.theta = theta; else if(pendulum == 2) pendulum_2.attributes.theta = theta; else pendulum_3.attributes.theta = theta; }

void TriplePendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    if(position_trace.size() > 1) for(std::size_t i = 1; i < position_trace.size(); i++) { sf::Vertex line[] = { sf::Vertex(position_trace[i - 1], color), sf::Vertex(position_trace[i], color) }; target.draw(line, 2, sf::Lines); }
    
    target.draw(pendulum_3); target.draw(pendulum_2); target.draw(pendulum_1);
    
}