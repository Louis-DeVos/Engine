#include <Minigin.h>

#if _DEBUG
#include <vld.h>
#endif

#include "Game.h"

int main(int, char* []) {
	Game game;
	game.Run();
	return 0;
}