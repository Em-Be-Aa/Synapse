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

	void RemovePendingDestroyObjects()
	{
		std::erase_if(RegisteredObjects, [](const std::unique_ptr<Object>& O) {
			return O->isPendingDestroy;
			});
	}

	void Register(std::unique_ptr<Object> registerObject)
	{
		PendingObjects.push_back(std::move(registerObject));
	};

	void FlushPending()
	{
		for (auto& registerObject : PendingObjects)
		{
			RegisteredObjects.push_back(std::move(registerObject));
		}

		PendingObjects.clear();
	}

	std::vector<std::unique_ptr<Object>> RegisteredObjects;



private: 

	UpdateManager() {};

	// Objects should only be added into registered objects list before or after the frame update function so nothing crashes
	std::vector<std::unique_ptr<Object>> PendingObjects;



};

