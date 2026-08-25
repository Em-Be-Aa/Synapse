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
		std::erase_if(PreUpdateObjects, [](const std::unique_ptr<Object>& O) {
			return O->isPendingDestroy;
			});

		std::erase_if(UpdateObjects, [](const std::unique_ptr<Object>& O) {
			return O->isPendingDestroy;
			});

		std::erase_if(PostUpdateObjects, [](const std::unique_ptr<Object>& O) {
			return O->isPendingDestroy;
			});
	}

	void RegisterPreUpdateObject(std::unique_ptr<Object> registerObject)
	{
		PendingPreUpdateObjects.push_back(std::move(registerObject));
	};

	void RegisterUpdateObject(std::unique_ptr<Object> registerObject)
	{
		PendingUpdateObjects.push_back(std::move(registerObject));
	};

	void RegisterPostUpdateObject(std::unique_ptr<Object> registerObject)
	{
		PendingPostUpdateObjects.push_back(std::move(registerObject));
	};

	void FlushPending()
	{
		for (auto& registerObject : PendingPreUpdateObjects)
		{
			PreUpdateObjects.push_back(std::move(registerObject));
		}

		for (auto& registerObject : PendingUpdateObjects)
		{
			UpdateObjects.push_back(std::move(registerObject));
		}

		for (auto& registerObject : PendingPostUpdateObjects)
		{
			PostUpdateObjects.push_back(std::move(registerObject));
		}

		PendingPreUpdateObjects.clear();
		PendingUpdateObjects.clear();
		PendingPostUpdateObjects.clear();
	}

	std::vector<std::unique_ptr<Object>> PreUpdateObjects;
	std::vector<std::unique_ptr<Object>> UpdateObjects;
	std::vector<std::unique_ptr<Object>> PostUpdateObjects;



private: 

	UpdateManager() {};

	// Objects should only be added into registered objects list before or after the frame update function so nothing crashes
	std::vector<std::unique_ptr<Object>> PendingPreUpdateObjects;
	std::vector<std::unique_ptr<Object>> PendingUpdateObjects;
	std::vector<std::unique_ptr<Object>> PendingPostUpdateObjects;



};

