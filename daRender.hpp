
#pragma once


#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "../AYYLaNavesitaLol/EntityFr.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

#include "Singleton.hpp"
#include "Texture.hpp"

using namespace std;

class EntityFr;

//Window class and constructor to render the window with specific parameters (title and proportions)

class rWindow
{

public:

	//-----

	rWindow(const char* daWindowTitle, int daWidth, int daHeight);
	int daWidth_;
	int daHeight_;

	//-----

	//template<typename T>
	//using sdl_resources = unordered_map<string, T>;
		
	int getRefreshRate();

	void cleanUp();
	void clearScreen();
	void daRender(EntityFr& texture);
	void display();

	inline SDL_Renderer* renderer()
	{
		return renderer_;
	}

	//-----



	//virtual ~rWindow();

private:
	void initWindow();
	void closeWindow();
	void initSDLExt();
	void killAllYourFriends();

	//float width, height;

	EntityFr* entity;
	SDL_Window* window;
	SDL_Renderer* renderer_;

};
