#pragma once

#include "Component.hpp"
#include "Manager.hpp"

void Component::Render()
{

}

void Component::Update()
{}

//Transform Component--

void TransformComponent::initComponent()
{
	
	position_.setX(0);
	position_.setY(0);
	velocity_.setX(0);
	velocity_.setY(0);
	width_ = 32;
	height_ = 32;
	angle_ = 0;

}

void TransformComponent::Update(EntityFr& ent)
{
	position_.setX(x_);
	position_.setY(y_);
	
	velocity_.setX(vX_);
	velocity_.setY(vX_);

	position_ = position_ + velocity_;



	Vector2D pos = getPosition();

	//cout << "if this shit's updating, then I should see this fckng message somewhere" << endl;

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