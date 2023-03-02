#include "daRender.hpp"
#include "EntityFr.hpp"
#include "Utils.hpp"
#include "../AYYLaNavesitaLol/ecs.hpp"
#include "../AYYLaNavesitaLol/Component.hpp"
#include "../AYYLaNavesitaLol/Texture.hpp"
#include "../AYYLaNavesitaLol/Manager.hpp"

namespace utils
{

	inline float time()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;

	}
	const int NUM_KEYS = 323;
	extern bool keys[NUM_KEYS] = { false };
}

//#include <SDL_ttf.h>

using namespace std;


int main(int argc, const char **argv[])
{

	bool itsAlive = true;

	int* moveC = 0;

	double angle = 45.0;


	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "Bro, your video failed somewhere! CODE: " << SDL_GetError() << endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout << "Dude there's an error with the image! CODE: " << SDL_GetError() << endl;

	
	rWindow window("Epic Space Game!", 800, 600);

	SDL_Renderer* renderer = window.renderer();
	Texture shipTexture(renderer, "resources/ShipSprites/Ship1.png");
	//Texture asteroidTexture(renderer, "resources/images/AstImg.png");


	int winWidth = 800;
	int winHeight = 600;

	auto x1 = 0;
	auto y1 = 0;
	auto vX = 1;
	auto vY = 1;

	//----

	SDL_Rect src = {32,32,64,64};

	//-----

	auto &ih = *InputHandler::instance();
	auto& tm = *TextureManager::instance();

	Bullet* b;

	//Textures

	auto shipTx = new Texture(renderer, "resources/ShipSprites/Ship1.png");
	auto astTx = new Texture(renderer, "resources/images/asteroid.png");

	tm.loadTexture(renderer, "resources/images/asteroid.png", "one");

	//Manager

	auto man_ = new Manager();
	auto manB_ = new Manager();
	EntityFr* ship = man_->addEnts();
	EntityFr* asteroid = man_->addEnts();
	auto bullet = manB_->addEnts();

	//auto bullet = man_->addEnts();

	//Ship components

	auto shipComp = ship->addComponent<TransformComponent>(_Transform, ship , 0, 64, 64);
	ship->addComponent<Image>(_frmImage, shipTx);
	ship->addComponent<WrapAroundComp>(_reappear, winWidth -64, winHeight - 64);

	ship->getComponent<TransformComponent>(_Transform)->setContext(ship, man_);
	ship->getComponent<Image>(_frmImage)->setContext(ship, man_);

	ship->setName("ship");
	ship->setAlive(true);
	shipComp->setAngle(0);
	shipComp->setWidth(64);
	shipComp->setHeight(64);
	shipComp->setPosition(Vector2D(winWidth / 2, winHeight/2));
	shipComp->setContext(ship, man_);

	//asteroid

	auto astComp = asteroid->addComponent<TransformComponent>(_Transform, asteroid, 0, 32, 32);
	asteroid->setName("asteroid");
	asteroid->addComponent<framedImage>(_framed, astTx, src.x, src.y, src.w, src.h);
	asteroid->getComponent<TransformComponent>(_Transform)->setX(0);
	asteroid->getComponent<TransformComponent>(_Transform)->setY(0);

	//transform()->setPosition(Vector2D(0,0));
	SDL_Event running;	

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
		man_->Update();
		man_->Render();
		ship->updateC();
		ship->renderC();
		//shipComp->Update(*ship);
		//bulletComp->Update(*bullet);
		//astComp->Render();

		window.display();

		/**/


		int frTicks = SDL_GetTicks() - Ticks;

		if (frTicks < 1000 / window.getRefreshRate())
		{

			SDL_Delay(1000 / window.getRefreshRate() - frTicks);

		}
		man_->Refresh();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}

