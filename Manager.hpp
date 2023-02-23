#pragma once

#include "daRender.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"
#include "Singleton.hpp"
#include "Utils.hpp"
#include "EntityFr.hpp"

class Entity;

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

	Entity* addEnts();

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

	Entity* ent;

	std::vector<Entity*> entities_;

};