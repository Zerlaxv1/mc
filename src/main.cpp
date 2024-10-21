#include "Game/Game.h"
#include <csignal>

[[noreturn]] void signalHandler(int signum) {
    std::cerr << "Interrupt signal (" << signum << ") received.\n";
    exit(signum);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    std::signal(SIGINT, signalHandler);

    Game game;
    game.run();
    return 0;
}