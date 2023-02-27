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