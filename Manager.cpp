#include "Manager.hpp"
#include "EntityFr.hpp"

class Manager;

Manager::Manager()
{
	entities_.reserve(100);
}

EntityFr* Manager::addEnts()
{
	EntityFr* e = new EntityFr();
	//std::unique_ptr<EntityFr> uPtr{ e };

	e->setAlive(true);
	e->setContext(this);

	entities_.push_back(e);
	return e;
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
	auto n = entities_.size();
	for (auto i = 0; i < n; i++)
	{
		entities_[i]->updateC();
	}
}

void Manager::Render()
{
	auto n = entities_.size();
	for (auto i = 0; i < n; i++)
	{
		entities_[i]->updateC();
	}
}

virtual ~Manager::Manager()
{
	
}



