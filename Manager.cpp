#include "Manager.hpp"

EntityFr* Manager::addEnts()
{
	EntityFr* e = new EntityFr();
	//std::unique_ptr<EntityFr> uPtr{ e };

	entities_.push_back(e);
	return e;
}