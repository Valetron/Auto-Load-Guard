#pragma once

class IGuard
{
public:
    IGuard() = default;
    virtual ~IGuard() = default;
    virtual void compareState() = 0;
    virtual void run() = 0;
};
