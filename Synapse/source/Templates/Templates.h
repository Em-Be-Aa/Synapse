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
T* SpawnActor(Args&&... args)
{
	std::unique_ptr<T> actor(new T(std::forward<Args>(args)...));
	T* rawPtr = actor.get();
	UpdateManager::GetUpdateManager().RegisterUpdateObject(std::move(actor));
	rawPtr->Init();
	return rawPtr;
};

template<typename T>
void AddAbility(Character* Char, std::string Tag, AbilityInfo info)
{
	std::unique_ptr<Ability> ability(new T(Tag, Char->GetSpriteComponent().spriteAnimator, Char->GetCharacterTag(), Char, info));
	Ability* newAbility = ability.get();
	UpdateManager::GetUpdateManager().RegisterPostUpdateObject(std::move(ability));
	newAbility->Init();
	Char->GetAbilityComponent().GetAbilities().push_back(newAbility);
};