#pragma once

#include "daRender.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"
#include "Singleton.hpp"
#include "Utils.hpp"
#include "EntityFr.hpp"

class EntityFr;

class Manager
{


public:

	//Constructor and destructor set to be empty with "default"
	Manager() = default;
	virtual ~Manager() = default;

	//Only one instance of the entity manager can exist
	static Manager& getInstance()
	{
		static Manager instance;
		return instance;
	}

	//disable the copy constructor
	Manager(const Manager&) = delete;
	Manager& operator = (const Manager&) = delete;

	inline EntityFr& addEnts()
	{
		EntityFr* e = new EntityFr();
		//std::unique_ptr<EntityFr> uPtr{ e };

		entities_.push_back(e);
		return e;
	}

	void Update()
	{
		
	}
	void Refresh()
	{

	}
	void Render()
	{

	}
private:

	EntityFr* ent;

	std::vector<EntityFr*> entities_;

};