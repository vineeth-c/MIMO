#include "MimoStateMachine.hpp"

void MimoStateMachine::handleEvent(MimoEvent event) {
    switch (currentState)
    {
        
        case MimoState::Idle:
            if (event == MimoEvent::WakeWordDetected)
            {
                currentState = MimoState::Listening;
            }
            break;

        case MimoState::Listening:
            if (event == MimoEvent::CommandReceived)
            {
                currentState = MimoState::Thinking;
            }
            else if (event == MimoEvent::Timeout)
            {
                currentState = MimoState::Idle;
            }
            break;
        
        case MimoState::Thinking:
            if (event == MimoEvent::ProcessingComplete)
            {
                currentState = MimoState::Idle;
            }
            break;
        
        case MimoState::Sleeping:
            break;
            
    }
}

MimoState MimoStateMachine::getCurrentState() const {
    return currentState;
}