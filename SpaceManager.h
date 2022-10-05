#ifndef GENETICALGORITHM_SPACEMANAGER_H_
#define GENETICALGORITHM_SPACEMANAGER_H_

#include "GraphicsManager/Space.h"


class SpaceManager {
public:
    enum Mode{
        MENU, PLAY
    };
    std::vector<Mode> modes;
    Space& space;
    explicit SpaceManager(Space& space) : space(space) {
    }
    void FillByTag(const Mode mode);
};



#endif //GENETICALGORITHM_SPACEMANAGER_H_
