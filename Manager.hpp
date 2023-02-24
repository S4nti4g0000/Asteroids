#pragma once

#define MANAGER_HPP	

#include "daRender.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"
#include "Singleton.hpp"
#include "Utils.hpp"

#include <vector>
#include <memory>

#include "EntityFr.hpp"

class EntityFr;

class Manager
{


public:

	
	Manager();
	virtual ~Manager();

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

	inline EntityFr* addEnts();
	inline void Update();
	inline void Refresh();
	void Render();

private:

	EntityFr* ent;

	std::vector<EntityFr*> entities_;

};
