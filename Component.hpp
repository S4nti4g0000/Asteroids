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

	inline void Update();
	virtual void Render();
	inline void initComponent();
	
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

	void Update(EntityFr& entity);
	void Render();
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

	inline float getX_()
	{
		return x_;
	}
	
	inline float getY_()
	{
		return y_;
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

	inline void setX(float x)
	{
		x_ = x;
	}

	inline void setY(float y)
	{
		y_ = y;
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

	virtual ~Image();

	void initComponent();
	inline void Render() override;

	static SDL_Rect b_rect(const Vector2D& position, int width, int height)
	{
		SDL_Rect rect;
		rect.x = position.getX();
		rect.y = position.getY();
		rect.w = width;
		rect.h = height;
		return rect;
	}


private:

	TransformComponent* transform_;
	Texture* texture_;

};



class AsteroidBehaviour : public Component
{

public:

	AsteroidBehaviour(float speed, bool dmg, int h) : speed_(speed), dmg_(dmg), health_(h), entity_(nullptr)
	{}

	virtual ~AsteroidBehaviour();

	void Update(EntityFr& ent);
	inline void Render();
	void initComponent();
	void takeDmg()
	{
		health_--;
	}

	bool isDestroyed()
	{
		return health_ <= 0;
	}

	inline int getAsHealth()
	{
		return health_;
	}

private:

	EntityFr* entity_;

	float speed_;
	bool dmg_;
	int health_ = 1;

};