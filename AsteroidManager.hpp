#pragma once

#include "daRender.hpp"
#include "Manager.hpp"
#include "EntityFr.hpp"


class AsteroidManager
{
public:
	AsteroidManager(EntityFr* ent, Manager* mngr_)
	{}

	inline void CreateAst(int n);
	inline void addAsteroid();
	inline void destroyAllAsteroid();
	inline void onCollision(EntityFr* col);

private:

	Manager* mngr_;

};