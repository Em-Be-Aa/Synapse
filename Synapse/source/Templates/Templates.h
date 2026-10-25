#pragma once
#include "../Characters/Character.h"
#include "../Managers/UpdateManager.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Ability;



// change this name to be generic...also this is not the right way to register objects and actors.....i have to manually paste this code for abilities and manager and such that need update....figure this out...
template<typename T, typename... Args>
[[nodiscard]] std::shared_ptr<T> SpawnActor(Args&&... args)
{
	std::shared_ptr<T> actor = std::make_shared<T>(std::forward<Args>(args)...);
	actor->Init();
	UpdateManager::GetUpdateManager().RegisterUpdateObject(std::weak_ptr<T>(actor));
	return actor;
};

template<typename T>
void AddAbility(std::shared_ptr<Character> Char, std::string Tag, AbilityInfo info)
{
	std::shared_ptr<Ability> ability = std::make_shared<Ability>(Tag, Char->GetSpriteComponent().lock()->GetAnimator().lock(), Char->GetCharacterTag(), Char, info);
	UpdateManager::GetUpdateManager().RegisterPostUpdateObject(ability);
	ability->Init();
	Char->GetAbilityComponent().lock()->GetAbilities().push_back(ability);
};