#include "AsteroidManager.hpp"

//auto& ren_ = *rWindow::instance();

int AsteroidManager::CreateAst(int n)
{
	
	for (int i = 0; i < n; i++)
	{
		auto AstEnt = mngr_->addEnts(_grp_Asteroids);
		auto astComp = AstEnt->addComponent<AsteroidComp>(_AsteroidC, AsteroidComp::a);
		AstEnt->addComponent<TransformComponent>(_Transform, AstEnt, 0, 32, 32);
		//AstEnt->addComponent<Image>(_frmImage, AstEnt, texture_);
		//AstEnt->addComponent<framedImage>(_framed, tex, src_, 6, 50);
	}
}

void AsteroidManager::addAsteroid()
{

}

void AsteroidManager::destroyAllAsteroid()
{

}

void AsteroidManager::onCollision(EntityFr* col)
{

}
