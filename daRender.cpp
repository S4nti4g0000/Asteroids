

#include "daRender.hpp"
#include "EntityFr.hpp"



rWindow::rWindow(const char* daWindowTitle, int daWidth, int daHeight)
	:window(NULL), renderer_(NULL)
{

	//Spawns the window on screen using the pointer defined in the hpp file
	//first parameter title, then the on-screen position (x,y), then proportions
	//lastly Uint32 flags, in this case, window states (shown, fullscreen, minimized, maximized, etc...)
	//other flags here: https://wiki.libsdl.org/SDL2/SDL_WindowFlags

	window = SDL_CreateWindow(daWindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, daWidth, daHeight, SDL_WINDOW_SHOWN);

	//"2D rendering context for a window"
	//takes the just defined window, then the rendering driver (if set to -1 will take the default one)
	//then flags.
	//other renderer flags: https://wiki.libsdl.org/SDL2/SDL_RendererFlags

	renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer_ != nullptr);

	if (window == NULL)
	{
		cout << "Who turned off the lights?! Oh no, the window failed to init. CODE: " << SDL_GetError() << endl;
	}

	daWidth_ = daWidth;
	daHeight_ = daHeight;

}


/*SDL_Texture* rWindow::loadTexture(const char* daPath)
{

	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer_, daPath);

	if (texture == NULL)
	{
		cout << "Nope, the texture did not load. CODE: " << SDL_GetError() << endl; 
	}

	return texture;

}*/

int rWindow::getRefreshRate()
{

	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;

}

void rWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void rWindow::clearScreen()
{
	//"Clear the current rendering target with the drawing color."

	SDL_RenderClear(renderer_);
}

void rWindow::daRender(EntityFr& texture)
{
	//"Copy a portion of the texture to the current rendering target."
	//Receives the rendering context, then source texture
	
	//src stands for source, dst stands for destination

	SDL_Rect src;

	src.x = texture.getwReckd().x;
	src.y = texture.getwReckd().y;
	src.w = texture.getwReckd().w;
	src.y = texture.getwReckd().h;

	SDL_Rect dst;

	dst.x = texture.getPos().getX();
	dst.y = texture.getPos().getY();
	dst.w = texture.getwReckd().w;
	dst.h = texture.getwReckd().h;
	
	//If src and dsl values are null it will fill the screen


}

void rWindow::display()
{
	//Updates the rendering context

	SDL_RenderPresent(renderer_);
}

/*void rWindow::getWidth()
{

	SDL_GetWindowSurface(window)->w;

}

void rWindow::getHeight()
{

	SDL_GetWindowSurface(window)->h;

}*/

