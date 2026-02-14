#include "PhySim2/Simulator/Application.hpp"
#include <iostream>

int main() {
    
    try { std::unique_ptr<Application> application = std::unique_ptr<Application>(new Application()); application->run(); }
    
    catch(std::exception &exp) { std::cout << "\nEXCEPTION: " << exp.what() << "\n"; }
    
}