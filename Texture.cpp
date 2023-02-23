#include "Texture.hpp"

Texture& Texture::Texture::operator=(Texture&& other) noexcept
{
	this->~Texture();
	Texture_ = other.Texture_;
	other.Texture_ = nullptr;

	renderer_ = other.renderer_;
	other.renderer_ = nullptr;

	tWidth_ = other.tWidth_;
	tHeight_ = other.tHeight_;

	return *this;
}

Texture::Texture(Texture&& other) noexcept
{
	Texture_ = other.Texture_;
	other.Texture_ = nullptr;

	renderer_ = other.renderer_;
	other.renderer_ = nullptr;

	tWidth_ = other.tWidth_;
	tHeight_ = other.tHeight_;
}

Texture::Texture(SDL_Renderer* renderer, const std::string& Path)
{

	assert(renderer != nullptr);
	SDL_Surface* imgSurface = IMG_Load(Path.c_str());

	Texture_ = SDL_CreateTextureFromSurface(renderer, imgSurface);

	tWidth_ = imgSurface->w;
	tHeight_ = imgSurface->h;
	renderer_ = renderer;

	SDL_FreeSurface(imgSurface);

}