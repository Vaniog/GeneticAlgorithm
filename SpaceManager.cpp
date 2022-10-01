#include "SpaceManager.h"

void SpaceManager::FillByTag(const SpaceManager::Mode mode){
    modes.push_back(mode);
    space.Clear();
    switch (mode) {
        case Mode::MENU:
            space << new ExitButton(space);
            space << new StartButton(*this);
            break;
        case Mode::PLAY:
            space << new MenuButton(*this);
            break;
    }
}