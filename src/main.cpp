#include <iostream>

#include "AI/Ai.h"
#include "AI/FullyConnectedLayer.h"
#include "AI/FunctionLayer.h"
#include "Game/Tournament.h"
#include "Game/Game.h"
#include "Output/ConsoleOutput.h"
#include "Output/NullOutput.h"
#include "Player/AiPlayer.h"
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

    std::unique_ptr<AbstractLayer> l1{std::make_unique<FullyConnectedLayer>(6, 8)};
    std::unique_ptr<AbstractLayer> l2{std::make_unique<FunctionLayer>(8, gelu)};
    std::unique_ptr<AbstractLayer> l3{std::make_unique<FullyConnectedLayer>(8, 6)};
    Ai baseAi;
    baseAi.addLayer(l1);
    baseAi.addLayer(l2);
    baseAi.addLayer(l3);

    for (char i = 'A'; i <= 'Z'; i++)
    {
        Ai playerAi = baseAi;
        playerAi.mutate(2);
        players.emplace_back(std::make_shared<AiPlayer>(std::string(1, i), playerAi));
    }
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
