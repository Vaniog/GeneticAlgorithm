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
            space << new Background();
            space << new ExitButton("size_x:6% size_y:5% "
                                    "pos_x:5%  pos_y:3% "
                                    "out_color:#ca3299  fill_color:#ffffffef  out_thick:0.3% "
                                    "text_string:'exit'  char_size:2.5% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "text_color:#ca3299 ", space);
            space << new StartButton("size_x:25% size_y:20% "
                                     "pos_x:50%  pos_y:50% "
                                     "out_color:#ca3299  fill_color:#ffffffef  out_thick:1% "
                                     "text_string:'play'  char_size:8% "
                                     "font_path:'../Resources/Fonts/statsFont.ttf' "
                                     "text_color:#ca3299 ", *this);
        } else if (tag == "PLAY") {
            space << new MenuButton("size_x:6% size_y:5% "
                                    "pos_x:5%  pos_y:3% "
                                    "out_color:#ca3299  fill_color:#ffffffef  out_thick:0.3% "
                                    "text_string:'menu'  char_size:2.5% "
                                    "font_path:'../Resources/Fonts/statsFont.ttf' "
                                    "text_color:#ca3299 ", *this);
            space << new SceneGraphic("size_y: 100% "
                                      "pos_x:50% pos_y:50%");
        }
    }
};