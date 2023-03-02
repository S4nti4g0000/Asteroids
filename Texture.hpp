#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
	/*inline SDL_Rect b_rect(const Vector2D& pos, int w, int h)
	{
		return SDL_Rect{ static_cast<int>(pos.getX(), -w / 2), static_cast<int>(pos.getY(), -h / 2) };
	}*/

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

class TextureManager: public Singleton<TextureManager>
{
	friend Singleton<TextureManager>;
public:

	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	bool loadTexture(SDL_Renderer* renderer, const std::string& path, const std::string& id);
	void clear();
	void draw(const std::string& id, const SDL_Rect& src, const SDL_Rect& dest, double angle = 0.0, const SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(const std::string& id, const SDL_Rect& src, const SDL_Rect& dest);
	void draw(const std::string& id, int x, int y);
	void draw(const std::string& id, const SDL_Rect& dest, float rotation);

private:
	TextureManager() {}
	std::unordered_map<std::string, Texture*> textureMap_;

};

inline TextureManager& tm()
{
	return *TextureManager::instance();
}