#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Vector2D.hpp"
#include <array>

#include "Math.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "Component.hpp"
#include "ecs.hpp"
#include "Manager.hpp"
#include "daRender.hpp"

class Component;

class EntityFr
{

public:

	EntityFr(TransformComponent* transform, SDL_Texture* texture, Manager* manager, float velocity)
		:tCompo_(transform), entTexture(texture), mngr_(manager), velocity_(velocity), aliveBoi(true)
	{
		Vector2D pos = transform->getPosition();
		SDL_Rect cFrame = transform->getSize();

		cComps_.reserve(maxCompId);

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
	inline void getComponent(cmpId_type cId)
	{
		return static_cast<T*>(compId_[cId]);
	}

	inline bool hasComponent(cmpId_type cId)
	{
		return compId_[cId] != nullptr;
	}

	//Call update and render of all components

	inline void updateC()
	{
		auto n = cComps_.size();
		for (auto i = 0u; i < n; i++)
		{
			cComps_[i]->Update();
		}
	}

	inline void renderC()
	{
		auto n = cComps_.size();
		for (auto i = 0u; i < n; i++)
		{
			cComps_[i]->Render();
		}
	}

private:

	TransformComponent* tCompo_;

	Vector2D* pos;
	SDL_Texture* entTexture;
	SDL_Rect* cFrame;
	Manager* mngr_;

	float velocity_;
	bool aliveBoi;

	std::vector<Component*> cComps_;
	std::array<Component*, maxCompId> compId_;

};