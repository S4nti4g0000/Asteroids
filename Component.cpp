#pragma once

#include "Component.hpp"


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

Image::~Image()
{
	delete texture_;
}

void TransformComponent::Update(EntityFr& ent)
{
	position_ = position_ + velocity_;
}

void Image::initComponent()
{
	transform_: entity_->getComponent<TransformComponent>(_Transform);
	assert(transform_ != nullptr);

}

void Image::Render()
{
	SDL_Rect dest = b_rect(transform_->getPosition(), transform_->getW(), transform_->getH());

	texture_->render(dest, transform_->getAngle());

}
