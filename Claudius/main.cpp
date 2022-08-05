#include "Game.h"
#undef main

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Fatal Error!\n" << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		std::cout << "Unknown Fatal Error!" << std::endl;
		return -1;
	}
	return 0;
}

