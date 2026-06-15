#pragma once
#include <string>

class IAnimate {

public:

	virtual void PlayAnimation(std::string animationTag) = 0;

};