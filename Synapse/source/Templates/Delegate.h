#pragma once

#include <functional>
#include <memory>
#include <string>
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