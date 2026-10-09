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
    Timeout
};

class MimoStateMachine {
    public:
        void handleEvent(MimoEvent event);
        MimoState getCurrentState() const;

    private:
        MimoState currentState = MimoState::Idle;
};