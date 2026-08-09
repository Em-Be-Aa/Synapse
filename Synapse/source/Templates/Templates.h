#pragma once
#include "../Managers/UpdateManager.h"
#include <functional>
#include <memory>
#include <vector>

// Make this a template so delegate with different inputs and outputs can instantiate it
template<typename... Args>
class Delegate
{

public:

	void Subscribe(std::function<void(Args...)> functor)
	{
		subscribers.push_back(functor);
	};

	void Broadcast(Args... payload) const
	{
		for (const auto& subscriber : subscribers)
		{
			subscriber(payload...);
		}
	};


private:

	std::vector<std::function<void(Args...)>> subscribers;

};

// change this name to be generic...also this is not the right way to register objects and actors.....i have to manually paste this code for abilities and manager and such that need update....figure this out...
template<typename T, typename... Args>
T* SpawnActor(Args&&... args)
{
	std::unique_ptr<T> actor(new T(std::forward<Args>(args)...));
	T* rawPtr = actor.get(); 
	UpdateManager::GetUpdateManager().Register(std::move(actor)); 
	rawPtr->Init(); 
	return rawPtr; 
}