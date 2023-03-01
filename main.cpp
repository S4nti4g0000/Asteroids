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

	//Error stuff----------------------------------------------------------------------------------

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "Bro, your video failed somewhere! CODE: " << SDL_GetError() << endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout << "Dude there's an error with the image! CODE: " << SDL_GetError() << endl;

	//Window creation------------------------------------------------------------------------------
	
	rWindow window("Epic Space Game!", 800, 600);
	//SDL_Window* win;

	//Texture--------------------------------------------------------------------------------------

	SDL_Renderer* renderer = window.renderer();
	Texture shipTexture(renderer, "resources/ShipSprites/Ship1.png");
	//Texture asteroidTexture(renderer, "resources/images/AstImg.png");

	//Entity---------------------------------------------------------------------------------------

	int winWidth = 800;
	int winHeight = 600;

	auto x1 = 0;
	auto y1 = 0;
	auto vX = 1;
	auto vY = 1;

	//Input Handler -------------------------------------------------------------------------------

	auto &ih = *InputHandler::instance();

	Bullet* b;

	//Textures

	auto shipTx = new Texture(renderer, "resources/ShipSprites/Ship1.png");
	auto fireTx = new Texture(renderer, "resources/images/fire.png");

	//Manager

	auto man_ = new Manager();
	auto ship = man_->addEnts();

	//auto bullet = man_->addEnts();

	//Ship components

	auto shipComp = ship->addComponent<TransformComponent>(_Transform, ship , 0, 64, 64);
	ship->addComponent<Image>(_frmImage, shipTx);
	ship->addComponent<WrapAroundComp>(_reappear, winWidth, winHeight);

	ship->setName("ship");
	ship->setAlive(true);
	shipComp->setAngle(0);
	shipComp->setWidth(64);
	shipComp->setHeight(64);
	shipComp->setPosition(Vector2D(winWidth / 2, winHeight/2));
	shipComp->setContext(ship, man_);

	//Bullet components
	

	/*auto bulletComp = bullet->addComponent<TransformComponent>(_Transform, bullet, 0, 10, 10);
	bullet->addComponent<Image>(_frmImage, fireTx);	
	bullet->addComponent<Bullet>(_bullet, bullet, 1, winWidth, winHeight);
	
	bullet->setName("bullet");
	bullet->setAlive(true);*/
	
	

	//transform()->setPosition(Vector2D(0,0));

	//Game loop------------------------------------------------------------------------------------

	SDL_Event running;	

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
		ship->renderC();
		ship->updateC();
		shipComp->Update(*ship);
		//bulletComp->Update(*bullet);

		window.display();

		/*if (ih.isKeyDown(SDL_SCANCODE_SPACE))
		{
			cout << "bullet created" << endl;

			auto bulletEnt = std::make_shared<EntityFr>();

			Vector2D cPos = ship->getComponent<TransformComponent>(_Transform)->getPosition();
			Vector2D cDir = ship->getComponent<TransformComponent>(_Transform)->getForward();

			bulletEnt->addComponent<Bullet>(_bullet, bulletEnt.get(), fireTx);
			bulletEnt->getComponent<TransformComponent>(_Transform)->setPosition(cPos);

			cPos = cPos + cDir;
			auto bulletImg = std::make_shared<Image>(fireTx);
			bulletEnt->addComponent<Image>(_frmImage, fireTx);
			bulletEnt->getComponent<TransformComponent>(_Transform)->setVelocity(cDir * 10.0f);

			man_->addEnts();

		}*/


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

