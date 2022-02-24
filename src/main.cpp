#include <iostream>

#include "Game/Tournament.h"
#include "Game/Game.h"
#include "Output/ConsoleOutput.h"
#include "Output/NullOutput.h"
#include "Player/ConsoleInputPlayer.h"
#include "Player/RandomPlayer.h"
#include "Player/SmartPlayer.h"

#include <chrono>
#include <memory>

void tournament()
{
    NullOutput nullOutput;
    std::vector<std::shared_ptr<AbstractPlayer>> players;
    players.emplace_back(std::make_shared<SmartPlayer>("Smart Player"));
    for (char i = 'A'; i <= 'Z'; i++)
        players.emplace_back(std::make_shared<RandomPlayer>(std::string(1, i)));
    Tournament c{{6, 6}, players, 10000, nullOutput};

    auto outcome = c.run();
    ConsoleOutput{}.showTournamentEnd(outcome);
    std::cout << "Games: " << (players.size() * (players.size() - 1)) << std::endl;
}

int main()
{
    const auto startTime = std::chrono::high_resolution_clock::now();

    tournament();

    const auto endTime = std::chrono::high_resolution_clock::now();
    const double duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Duration: " << duration << " ms" << std::endl;
    return 0;
}
