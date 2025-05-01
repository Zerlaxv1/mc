#include "Game/Game.h"
#include <csignal>

Game* gameInstance = nullptr;

void signalHandler(int signum) {
    std::cerr << "Interrupt signal (" << signum << ") received.\n";
    std::cerr << "Shutting down gracefully...\n";

    if (gameInstance) {
        gameInstance->stop();
    }

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    std::signal(SIGINT, signalHandler);

    Game game;
    gameInstance = &game;
    game.run();

    gameInstance = nullptr;
    return 0;
}