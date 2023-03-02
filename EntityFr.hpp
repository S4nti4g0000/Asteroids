#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <array>
#include <algorithm>
#include <bitset>

#include "Vector2D.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "ecs.hpp"
#include "Manager.hpp"
#include "Component.hpp"
#include "daRender.hpp"

using namespace ecs;

class Component;
class TransformComponent;


class EntityFr
{

public:

	EntityFr()
		:tCompo_(), mngr_(nullptr), compId_(), aliveBoi(true)
	{

		cComps_.reserve(ecs::maxCompId);

	}

	virtual ~EntityFr()
	{
		for (auto c : cComps_)
		{
			delete c;
		}
	}

	//Getters

	Vector2D* getPos()
	{
		return pos;
	}

	inline SDL_Texture* getTex()
	{
		return entTexture;
	}

	inline SDL_Rect* getwReckd()
	{
		return cFrame;
	}

	inline float getVel()
	{
		return velocity_;
	}

	inline bool isAlive()
	{
		return aliveBoi;
	}

	//setters

	inline bool setAlive(bool alive)
	{
		aliveBoi = alive;
		return this;
	}

	inline void setContext(Manager* man)
	{
		mngr_ = man;
	}

	//Add, remove, get component

	template<typename T, typename ...Ts>
	inline T* addComponent(cmpId_type cId, Ts&&...args)
	{
		T* c = new T(std::forward<Ts>(args)...);

		removeComponent(cId);

		cComps_.push_back(c);
		compId_[cId] = c;

		c->setContext(this, mngr_);
		c->initComponent();

		return c;
	}

	inline void removeComponent(cmpId_type cId)
	{
		if (compId_[cId] != nullptr)
		{
			auto iter = std::find(cComps_.begin(), cComps_.end(), compId_[cId]);
			cComps_.erase(iter);
			delete compId_[cId];
			compId_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent(cmpId_type cId)
	{
		return static_cast<T*>(compId_[cId]);
	}


	inline bool hasComponent(cmpId_type cId)
	{
		return compId_[cId] != nullptr;
	}

	//Call update and render of all components

	void updateC();
    void renderC();

	//get the entity name

	const std::string& getName() const
	{
		return name_;
	}

	inline void setName(const std::string& name)
	{
		name_ = name;
	}
private:

	TransformComponent* tCompo_;

	Component* comp;
	Vector2D* pos;
	SDL_Texture* entTexture;
	SDL_Rect* cFrame;
	Manager* mngr_;

	std::string name_;

	float velocity_;
	bool aliveBoi;

	//----
			 
	//

	//----

	std::vector<Component*> cComps_;
	std::array<Component*, ecs::maxCompId> compId_;

};
