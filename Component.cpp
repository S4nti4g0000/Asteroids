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
	
	position_.setX(getX_());
	position_.setY(getX_());

	width_ = 32;
	height_ = 32;
	angle_ = 0;

}

void TransformComponent::Update(EntityFr& ent)
{
	position_ = position_ + velocity_;

	Vector2D pos = getPosition();


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