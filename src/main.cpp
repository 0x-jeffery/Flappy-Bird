#include <iostream>
#include "DEFINITIONS.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include <string>

using namespace std;
int main(int argc, char *argv[]){
    omi::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    return EXIT_SUCCESS;
}
