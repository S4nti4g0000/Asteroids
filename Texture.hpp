#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>

#include "Singleton.hpp"
//#include "EntityFr.hpp"

class Texture
{

public:

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture& operator=(Texture&& other) noexcept;
	Texture(Texture&& other)noexcept;

	//Img
	Texture(SDL_Renderer* renderer, const std::string& Path);

	virtual ~Texture()
	{
		if (Texture_ != nullptr)
			SDL_DestroyTexture(Texture_);
	}

	inline int getWidth() const
	{
		return tWidth_;
	}

	inline int getHeight() const
	{
		return tHeight_;
	}


	//SDL_RenderCopyEx

	inline void render(const SDL_Rect& src, const SDL_Rect& dest, double angle, const SDL_Point* p = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		assert(Texture_ != nullptr);
		SDL_RenderCopyEx(renderer_, Texture_, &src, &dest, angle, p, flip);
	}

	//SDL_RenderCopy

	inline void render(const SDL_Rect& src, const SDL_Rect& dest)
	{
		assert(Texture_ != nullptr);
		SDL_RenderCopy(renderer_, Texture_, &src, &dest);
	}

	//(x,y)

	inline void render(int x, int y)
	{
		SDL_Rect dest = { x, y, tWidth_, tHeight_ };
		render(dest);
	}

	inline void render(const SDL_Rect& dest)
	{
		SDL_Rect src = { 0,0,tWidth_, tHeight_ };
		render(src, dest);
	}

	inline void render(const SDL_Rect& dest, float rotation)
	{
		SDL_Rect src = { 0,0,tWidth_, tHeight_ };
		render(src, dest, rotation);
	}

private:

	SDL_Texture* Texture_;
	SDL_Renderer* renderer_;
	int tWidth_;
	int tHeight_;

};