#pragma once
#include "GraphicsManager/include/Space.h"
#include "GraphicsManager/include/SpaceManager.h"
#include "Objects/include/Button.h"
#include "Objects/include/Background.h"
#include "Objects/include/SceneGraphic.h"

class MySpaceManager : public SpaceManager{
private:
    void FillByTag(const std::string& tag) override {
        Space& space = Space::GetInstance();
        space.Clear();
        if (tag == "MENU") {
            space << new Background("size_x:100% size_y:100%");
            space << new ExitButton("size_x:6% size_y:5% "
                                    "id:exit_button "
                                    "pos_x:5%  pos_y:3% "
                                    "color_out:#ca3299  color_fill:#ffffffef  out_thick:0.3% "
                                    "text_string:'exit'  char_size_y:4% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "color_text:#ca3299 ", space);
            space << new StartButton("size_x:20% size_y:15% "
                                     "pos_x:50%  pos_y:50% "
                                     "color_out:#ca3299  color_fill:#ffffffef  out_thick:1% "
                                     "text_string:'play'  char_size_y:10% "
                                     "font_path:'../Resources/Fonts/statsFont.ttf' "
                                     "color_text:#ca3299 ", *this);
        } else if (tag == "PLAY") {
            space << new MenuButton("size_x:6% size_y:5% "
                                    "pos_x:5%  pos_y:3% "
                                    "color_out:#ca3299  color_fill:#ffffffef  out_thick:0.3% "
                                    "text_string:'menu'  char_size_y:4% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "color_text:#ca3299 ", *this);
            space << new SceneGraphic("size_y: 100% "
                                      "pos_x:50% pos_y:50%");
        }
    }
};