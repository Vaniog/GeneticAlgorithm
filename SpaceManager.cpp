#include "SpaceManager.h"
#include "Objects/include/Background.h"
#include "Objects/include/SceneGraphic.h"
#include "Objects/include/Button.h"

void SpaceManager::FillByTag(const SpaceManager::Mode mode) {
    modes.push_back(mode);
    space.SaveParams();
    space.Clear();
    switch (mode) {
        case Mode::MENU:
            space << new Background();
            space << new ExitButton("width:6% height:3% "
                                   "pos_x:5%  pos_y:3% "
                                   "out_color:#ff69b4  fill_color:#ffffffef  out_thick:0.3% "
                                   "text_string:'exit'  char_size:2.5% "
                                   "font_path:'../Resources/Fonts/statsFont.ttf' "
                                   "text_color:#ff69b4 ", space);
            space << new StartButton("width:25% height:10% "
                                    "pos_x:50%  pos_y:25% "
                                    "out_color:#ff69b4  fill_color:#ffffffef  out_thick:1% "
                                    "text_string:'play'  char_size:8% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "text_color:#ff69b4 ", *this);
            break;
        case Mode::PLAY:
            space << new MenuButton("width:6% height:3% "
                                    "pos_x:5%  pos_y:3% "
                                    "out_color:#ff69b4  fill_color:#ffffffef  out_thick:0.3% "
                                    "text_string:'menu'  char_size:2.5% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "text_color:#ff69b4 ", *this);
            space << new SceneGraphic(0.5, 0.5, 0.5);
            break;
    }
}