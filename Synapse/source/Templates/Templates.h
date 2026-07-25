#pragma once
#include "../Managers/UpdateManager.h"
#include <functional>
#include <memory>
#include <vector>

// Make this a template so delegate with different inputs and outputs can instantiate it
template<typename In, typename Out = void>
class Delegate
{

public:

	void Subscribe(std::function<Out(In)> functor)
	{
		subscribers.push_back(functor);
	};

	void Broadcast(In payload) const
	{
		for (const auto& subscriber : subscribers)
		{
			subscriber(payload);
		}
	};


private:

	std::vector<std::function<Out(In)>> subscribers;

};

// change this name to be generic
template<typename T, typename... Args>
T* SpawnActor(Args&&... args)
{
	std::unique_ptr<T> actor(new T(std::forward<Args>(args)...));
	T* rawPtr = actor.get(); 
	UpdateManager::GetUpdateManager().Register(std::move(actor)); 
	rawPtr->Init(); 
	return rawPtr; 
}