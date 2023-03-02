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

//texture manager

bool TextureManager::loadTexture(SDL_Renderer* renderer, const std::string& path, const std::string& id)
{
	Texture* texture = new Texture(renderer, path);
	if (texture == nullptr) {
		std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
		return false;
	}

	textureMap_[id] = texture;
	return true;
}

void TextureManager::draw(const std::string& id, const SDL_Rect& src, const SDL_Rect& dest, double angle, const SDL_Point* center, SDL_RendererFlip flip)
{
	auto it = textureMap_.find(id);
	if (it == textureMap_.end()) {
		std::cerr << "Failed to find texture: " << id << std::endl;
		return;
	}

	Texture* texture = it->second;
	texture->render(src, dest, angle, center, flip);
}

void TextureManager::draw(const std::string& id, const SDL_Rect& src, const SDL_Rect& dest)
{
	draw(id, src, dest, 0.0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::draw(const std::string& id, int x, int y)
{
	auto it = textureMap_.find(id);
	if (it == textureMap_.end()) {
		std::cerr << "Failed to find texture" << id << std::endl;
	}
}
