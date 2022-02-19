#include <iostream>

#include "Game/Competition.h"
#include "Game/Game.h"
#include "Output/ConsoleOutput.h"
#include "Output/NullOutput.h"
#include "Player/ConsoleInputPlayer.h"
#include "Player/RandomPlayer.h"
#include "Player/SmartPlayer.h"

#include <chrono>
#include <memory>

int main()
{
    NullOutput nullOutput;
    std::shared_ptr<AbstractPlayer> playerA{std::make_shared<RandomPlayer>(PlayerNumber::One)};
    std::shared_ptr<AbstractPlayer> playerB{std::make_shared<SmartPlayer>(PlayerNumber::Two)};
    std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> playerMap{{PlayerNumber::One, playerA}, {PlayerNumber::Two, playerB}};
    Competition c{{6, 6}, playerA, playerB, 10000, nullOutput};

    const auto startTime = std::chrono::high_resolution_clock::now();
    auto outcome = c.run();
    const auto endTime = std::chrono::high_resolution_clock::now();
    ConsoleOutput{}.showCompetitionEnd(outcome);
    const double duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Duration: " << duration << " ms" << std::endl;
    return 0;
}
