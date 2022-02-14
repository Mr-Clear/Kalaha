#include <iostream>

#include "Game/Game.h"
#include "Output/ConsoleOutput.h"


int main()
{
    ConsoleOutput output;
    Game g{6, 4, output};
    return 0;
}
