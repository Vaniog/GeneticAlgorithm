#include "GraphicsManager/include/Space.h"
#include "MySpaceManager.h"

int main() {
    Space& space = Space::GetInstance();
    space.AddSpaceManager(new MySpaceManager);
    space.FillByTag("MENU");
    space.Start();
}