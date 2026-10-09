#include <iostream>
#include <string>
#include "MimoStateMachine.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--smoke-test") {
        std::cout << "MIMO startup OK\n";
        return 0;
    }

    std::cout << "MIMO Firmware Simulator Starting..\n";

    MimoStateMachine mimo;
    std::string command;

    while(true)
    {
        std::cout << "\nEnter command (wake, command, complete, sleep, timeout, exit): ";

        if(!(std::cin >> command))
        {
            break;
        }

        if(command == "exit") {
            break;
        }

        MimoEvent event;

        if (command == "wake"){
            event = MimoEvent::WakeWordDetected;
        }
        else if (command == "command"){
            event = MimoEvent::CommandReceived;
        }
        else if (command == "complete"){
            event = MimoEvent::ProcessingComplete;
        }
        else if (command == "sleep"){
            event = MimoEvent::SleepRequested;
        }
        else if (command == "timeout"){
            event = MimoEvent::Timeout;
        }
        else {
            std::cout << "unknown command\n";
            continue;
        }

        MimoState previousState = mimo.getCurrentState();

        bool accepted = mimo.handleEvent(event);

        MimoState newState = mimo.getCurrentState();

        std::cout << "[STATE] "
                  << stateToString(previousState)
                  << " -> "
                  << stateToString(newState)
                  << '\n';
        
        std::cout << "[RESULT] "
                  << (accepted ? "Accepted" : "Ignored")
                  << '\n';
        
    }
    
    std::cout << "MIMO shutting down...\n";
    return 0;
}