#pragma once

#include "EntityFr.hpp"
#include "daRender.hpp"
#include "Utils.hpp"

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

	TransformComponent(float x, float y) :position_(x,y)
	{}

	virtual void Update(EntityFr& entity)
	{

	}
	virtual void Render()
	{

	}

	inline Vector2D getPosition() const
	{
		return position_;
	}

	inline void setPosition(const Vector2D& position)
	{
		position_ = position;
	}

	virtual ~TransformComponent() {}


private:

	EntityFr entity_;
	Vector2D position_;

};