#include <iostream>
#include "MimoStateMachine.hpp"

int main() {
    std::cout << "MIMO Firmware Simulator Starting..\n";

    MimoStateMachine mimo;

    std::cout << "Initially Idle: "
    << (mimo.getCurrentState() == MimoState::Idle)
    << '\n';

    mimo.handleEvent(MimoEvent::WakeWordDetected);

    std::cout << "Now Listening: "
    << (mimo.getCurrentState() == MimoState::Listening)
    << '\n';
    
    if (mimo.getCurrentState() == MimoState::Listening) {
        std::cout << "MIMO is now listening...\n";
    }

    return 0;
}