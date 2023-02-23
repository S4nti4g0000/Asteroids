#include "daRender.hpp"
#include "EntityFr.hpp"
#include "Utils.hpp"

//#include <SDL_ttf.h>

using namespace std;
using namespace utils;


int main(int argc, const char **argv[])
{

	bool itsAlive = true;

	int* moveC = 0;

	double angle = 45.0;

	//Error stuff----------------------------------------------------------------------------------

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "Bro, your video failed somewhere! CODE: " << SDL_GetError() << endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout << "Dude there's an error with the image! CODE: " << SDL_GetError() << endl;

	//Window creation------------------------------------------------------------------------------
	
	rWindow window("Epic Space Game!", 800, 600);

	//Texture--------------------------------------------------------------------------------------

	SDL_Renderer* renderer = window.renderer();
	//Texture shipTexture(renderer, "resources/ShipSprites/Ship1.png");
	//Texture asteroidTexture(renderer, "resources/images/AstImg.png");

	//Entity---------------------------------------------------------------------------------------

	auto winWidth = window.daWidth_;
	auto winHeight = window.daHeight_;
	auto x1 = 0;
	auto y1 = 0;
	auto vX = 1;
	auto vY = 1;

	Vector2D pos(x1, y1);
	Vector2D sp(0, 0);
		

	//Game loop------------------------------------------------------------------------------------

	SDL_Event running;


	//Input Handler -------------------------------------------------------------------------------

	auto &ih = *InputHandler::instance();

	

	//Performance----------------------------------------------------------------------------------

	const float tS = 0.01f;
	float acc = 0.0f;
	float cTime = utils::time();


	//GameLoop-------------------------------------------------------------------------------------

	while (itsAlive)
	{

		auto dt = ih.deltaTime();

		//----

		int Ticks = SDL_GetTicks();

		float newTime = utils::time();
		float fT = newTime - cTime;

		cTime = newTime;

		acc += fT;

		//----

		ih.refresh();

		if (ih.getKeyDown())
			cout << "Key down" << endl;
		
			

		if (ih.isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			ih.closeWindowEvent();
			itsAlive = false;
		}



		//----

		while (acc >= tS)
		{
			while (SDL_PollEvent(&running))
			{
				if (running.type == SDL_QUIT)
				{
					itsAlive = false;
				}
			}

			acc -= tS;

		}

		//ih().init();

		window.clearScreen();
	

		//shipTexture.render(x1, y1);
		if (ih.isKeyDown(SDL_SCANCODE_D))
		{
			cout << "Key is D" << endl;
			x1 = (x1 + 5) % winWidth;
		}

		window.display();

		//inputHandler_.processInput(key);

		int frTicks = SDL_GetTicks() - Ticks;

		if (frTicks < 1000 / window.getRefreshRate())
		{

			SDL_Delay(1000 / window.getRefreshRate() - frTicks);

		}

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}

