#include "PhySim2/Simulator/MainMenuState.hpp"
#include "PhySim2/Interface/Button.hpp"
#include "PhySim2/Interface/Utility.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

MainMenuState::MainMenuState(StateStack &stack, Context context): State(stack, context), mDisplayText(), mCaptionText(), mGUIContainer(*context.window) {
    
    sf::Vector2f viewSize = context.window->getView().getSize(); float spacing = 1.f / 7.f; mBackgroundSprite.setTexture(*context.texture);
    
    mDisplayText.setFont(*context.button_font); mDisplayText.setString("PHYSIM2"); mDisplayText.setCharacterSize(130u); centerOrigin(mDisplayText); mDisplayText.setPosition(viewSize.x * 0.77f, viewSize.y * 0.45f);
    
    mCaptionText.setFont(*context.button_font); mCaptionText.setString("THE PHYSICS IS THEORETICAL, BUT THE FUN IS REAL !"); mCaptionText.setCharacterSize(28u); centerOrigin(mCaptionText); mCaptionText.setPosition(viewSize.x * 0.77f, viewSize.y * 0.55f);
    
    auto double_pendulum_button = std::make_shared<GUI::Button>(*context.button_font); auto triple_pendulum_button = std::make_shared<GUI::Button>(*context.button_font); auto butterfly_effect_button = std::make_shared<GUI::Button>(*context.button_font);
    
    auto elliptical_billiards_button = std::make_shared<GUI::Button>(*context.button_font); auto tearable_cloth_button = std::make_shared<GUI::Button>(*context.button_font); auto master_exit_button = std::make_shared<GUI::Button>(*context.button_font);
    
    double_pendulum_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 1.f); double_pendulum_button->setText("Double Pendulum"); double_pendulum_button->setCallback([this] () { requestStackPop(); requestStackPush(States::Double_Pendulum); });
    
    triple_pendulum_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 2.f); triple_pendulum_button->setText("Triple Pendulum"); triple_pendulum_button->setCallback([this] () { requestStackPop(); requestStackPush(States::Triple_Pendulum); });
    
    butterfly_effect_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 3.f); butterfly_effect_button->setText("Butterfly Effect"); butterfly_effect_button->setCallback([this] () { requestStackPop(); requestStackPush(States::Butterfly_Effect); });
    
    elliptical_billiards_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 4.f); elliptical_billiards_button->setText("Elliptical Billiards"); elliptical_billiards_button->setCallback([this] () { requestStackPop(); requestStackPush(States::Elliptical_Billiards); });
    
    tearable_cloth_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 5.f); tearable_cloth_button->setText("Tearable Cloth"); tearable_cloth_button->setCallback([this] () { requestStackPop(); requestStackPush(States::Tearable_Cloth); });
    
    master_exit_button->setPosition(viewSize.x * 0.3f, viewSize.y * spacing * 6.f); master_exit_button->setText("Exit Simulator"); master_exit_button->setCallback([this] () { requestStackPop(); });
    
    mGUIContainer.pack(double_pendulum_button); mGUIContainer.pack(triple_pendulum_button); mGUIContainer.pack(butterfly_effect_button); mGUIContainer.pack(elliptical_billiards_button); mGUIContainer.pack(tearable_cloth_button); mGUIContainer.pack(master_exit_button);
    
}

void MainMenuState::draw() { sf::RenderWindow &window = *getContext().window; window.setView(window.getDefaultView()); window.draw(mBackgroundSprite); window.draw(mDisplayText); window.draw(mCaptionText); window.draw(mGUIContainer); }

bool MainMenuState::update(sf::Time deltaTime) { return true; }

bool MainMenuState::handleEvent(const sf::Event &event) { mGUIContainer.handleEvent(event); return false; }