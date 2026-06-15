#pragma once


class IInputObserver
{
public:
    virtual void onInputPressed(int Key) = 0;
    virtual void onInputReleased(int Key) = 0;
    virtual void onInputClicked(int Key) = 0;
};