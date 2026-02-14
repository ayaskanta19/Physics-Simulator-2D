#include "PhySim2/Physics/Mouse.hpp"

Mouse::Mouse(): previous_position(), current_position(), cursor_size(20.f), cursor_min(20.f), cursor_max(100.f), blast_intensity(0.f), blast_min(-2.f), blast_max(2.f), left_button(false), right_button(false) {}

void Mouse::update(sf::Vector2f position) { previous_position = current_position; current_position = position; }

void Mouse::setCursorSize(float cursor_size) { if(this->cursor_size + cursor_size < cursor_min || this->cursor_size + cursor_size > cursor_max) return; this->cursor_size += cursor_size; }

void Mouse::setBlastIntensity(float blast_intensity) { if(this->blast_intensity + blast_intensity < blast_min || this->blast_intensity + blast_intensity > blast_max) return; this->blast_intensity += blast_intensity; }

void Mouse::setLeftButtonPressed(bool left_button) { this->left_button = left_button; }

void Mouse::setRightButtonPressed(bool right_button) { this->right_button = right_button; }

bool Mouse::activeBlastEffect() const { return blast_intensity != 0.f; }

bool Mouse::leftButtonPressed() const { return left_button; }

bool Mouse::rightButtonPressed() const { return right_button; }

float Mouse::getCursorSize() const { return cursor_size; }

float Mouse::getBlastIntensity() const { return blast_intensity; }

const sf::Vector2f Mouse::getCurrentPosition() const { return current_position; }

const sf::Vector2f Mouse::getPreviousPosition() const { return previous_position; }