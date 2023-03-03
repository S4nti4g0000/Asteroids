#include "daRender.hpp"
#include "EntityFr.hpp"
#include "Utils.hpp"
#include "../AYYLaNavesitaLol/ecs.hpp"
#include "../AYYLaNavesitaLol/Component.hpp"
#include "../AYYLaNavesitaLol/Texture.hpp"
#include "../AYYLaNavesitaLol/Manager.hpp"
#include "AsteroidManager.hpp"

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

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "Bro, your video failed somewhere! CODE: " << SDL_GetError() << endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout << "Dude there's an error with the image! CODE: " << SDL_GetError() << endl;

	auto& ren = *rWindow::instance();

	SDL_Window* window = SDL_CreateWindow("Epic Space Game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = ren.renderer();

	//SDL_Renderer* renderer = window.renderer();


	Texture shipTexture(renderer, "resources/ShipSprites/Ship1.png");
	//Texture asteroidTexture(renderer, "resources/images/AstImg.png");


	int winWidth = 800;
	int winHeight = 600;

	auto x1 = 0;
	auto y1 = 0;
	auto vX = 1;
	auto vY = 1;

	//-----

	auto &ih = *InputHandler::instance();
	auto& tm = *TextureManager::instance();

	Bullet* b;

	//Textures

	auto shipTx = new Texture(renderer, "resources/ShipSprites/Ship1.png");
	//auto astTx = new Texture(renderer, "resources/images/asteroid.png");

	tm.loadTexture(renderer, "resources/images/asteroid.png", "one");

	//Manager

	auto man_ = new Manager();
	auto manB_ = new Manager();
	EntityFr* ship = man_->addEnts(_grp_General);
	auto bullet = manB_->addEnts(_grp_Bullets);
	AsteroidManager astMngr(man_);

	
	
	//auto bullet = man_->addEnts();

	//Ship components

	auto shipComp = ship->addComponent<TransformComponent>(_Transform, ship , 0, 64, 64);
	ship->addComponent<Image>(_frmImage, ship ,shipTx);
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

	astMngr.CreateAst(10);
	
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

		ren.clearScreen();
		man_->Update();
		man_->Render();
		ship->updateC();
		ship->renderC();
		//shipComp->Update(*ship);
		//bulletComp->Update(*bullet);
		//astComp->Render();

		ren.display();

		/**/

		
		int frTicks = SDL_GetTicks() - Ticks;

		if (frTicks < 1000 / ren.getRefreshRate())
		{

			SDL_Delay(1000 / ren.getRefreshRate() - frTicks);

		}
		man_->Refresh();

	}

	SDL_DestroyWindow(window);
	ren.cleanUp();
	SDL_Quit();

	return 0;
}

