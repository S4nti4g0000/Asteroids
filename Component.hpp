#pragma once

#include "EntityFr.hpp"
#include "daRender.hpp"
#include "Texture.hpp"
#include "Utils.hpp"

class EntityFr;
class Manager;

class Component
{

public:
	Component(): entity_(), manager_()
	{}

	virtual ~Component() = default;

	inline void setContext(EntityFr* ent, Manager* mngr)
	{
		entity_ = ent;
		manager_ = mngr;
	}

	virtual void Update();
	virtual void Render();
	virtual void initComponent();
	
protected:

	EntityFr* entity_;
	Manager* manager_;

};

class TransformComponent : public Component
{

public:

	TransformComponent(EntityFr* entity = nullptr, float x = 0, float y = 0, float a = 0, int w = 1, int h= 1)
		:entity_(entity), position_(Vector2D(x,y)), velocity_(Vector2D(0,0)), angle_(a), width_(w), height_(h)
	{}

	void Update(EntityFr& entity)
	{

		position_ = position_ + velocity_;

	}
	virtual void Render()
	{
	}
	void initComponent();

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

	inline float getX_(float x)
	{
		x_ = x;
	}
	
	inline float getY_(float y)
	{
		y_ = y;
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

	float x_;
	float y_;

};

class Image : public Component
{

public:

	Image(Texture* tex) : transform_(nullptr), texture_(tex)
	{
	}

private:

	TransformComponent* transform_;
	Texture* texture_;

};