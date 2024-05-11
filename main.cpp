#include<SFML/Graphics.hpp>
#include<time.h>
#include<random>
#include<vector>
#include<math.h>
#include<algorithm>
#include "Game.h"
using namespace sf;

int main(){
    srand(time(0));
    Game game;
    game.play();
    return 0;
}