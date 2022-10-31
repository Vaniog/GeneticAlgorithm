#pragma once
#include <iostream>

class SpaceManager {
public:
    explicit SpaceManager() = default;
private:
    virtual void FillByTag(const std::string &tag);
private:
    friend class Space;
};
