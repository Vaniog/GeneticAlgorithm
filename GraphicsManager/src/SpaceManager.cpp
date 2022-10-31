#include "../include/SpaceManager.h"
#include "../../Objects/include/Background.h"
#include "../../Objects/include/SceneGraphic.h"
#include "../../Objects/include/Button.h"

void SpaceManager::FillByTag(const std::string& tag) {
    Space& space = Space::GetInstance();
    space.SaveParams();
    space.Clear();
    space << new Button("width:80% height:30% "
                        "pos_x:50%  pos_y:30% "
                        "out_color:#ca3299  fill_color:#ffffffef  out_thick:1% "
                        "text_string:'Override SpaceManager::FillByTag in your own class'  "
                        "char_size:4% "
                        "font_path:'../Resources/Fonts/statsFont.ttf' "
                        "text_color:#ca3299 ");
}
