#include "SpaceManager.h"
#include "Objects/include/Background.h"
#include "Objects/include/Button.h"
#include "Objects/include/SceneGraphic.h"
#include "Objects/include/ButtonNew.h"
#include "Objects/include/ButtonBest.h"

void SpaceManager::FillByTag(const SpaceManager::Mode mode) {
    modes.push_back(mode);
    space.SaveParams();
    space.Clear();
    switch (mode) {
        case Mode::MENU:
            space << new Background();
            space << new NewButton("width-% 0.1 height-% 0.05 "
                                   "pos_x-% 0.5  pos_y-% 0.1 "
                                   "out_color #ff69b4  color #ffffffaf  out_thickness-% 0.003 "
                                   "text 'Button'  char_size-p 100  font_path '../Resources/Fonts/statsFont.ttf' "
                                   "text_color #ff69b4 "); // image_path '../Resources/Images/Buttons/exitButton.png'

            space << new ButtonBest("width:10% height:3% "
                                   "pos_x:50%  pos_y:40% "
                                   "out_color:#ff69b4  fill_color:#ffffffaf  out_thick:0.3% "
                                   "text_string:'Button'  char_size:100  font_path:'../Resources/Fonts/statsFont.ttf' "
                                   "text_color:#ff69b4 ");
            //space << new ExitButton(0.05, 0.05, 0.07, space);
            //space << new StartButton(0.5, 0.5, 0.25, *this);
            break;
        case Mode::PLAY:
            space << new MenuButton(0.05, 0.05, 0.07, *this);
            space << new SceneGraphic(0.5, 0.5, 0.5);
            break;
    }
}