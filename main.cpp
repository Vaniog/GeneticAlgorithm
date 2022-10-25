#include "GraphicsManager/include/Space.h"
#include "SpaceManager.h"
#include "GeneticAlgorithmCore/Evolution.h"

int main() {
    Space space;
    SpaceManager space_manager(space);
    space_manager.FillByTag(SpaceManager::Mode::MENU);
    space.Start();
}