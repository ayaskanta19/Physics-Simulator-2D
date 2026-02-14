#include "PhySim2/Physics/DoublePendulum.hpp"
#include <cmath>

#define PI 3.141592653589793238462643383f

// SET damping_coefficient = 0.99999f FOR EXPLICIT EULER | SET trace_count = 0 FOR STATIC TRACE

DoublePendulum::DoublePendulum(Pendulum::Attributes &attributes_1, Pendulum::Attributes &attributes_2): pendulum_1(attributes_1), pendulum_2(attributes_2), color(sf::Color(40, 255, 255)), gravity(9.8f), damping_coefficient(0.99699f), trace_count(50) {}

void DoublePendulum::reset() { position_trace.clear(); pendulum_1.attributes.alpha = 0.f; pendulum_2.attributes.alpha = 0.f; pendulum_1.attributes.omega = 0.f; pendulum_2.attributes.omega = 0.f; pendulum_1.attributes.theta = 0.f; pendulum_2.attributes.theta = 0.f; }

void DoublePendulum::simulate(sf::Time deltaTime) {
    
    rungeKutta4(deltaTime); // explicitEuler(deltaTime);
    
}

void DoublePendulum::update(const sf::Vector2f window_center, bool paused) {
    
    pendulum_1.attributes.position.x = window_center.x + pendulum_1.attributes.length * std::sin(pendulum_1.attributes.theta); pendulum_1.attributes.position.y = window_center.y + pendulum_1.attributes.length * std::cos(pendulum_1.attributes.theta);
    
    pendulum_2.attributes.position.x = pendulum_1.attributes.position.x + pendulum_2.attributes.length * std::sin(pendulum_2.attributes.theta); pendulum_2.attributes.position.y = pendulum_1.attributes.position.y + pendulum_2.attributes.length * std::cos(pendulum_2.attributes.theta);
    
    float theta_1 = pendulum_1.attributes.theta * 180.f / PI, theta_2 = pendulum_2.attributes.theta * 180.f / PI; theta_1 = 90.f - theta_1; theta_2 = 90.f - theta_2;
    
    pendulum_1.update(window_center, theta_1); pendulum_2.update(pendulum_1.attributes.position, theta_2); if(paused) return;
    
    position_trace.push_back(pendulum_2.attributes.position); if(trace_count != 0 && position_trace.size() > trace_count) position_trace.erase(position_trace.begin());
    
}

void DoublePendulum::initiate(const sf::Vector2f fulcrum_position, const sf::Vector2i mouse_position, int pendulum) { float theta = std::atan2((mouse_position.x - fulcrum_position.x), (mouse_position.y - fulcrum_position.y)); if(pendulum == 1) pendulum_1.attributes.theta = theta; else pendulum_2.attributes.theta = theta; }

void DoublePendulum::rungeKutta4(sf::Time deltaTime) {
    
    float time_step = deltaTime.asSeconds();
    
    float expression_1 = -gravity * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::sin(pendulum_1.attributes.theta);
    
    float expression_2 = -pendulum_2.attributes.mass * gravity * std::sin(pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta);
    
    float expression_3 = -2.f * std::sin(pendulum_1.attributes.theta - pendulum_2.attributes.theta) * pendulum_2.attributes.mass * (pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length + pendulum_1.attributes.omega * pendulum_1.attributes.omega * pendulum_1.attributes.length * std::cos(pendulum_1.attributes.theta - pendulum_2.attributes.theta));
    
    float expression_4 = pendulum_1.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta));
    
    float alpha_11 = (expression_1 + expression_2 + expression_3) / expression_4;
    
    expression_1 = 2.f * std::sin(pendulum_1.attributes.theta - pendulum_2.attributes.theta);
    
    expression_2 = pendulum_1.attributes.omega * pendulum_1.attributes.omega * pendulum_1.attributes.length * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) + gravity * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::cos(pendulum_1.attributes.theta);
    
    expression_3 = pendulum_2.attributes.omega * pendulum_2.attributes.omega * pendulum_2.attributes.length * pendulum_2.attributes.mass * std::cos(pendulum_1.attributes.theta - pendulum_2.attributes.theta);
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * pendulum_1.attributes.theta - 2.f * pendulum_2.attributes.theta));
    
    float alpha_21 = (expression_1 * (expression_2 + expression_3)) / expression_4, omega_11 = pendulum_1.attributes.omega, omega_21 = pendulum_2.attributes.omega;
    
    expression_1 = -gravity * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::sin(pendulum_1.attributes.theta + time_step * 0.5f * omega_11);
    
    expression_2 = -pendulum_2.attributes.mass * gravity * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_21));
    
    expression_3 = -2.f * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_21)) * pendulum_2.attributes.mass * ((pendulum_2.attributes.omega + time_step * 0.5f * alpha_21) * (pendulum_2.attributes.omega + time_step * 0.5f * alpha_21) * pendulum_2.attributes.length + (pendulum_1.attributes.omega + time_step * 0.5f * alpha_11) * (pendulum_1.attributes.omega + time_step * 0.5f * alpha_11) * pendulum_1.attributes.length * std::cos((pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_21)));
    
    expression_4 = pendulum_1.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_21)));
    
    float alpha_12 = (expression_1 + expression_2 + expression_3) / expression_4;
    
    expression_1 = 2.f * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_21));
    
    expression_2 = (pendulum_1.attributes.omega + time_step * 0.5f * alpha_11) * (pendulum_1.attributes.omega + time_step * 0.5f * alpha_11) * pendulum_1.attributes.length * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) + gravity * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::cos(pendulum_1.attributes.theta + time_step * 0.5f * omega_11);
    
    expression_3 = (pendulum_2.attributes.omega + time_step * 0.5f * alpha_21) * (pendulum_2.attributes.omega + time_step * 0.5f * alpha_21) * pendulum_2.attributes.length * pendulum_2.attributes.mass * std::cos((pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_21));
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * 0.5f * omega_11) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_21)));
    
    float alpha_22 = (expression_1 * (expression_2 + expression_3)) / expression_4, omega_12 = pendulum_1.attributes.omega + time_step * 0.5f * alpha_11, omega_22 = pendulum_2.attributes.omega + time_step * 0.5f * alpha_21;
    
    expression_1 = -gravity * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::sin(pendulum_1.attributes.theta + time_step * 0.5f * omega_12);
    
    expression_2 = -pendulum_2.attributes.mass * gravity * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_22));
    
    expression_3 = -2.f * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_22)) * pendulum_2.attributes.mass * ((pendulum_2.attributes.omega + time_step * 0.5f * alpha_22) * (pendulum_2.attributes.omega + time_step * 0.5f * alpha_22) * pendulum_2.attributes.length + (pendulum_1.attributes.omega + time_step * 0.5f * alpha_12) * (pendulum_1.attributes.omega + time_step * 0.5f * alpha_12) * pendulum_1.attributes.length * std::cos((pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_22)));
    
    expression_4 = pendulum_1.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_22)));
    
    float alpha_13 = (expression_1 + expression_2 + expression_3) / expression_4;
    
    expression_1 = 2.f * std::sin((pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_22));
    
    expression_2 = (pendulum_1.attributes.omega + time_step * 0.5f * alpha_12) * (pendulum_1.attributes.omega + time_step * 0.5f * alpha_12) * pendulum_1.attributes.length * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) + gravity * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::cos(pendulum_1.attributes.theta + time_step * 0.5f * omega_12);
    
    expression_3 = (pendulum_2.attributes.omega + time_step * 0.5f * alpha_22) * (pendulum_2.attributes.omega + time_step * 0.5f * alpha_22) * pendulum_2.attributes.length * pendulum_2.attributes.mass * std::cos((pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - (pendulum_2.attributes.theta + time_step * 0.5f * omega_22));
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * 0.5f * omega_12) - 2.f * (pendulum_2.attributes.theta + time_step * 0.5f * omega_22)));
    
    float alpha_23 = (expression_1 * (expression_2 + expression_3)) / expression_4, omega_13 = pendulum_1.attributes.omega + time_step * 0.5f * alpha_12, omega_23 = pendulum_2.attributes.omega + time_step * 0.5f * alpha_22;
    
    expression_1 = -gravity * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::sin(pendulum_1.attributes.theta + time_step * omega_13);
    
    expression_2 = -pendulum_2.attributes.mass * gravity * std::sin((pendulum_1.attributes.theta + time_step * omega_13) - 2.f * (pendulum_2.attributes.theta + time_step * omega_23));
    
    expression_3 = -2.f * std::sin((pendulum_1.attributes.theta + time_step * omega_13) - (pendulum_2.attributes.theta + time_step * omega_23)) * pendulum_2.attributes.mass * ((pendulum_2.attributes.omega + time_step * alpha_23) * (pendulum_2.attributes.omega + time_step * alpha_23) * pendulum_2.attributes.length + (pendulum_1.attributes.omega + time_step * alpha_13) * (pendulum_1.attributes.omega + time_step * alpha_13) * pendulum_1.attributes.length * std::cos((pendulum_1.attributes.theta + time_step * omega_13) - (pendulum_2.attributes.theta + time_step * omega_23)));
    
    expression_4 = pendulum_1.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * omega_13) - 2.f * (pendulum_2.attributes.theta + time_step * omega_23)));
    
    float alpha_14 = (expression_1 + expression_2 + expression_3) / expression_4;
    
    expression_1 = 2.f * std::sin((pendulum_1.attributes.theta + time_step * omega_13) - (pendulum_2.attributes.theta + time_step * omega_23));
    
    expression_2 = (pendulum_1.attributes.omega + time_step * alpha_13) * (pendulum_1.attributes.omega + time_step * alpha_13) * pendulum_1.attributes.length * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) + gravity * (pendulum_1.attributes.mass + pendulum_2.attributes.mass) * std::cos(pendulum_1.attributes.theta + time_step * omega_13);
    
    expression_3 = (pendulum_2.attributes.omega + time_step * alpha_23) * (pendulum_2.attributes.omega + time_step * alpha_23) * pendulum_2.attributes.length * pendulum_2.attributes.mass * std::cos((pendulum_1.attributes.theta + time_step * omega_13) - (pendulum_2.attributes.theta + time_step * omega_23));
    
    expression_4 = pendulum_2.attributes.length * (2.f * pendulum_1.attributes.mass + pendulum_2.attributes.mass - pendulum_2.attributes.mass * std::cos(2.f * (pendulum_1.attributes.theta + time_step * omega_13) - 2.f * (pendulum_2.attributes.theta + time_step * omega_23)));
    
    float alpha_24 = (expression_1 * (expression_2 + expression_3)) / expression_4, omega_14 = pendulum_1.attributes.omega + time_step * alpha_13, omega_24 = pendulum_2.attributes.omega + time_step * alpha_23;
    
    pendulum_1.attributes.alpha = alpha_11; pendulum_2.attributes.alpha = alpha_21; pendulum_1.attributes.omega += (time_step / 6.f) * (alpha_11 + 2.f * alpha_12 + 2.f * alpha_13 + alpha_14); pendulum_2.attributes.omega += (time_step / 6.f) * (alpha_21 + 2.f * alpha_22 + 2.f * alpha_23 + alpha_24); pendulum_1.attributes.theta += (time_step / 6.f) * (omega_11 + 2.f * omega_12 + 2.f * omega_13 + omega_14); pendulum_2.attributes.theta += (time_step / 6.f) * (omega_21 + 2.f * omega_22 + 2.f * omega_23 + omega_24); pendulum_1.attributes.omega *= damping_coefficient; pendulum_2.attributes.omega *= damping_coefficient;
    
}

void DoublePendulum::explicitEuler(sf::Time deltaTime) {
    
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

void DoublePendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    if(position_trace.size() > 1) for(std::size_t i = 1; i < position_trace.size(); i++) { sf::Vertex line[] = { sf::Vertex(position_trace[i - 1], color), sf::Vertex(position_trace[i], color) }; target.draw(line, 2, sf::Lines); }
    
    target.draw(pendulum_2); target.draw(pendulum_1);
    
}