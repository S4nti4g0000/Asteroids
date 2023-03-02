#include "Manager.hpp"
#include "EntityFr.hpp"

using namespace ecs;

class Manager;

Manager::Manager()
{
	entities_.reserve(100);
}

EntityFr* Manager::addEnts(grpId_type gId = ecs::_grp_General)
{
	EntityFr* e = new EntityFr();
	//std::unique_ptr<EntityFr> uPtr{ e };

	e->setAlive(true);
	e->setContext(this);

	groups_[gId].push_back(e);
	return e;
}

const auto& Manager::getEntities(grpId_type gId = ecs::_grp_General)
{
	return groups_[gId];
}

void Manager::Refresh()
{
	entities_.erase
	(
		std::remove_if(entities_.begin(), entities_.end(), [](EntityFr* e)
		{
			if (e->isAlive())
			{
				return false;
			}
			else {
				delete e;
				return true;
			}
		}),
		entities_.end()

	);
}


void Manager::Update()
{
	for (auto& ent : groups_)
	{
		auto n = entities_.size();
		for (auto i = 0; i < n; i++)
		{
			entities_[i]->updateC();
		}
	}	
}

void Manager::Render()
{
	for (auto& ent : groups_)
	{
		auto n = entities_.size();
		for (auto i = 0; i < n; i++)
		{
			entities_[i]->updateC();
		}
	}	
}


EntityFr* Manager::getEntity(const std::string& name)
{
	for (auto entity : entities_)
	{
		if (entity->getName() == name)
		{
			return entity;
		}
	}

	return nullptr;
}

