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
	inline void initComponent();
	
protected:

	EntityFr* entity_;
	Manager* manager_;
	Vector2D position_;
	Vector2D velocity_;

};

class TransformComponent : public Component
{

public:

	TransformComponent(EntityFr* entity, float a, int w = 1, int h= 1)
		:entity_(entity), position_(Vector2D(x_, y_)), velocity_(Vector2D(vX_, vY_)), angle_(a), targetAngle_(a), width_(w), height_(h)
	{}

	virtual void Update(EntityFr& entity);
	virtual void Render() override;
	void initComponent();

	//Getters
	Vector2D getVector2D()const 
	{
		return Vector2D();
	}

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

	inline float getvX()
	{
		return vX_;
	}

	inline float getvY()
	{
		return vY_;
	}

	Vector2D getForward()
	{
		float rad = angle_ * (M_PI / 180.0f);
		return Vector2D(std::sin(rad), -std::cos(rad)).getNormalized();
	}


	//Setters

	inline void setPosition(const Vector2D& position)
	{
		position_ = position;
	}

	inline void setVelocity(const Vector2D& v)
	{
		velocity_ = v;
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

	inline void setvX(float vx)
	{
		vX_ = vx;
	}

	inline void setvY(float vy)
	{

		vY_ = vy;
	}

	virtual ~TransformComponent() {}


	
private:

	EntityFr* entity_;
	Vector2D acceleration_;
	Vector2D position_;
	Vector2D velocity_;
	SDL_Rect size_;

	float angle_;
	float targetAngle_;
	float rotateSpeed_ = 0.5;

	float accelerationMagnitude_ = 0.1;
	float decelerationMagnitude_ = 1;
	float maxSpeed_ = 5;
	float currSpeed_ = 0;
	float friction_ = 0.95;
	//float acceleration_;
	int width_;
	int height_;

	float x_;
	float y_;

	float vX_;
	float vY_;

};

class Image : public Component
{

public:

	Image(Texture* tex) : transform_(nullptr), texture_(tex)
	{
	}
	
	Image() : transform_(nullptr), texture_(nullptr)
	{
	}

	virtual ~Image();

	void initComponent();
	virtual void Render() override;

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

	virtual void Update(EntityFr& ent);
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

class Bullet : public Component
{

public:

	Bullet(EntityFr* ent, Texture* tex)
		:entity_(ent), a(tex)
	{	
	}

	void initComponent();
	virtual void Update(EntityFr* ent);

	//getters

	inline float getSp() const
	{
		return speedB_;
	}
	inline int getWd() const
	{
		return wWidth_;
	}
	inline int getHg() const
	{
		return hHeight_;
	}

	//setters

	inline void setSP_(float vel)
	{
		speedB_ = vel;
	}
	inline void setWi_(int w)
	{
		wWidth_ = w;
	}
	inline void setHe_(int h)
	{
		hHeight_ = h;
	}

private:

	EntityFr* entity_;
	Vector2D bPos_;
	Texture* a;

	float speedB_ = 10.0f;
	int wWidth_ = 800;
	int hHeight_ = 600;

};

class WrapAroundComp : public Component
{

public:

	WrapAroundComp(int scWidth, int scHeight)
		:screenWidth_(scWidth), screenHeight_(scHeight)
	{}

	void initComponent();
	virtual void Update(EntityFr& ent);

public:


	int screenWidth_;
	int screenHeight_;

};