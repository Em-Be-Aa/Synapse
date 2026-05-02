#pragma once


class IInputObserver
{
public:
    virtual void onInputAction(int Key) = 0;
};