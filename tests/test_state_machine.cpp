#include "MimoStateMachine.hpp"
#include <cassert>
#include <iostream>

int main() {
    MimoStateMachine mimo;

    // verify initial state
    assert(mimo.getCurrentState() == MimoState::Idle);

    // valid transition: Idle -> Listening
    mimo.handleEvent(MimoEvent::WakeWordDetected);
    assert(mimo.getCurrentState() == MimoState::Listening);

    // Invalid transition: wake word while already listening
    mimo.handleEvent(MimoEvent::WakeWordDetected);
    assert(mimo.getCurrentState() == MimoState::Listening);

    // valid transition: listening -> thinking
    mimo.handleEvent(MimoEvent::CommandReceived);
    assert(mimo.getCurrentState() == MimoState::Thinking);

    // valid transition: thinking -> idle
    mimo.handleEvent(MimoEvent::ProcessingComplete);
    assert(mimo.getCurrentState() == MimoState::Idle);

    // Timeout while listening
    mimo.handleEvent(MimoEvent::WakeWordDetected);
    mimo.handleEvent(MimoEvent::Timeout);
    assert(mimo.getCurrentState() == MimoState::Idle);

    MimoStateMachine sleepTest;

    // Idle -> sleeping
    sleepTest.handleEvent(MimoEvent::SleepRequested);
    assert(sleepTest.getCurrentState() == MimoState::Sleeping);

    // command should be ignored while sleeping
    sleepTest.handleEvent(MimoEvent::CommandReceived);
    assert(sleepTest.getCurrentState() == MimoState::Sleeping);

    // wakeword -> listening
    sleepTest.handleEvent(MimoEvent::WakeWordDetected);
    assert(sleepTest.getCurrentState() == MimoState::Listening);
    
    std::cout << "ALL MIMO state machine tests passed.\n";
    return 0;

}