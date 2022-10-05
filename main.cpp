#include <iostream>
#include "GraphicsManager/Space.h"
#include "SpaceManager.h"

int main() {
    Space space;
    SpaceManager space_manager(space);
    space_manager.FillByTag(SpaceManager::Mode::MENU);
    space.Start();
    evolution("a.txt","b.txt");
}
