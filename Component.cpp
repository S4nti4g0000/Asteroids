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

void WrapAroundComp::Update()
{
	cout << "updating comp" << endl;
	Vector2D pos_ = entity_->getComponent<TransformComponent>(_Transform)->getPosition();
	if (pos_.getX() < -64)
	{
		pos_.setX(screenWidth_ + 64);
	}
	else if (pos_.getX() > screenWidth_ + 64)
	{
		pos_.setX(-64);
	}
	if (pos_.getY() < -64)
	{
		pos_.setY(screenHeight_ + 64);
	}
	else if (pos_.getY() > screenHeight_ + 64)
	{
		pos_.setY(-64);
	}

		entity_->getComponent<TransformComponent>(_Transform)->setPosition(pos_);
	
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

void TransformComponent::Update()
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
		if (currSpeed_ > 0.0f)
		{
			float decel = decelerationMagnitude_ * inH.deltaTime();
			float decelerationMag = std::min(currSpeed_, decel);
			Vector2D deceleration = acceleration_.getNormalized() * decelerationMag;
			acceleration_ = acceleration_ - deceleration;
		}

		velocity_ = velocity_ - acceleration_;
		position_ = position_ + velocity_;
	}
	
	velocity_ = velocity_ + acceleration_;
	velocity_ = velocity_ * friction_;

	position_ = position_ + velocity_;
	

	if (inH.isKeyDown(SDL_SCANCODE_A))
	{		
		angle_ -= 5;
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

void AsteroidComp::Render()
{

}

//framed image

void framedImage::initComponent()
{
	TransformComponent* tran = entity_->getComponent<TransformComponent>(_Transform);

	tran->setX(srcRect_.x);
	tran->setX(srcRect_.y);
	tran->setWidth(srcRect_.w);
	tran->setHeight(srcRect_.h);


}

void framedImage::Render(SDL_Renderer* ren, TransformComponent* trn)
{
	SDL_Rect dstRect = {

		static_cast<int>(trn->getPosition().getX()),
		static_cast<int>(trn->getPosition().getY()),
		srcRect_.w * trn->getSize().x,
		srcRect_.h * trn->getSize().y
	};

	SDL_RenderCopy(ren, frTexture_, &srcRect_, &dstRect);
}

//Bullet

void Bullet::initComponent()
{
	
}

void Bullet::Update()
{

	/*Vector2D cPos = entity_->getComponent<TransformComponent>(_Transform)->getPosition();
	Vector2D cDir = entity_->getComponent<TransformComponent>(_Transform)->getForward() * speedB_;

	//cPos = cPos + cDir;

	if (cPos.getX() > wWidth_ && cPos.getY() > hHeight_)
		entity_->setAlive(false);



	entity_->getComponent<TransformComponent>(_Transform)->setPosition(cPos);
	if (inH.isKeyDown(SDL_SCANCODE_SPACE))
	{
		cout << "bullet created" << endl;

		auto bulletEnt = std::make_shared<EntityFr>();

		Vector2D cPos = entity_->getComponent<TransformComponent>(_Transform)->getPosition();
		Vector2D cDir = entity_->getComponent<TransformComponent>(_Transform)->getForward();

		bulletEnt->addComponent<Bullet>(_bullet, bulletEnt.get());
		bulletEnt->getComponent<TransformComponent>(_Transform)->setPosition(cPos);

		cPos = cPos + cDir;

		//manager_->addEnts();

	}*/
		
}
