#pragma once

#include <iostream>
#include <SDL.h>
#include <chrono>
#include "Singleton.hpp"

namespace utils
{

	inline float time()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;

	}
	const int NUM_KEYS = 323;
	bool keys[NUM_KEYS];
}


class InputHandler : public Singleton<InputHandler>
{

	friend Singleton<InputHandler>;

public:

	virtual ~InputHandler() {
	}
	
	inline void clearState()
	{
		IsCloseWindowEvent_ = false;
		IsKeyDownEvent_ = false;
		IsKeyUpEvent_ = false; 
	}

	inline void processInput(const SDL_Event &event)
	{
		
		switch (event.type)
		{
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;

		case SDL_KEYUP:
			onKeyUp(event);
			break;

		case SDL_WINDOWEVENT:
			handleWindowEvent(event);
			break;

		default:
			break;
		}

	}

	inline void refresh() 
	{
		SDL_Event event;

		clearState();
		while(SDL_PollEvent(&event))
		{
			processInput(event);
		}

	}

	//keyboard getters

	inline bool getKeyDown()
	{
		return IsKeyDownEvent_;
	}
	inline bool getKeyUp()
	{
		return IsKeyUpEvent_;
	}

	//check if key is down or up

	inline bool isKeyDown(SDL_Scancode key)
	{
		return getKeyDown() && kbState[key] == 1;
	}
	inline bool isKeyDown(SDL_Keycode key)
	{
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	//----

	inline bool isKeyUp(SDL_Scancode key)
	{
		return getKeyUp() && kbState[key] == 0;
	}
	inline bool isKeyUp(SDL_Keycode key)
	{
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	//----

	inline bool closeWindowEvent()
	{
		return IsCloseWindowEvent_;
	}

	//-----------

	double deltaTime()
	{
		// start time, uses static so it's only initialized once
		static auto stTime = std::chrono::high_resolution_clock::now();
		//current time
		auto cTime = std::chrono::high_resolution_clock::now();
		//convert elapsed time into float
		auto delta_ = std::chrono::duration<double, std::chrono::seconds::period>(cTime - stTime).count();
		//update
		stTime = cTime;
		
		return delta_;

	}

private:

	InputHandler()
	{
		kbState = SDL_GetKeyboardState(0);
		clearState();
	}


	// Takes an SDL_Event as Input then returns a boolean value


	inline void onKeyDown(const SDL_Event&)
	{
		IsKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&)
	{
		IsKeyUpEvent_ = true;
	}

	inline void handleWindowEvent(const SDL_Event &event)
	{
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			IsCloseWindowEvent_ = true;
			break;
		default:
			break;

		}
	}

	const Uint8* kbState;
	bool IsCloseWindowEvent_;
	bool IsKeyDownEvent_;
	bool IsKeyUpEvent_;
	//bool IsCloseWindowEvent_;
};

inline InputHandler& ih()
{
	return *InputHandler::instance();
}