#pragma once

#include "Component.hpp"
#include "Manager.hpp"

auto& inH = *InputHandler::instance();

void Component::Render()
{

}

void Component::Update()
{}

//WrapAround--

void WrapAroundComp::Update(EntityFr& ent)
{
	entity_ = &ent;
	Vector2D pos_ = entity_->getComponent<TransformComponent>(_Transform)->getPosition();
	if (pos_.getX() < 0)
	{
		pos_.setX(screenWidth_);
	}
	else if (pos_.getX() > screenWidth_)
	{
		pos_.setX(0);
	}
	if (pos_.getY() < 0)
	{
		pos_.setY(screenHeight_);
	}
	else if (pos_.getY() > screenHeight_)
	{
		pos_.setY(0);
	}

}

void WrapAroundComp::initComponent()
{


}

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
		
		acceleration_.setX(sin(rad) * accelerationMagnitude_);
		acceleration_.setY(-cos(rad) * accelerationMagnitude_);

		currSpeed_ += acceleration_.getLength();
	
		if (currSpeed_ > maxSpeed_)
			currSpeed_ = maxSpeed_;

		velocity_ = velocity_ + acceleration_;

		position_ = position_ + velocity_;
	}
	if (inH.isKeyUp(SDL_SCANCODE_W))
	{
		float currentAccelerationMag = acceleration_.getLength();
		if (currentAccelerationMag > 0.0f)
		{
			float decel = decelerationMagnitude_ * inH.deltaTime();
			float decelerationMag = std::min(currentAccelerationMag, decel);
			Vector2D deceleration = acceleration_.getNormalized() * decelerationMag;
			acceleration_ = acceleration_ - deceleration;
		}

		velocity_ = velocity_ + acceleration_;
		position_ = position_ + velocity_;
	}
	
	velocity_ = velocity_ + acceleration_;
	velocity_ = velocity_ * friction_;

	position_ = position_ + velocity_;
	

	if (inH.isKeyDown(SDL_SCANCODE_A))
	{		
		angle_ -= 5;

		acceleration_.setX(sin(angle_ * (M_PI / 180.0)) * accelerationMagnitude_);
		acceleration_.setY(-cos(angle_ * (M_PI / 180.0)) * accelerationMagnitude_);

		velocity_ = velocity_ + acceleration_;
	}
	

	if (inH.isKeyDown(SDL_SCANCODE_D))
	{		
		angle_ += 5;
	}
	
	if (inH.getKeyUp())
	{
		currSpeed_ -= .5;

		velocity_.setX(velocity_.getX() * 0.95f);
		velocity_.setY(velocity_.getY() * 0.95f);


		position_ = position_ + velocity_;

	}

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

//Bullet

