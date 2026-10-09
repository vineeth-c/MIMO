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

    MimoStateMachine validationTest;

    // valid event
    bool accepted = validationTest.handleEvent(
        MimoEvent::WakeWordDetected
    );

    assert(accepted == true);
    assert(validationTest.getCurrentState() == MimoState::Listening);

    // Invalid event while listening
    accepted = validationTest.handleEvent(
        MimoEvent::ProcessingComplete
    );

    assert(accepted == false);
    assert(validationTest.getCurrentState() == MimoState::Listening);

    // valid command
    accepted = validationTest.handleEvent(
        MimoEvent::CommandReceived
    );

    assert(accepted == true);
    assert(validationTest.getCurrentState() == MimoState::Thinking);

    std::cout << "ALL MIMO state machine tests passed.\n";
    return 0;

}