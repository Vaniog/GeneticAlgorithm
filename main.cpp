#include <iostream>
#include "GraphicsManager/Space.h"
#include "SpaceManager.h"
#include "GeneticAlgorithmCore/Evolution.h"

int main() {
    Space space;
    SpaceManager space_manager(space);
    space_manager.FillByTag(SpaceManager::Mode::MENU);
    space.Start();
    Evolution("a.txt","b.txt",10);
}
