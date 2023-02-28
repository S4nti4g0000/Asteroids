#pragma once

#include "Component.hpp"
#include "Manager.hpp"

auto& inH = *InputHandler::instance();

void Component::Render()
{

}

void Component::Update()
{}

//Transform Component--

void TransformComponent::initComponent()
{
	
	position_.setX(x_);
	position_.setY(y_);
	velocity_.setX(vX_);
	velocity_.setY(vY_);
	width_ = 32;
	height_ = 32;
	angle_ = 0;

}

void TransformComponent::Update(EntityFr& ent)
{

	float rad;

	if (inH.isKeyDown(SDL_SCANCODE_W))
	{
		rad = angle_ * (M_PI / 180.0);

		vX_ = sin(rad) * speed_;
		vY_ = -cos(rad) * speed_;

		velocity_.setX(vX_);
		velocity_.setY(vY_);

		// Update position with updated velocity
		position_ = position_ + velocity_;
	}
	

	if (inH.isKeyDown(SDL_SCANCODE_A))
	{
		// Update velocity if needed
		
		angle_ -= 5;
	}
	

	if (inH.isKeyDown(SDL_SCANCODE_D))
	{
		// Update velocity if needed
		
		angle_ += 5;
	}
	
	if (inH.getKeyUp())
	{
		velocity_.setX(0);
		velocity_.setY(0);
		position_ = position_ + velocity_;

	}

	//velocity_.setX(0);
	//velocity_.setY(0);

	setPosition(position_);

}

void TransformComponent::Render()
{

}

//Image component--

Image::~Image()
{
	delete texture_;
}

void Image::initComponent()
{
	transform_ = entity_->getComponent<TransformComponent>(_Transform);
	assert(transform_ != nullptr);

}

void Image::Render()
{
	SDL_Rect dest = b_rect(transform_->getPosition(), transform_->getW(), transform_->getH());

	texture_->render(dest, transform_->getAngle());


}


//Normal Asteroid logic--

void AsteroidBehaviour::initComponent()
{
	entity_ = manager_->getEntity("ship");
}

void AsteroidBehaviour::Update(EntityFr& ent)
{


}