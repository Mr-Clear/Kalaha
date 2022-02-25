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
    for (char i = '1'; i <= '9'; ++i)
    {
        players.emplace_back(std::make_shared<SmartPlayer>("Smart Player " + std::string(1, i)));
    }

    std::unique_ptr<AbstractLayer> l1{std::make_unique<FullyConnectedLayer>(6, 8)};
    std::unique_ptr<AbstractLayer> l2{std::make_unique<FunctionLayer>(8, gelu)};
    std::unique_ptr<AbstractLayer> l3{std::make_unique<FullyConnectedLayer>(8, 6)};
    Ai baseAi;
    baseAi.addLayer(l1);
    baseAi.addLayer(l2);
    baseAi.addLayer(l3);

    for (char i = 'A'; i <= 'Z'; ++i)
    {
        Ai playerAi = baseAi;
        playerAi.mutate(2);
        players.emplace_back(std::make_shared<AiPlayer>(std::string(1, i), playerAi));
    }
    for (char i = '1'; i <= '9'; ++i)
    {
        players.emplace_back(std::make_shared<RandomPlayer>("Random Player " + std::string(1, i)));
    }

    int generation = 0;
    float stddev = 1;
    while(stddev > 0.001)
    {
        ++generation;
        Tournament c{{6, 6}, players, 10000, nullOutput};
        auto outcome = c.run();
        players.clear();

        auto sorted = outcome;
        std::sort(sorted.begin(), sorted.end(), [ ] (const Tournament::Outcome &a, const Tournament::Outcome &b) {
            return std::make_pair(a.wins, a.totalSones) > std::make_pair(b.wins, b.totalSones);
        });

        int selected = 0;
        for (const auto &p : sorted)
        {
            auto aiP = std::dynamic_pointer_cast<AiPlayer>(p.player);
            if (aiP)
            {
                if (selected < 3)
                {
                    players.emplace_back(p.player);
                    for (char i = '1'; i < '4'; ++i)
                    {
                        Ai nai = aiP->ai();
                        nai.mutate(stddev);
                        players.emplace_back(std::make_shared<AiPlayer>(aiP->name() + std::string(1, i), nai));
                    }
                    ++selected;
                }
            }
            else
                players.emplace_back(p.player);
        }

        ConsoleOutput{}.showTournamentEnd(outcome);
        std::cout << "Generation: " << generation << "; Mutation Rate: " << stddev << "; Games: " << (players.size() * (players.size() - 1)) << std::endl;
        stddev /= 1.1;
    }
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
