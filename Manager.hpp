#pragma once

#define MANAGER_HPP	

#include <vector>
#include <memory>	

#include "EntityFr.hpp"
#include "daRender.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"
#include "Singleton.hpp"
#include "Utils.hpp"



class EntityFr;

class Manager
{

public:

	
	Manager();

	virtual ~Manager()
	{
		
		for (auto e: entities_)
		{
			delete e;
		}
	}

	//Only one instance of the entity manager can exist
	static Manager& getInstance()
	{
		static Manager instance;
		return instance;
	}

	//disable the copy constructor
	Manager(const Manager&) = delete;
	Manager& operator = (const Manager&) = delete;

	//methods

	virtual EntityFr* addEnts();
	virtual void Update();
	virtual void Refresh();
	virtual void Render();

	EntityFr* getEntity(const std::string& name);

private:

	EntityFr* ent;

	std::vector<EntityFr*> entities_;

};
