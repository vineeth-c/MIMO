#pragma once

enum class MimoState {
    Idle,
    Listening,
    Thinking,
    Sleeping
};

enum class MimoEvent {
    WakeWordDetected,
    CommandReceived,
    ProcessingComplete,
    Timeout,
    SleepRequested
};

const char* stateToString(MimoState state);

class MimoStateMachine {
    public:
        bool handleEvent(MimoEvent event);
        MimoState getCurrentState() const;

    private:
        MimoState currentState = MimoState::Idle;
};