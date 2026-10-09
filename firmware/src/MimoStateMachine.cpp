#include "MimoStateMachine.hpp"

bool MimoStateMachine::handleEvent(MimoEvent event) {
    MimoState nextState = currentState;

    switch (currentState)
    {
        
        case MimoState::Idle:
            if (event == MimoEvent::WakeWordDetected)
            {
                nextState = MimoState::Listening;
            }
            else if (event == MimoEvent::SleepRequested)
            {
                nextState = MimoState::Sleeping;
            }
            break;

        case MimoState::Listening:
            if (event == MimoEvent::CommandReceived)
            {
                nextState = MimoState::Thinking;
            }
            else if (event == MimoEvent::Timeout)
            {
                nextState = MimoState::Idle;
            }
            break;
        
        case MimoState::Thinking:
            if (event == MimoEvent::ProcessingComplete)
            {
                nextState = MimoState::Idle;
            }
            break;
        
        case MimoState::Sleeping:
            if (event == MimoEvent::WakeWordDetected)
            {
                nextState = MimoState::Listening;
            }
            break;
            
    }
    if (nextState == currentState) {
        return false;
    }

    currentState = nextState;
    return true;
}

MimoState MimoStateMachine::getCurrentState() const {
    return currentState;
}

const char* stateToString(MimoState state) {
    switch(state) {
        case MimoState::Idle:
            return "Idle";
        
        case MimoState::Listening:
            return "Listening";

        case MimoState::Thinking:
            return "Thinking";
        
        case MimoState::Sleeping:
            return "Sleeping";
    }

    return "Unknown";
}