#pragma once

#include "EntityFr.hpp"
#include "daRender.hpp"
#include "Utils.hpp"

class EntityFr;

class Component
{

public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Update();
	virtual void Render();
	
};

class TransformComponent : public Component
{

public:

	TransformComponent(EntityFr* entity = nullptr, float x = 0, float y = 0, float a = 0, int w = 1, int h= 1)
		:entity_(entity), position_(Vector2D(x,y)), velocity_(Vector2D(0,0)), angle_(a), width_(w), height_(h)
	{}

	virtual void Update(EntityFr& entity)
	{

	}
	virtual void Render()
	{

	}

	//Getters

	inline Vector2D getPosition() const
	{
		return position_;
	}
	inline SDL_Rect getSize() const
	{
		return size_;
	}
	inline float getAngle()
	{
		return angle_;
	}

	inline float getW() const
	{
		return width_;
	}

	inline float getH() const
	{
		return height_;
	}

	//Setters

	inline void setPosition(const Vector2D& position)
	{
		position_ = position;
	}

	inline void setAngle(float angle)
	{
		angle_ = angle;
	}

	inline void setWidth(float width)
	{
		width_ = width;
	}
	
	inline void setHeight(float height)
	{
		height_ = height;
	}

	virtual ~TransformComponent() {}


private:

	EntityFr* entity_;
	Vector2D position_;
	Vector2D velocity_;
	SDL_Rect size_;

	float angle_;
	int width_;
	int height_;

};