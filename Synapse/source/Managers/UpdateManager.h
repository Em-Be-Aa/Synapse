#pragma once
#include "../Actor/Object.h"
#include <memory>
#include <vector>


class UpdateManager
{
	
public:

	static UpdateManager& GetUpdateManager()
	{
		static UpdateManager UM;
		return UM;
	};

	void Register(std::unique_ptr<Object> registerObject)
	{
		RegisteredObjects.push_back(std::move(registerObject));
	};

	void RemovePendingDestroyObjects()
	{
		for (auto& O : RegisteredObjects)
		{
			std::erase_if(RegisteredObjects,
				[](const std::unique_ptr<Object>& O) { return O->isPendingDestroy; });
		}

	}

	std::vector<std::unique_ptr<Object>> RegisteredObjects;

private: 

	UpdateManager() {};

};

