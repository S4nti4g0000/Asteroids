#pragma once

#include "daRender.hpp"
#include "Manager.hpp"
#include "EntityFr.hpp"

class AsteroidManager
{
public:
	AsteroidManager(Manager* mngr)
		:mngr_(mngr)
	{}

	inline void CreateAst(int n);
	inline void addAsteroid();
	inline void destroyAllAsteroid();
	inline void onCollision(EntityFr* col);

private:

	EntityFr* ast;
	Manager* mngr_;

	SDL_Rect src_ = { 32,32,64,64 };

	std::vector<EntityFr*>asteroids_;

};