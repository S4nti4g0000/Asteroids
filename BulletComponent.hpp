#pragma once

#include "EntityFr.hpp"
#include "Component.hpp"
#include "daRender.hpp"
#include "Texture.hpp"
#include "Utils.hpp"

class Bullet : public Component
{

public:

	Bullet(EntityFr* ent, float speed, int w, int h)
		:entity_(ent), speedB_(speed), wWidth_(w), hHeight_(h)
	{
	}

	void initComponent();
	virtual void UpdateB(EntityFr* ent);

private:

	EntityFr* entity_;
	Vector2D bPos_;

	float speedB_;
	int wWidth_;
	int hHeight_;

};
