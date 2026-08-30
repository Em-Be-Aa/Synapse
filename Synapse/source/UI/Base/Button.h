#pragma once

#include "../../Interfaces/IInputObserver.h"
#include "Widget.h"

class Button : public Widget, public IInputObserver
{

public:

	void Init() override;
	void Update(double dT) override;
	void onInputPressed(int Key);
	void onInputClicked(int Key);
	void onInputReleased(int Key);

	Delegate<> OnHovered;
	Delegate<> OnUnhovered;
	Delegate<> OnClicked;

private:
	bool isHovered = false;
	bool currentlyOver = false;

};

