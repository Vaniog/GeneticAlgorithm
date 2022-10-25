//
// Created by User on 01.10.2022.
//

#include "Evolution.h"

std::vector <Bot> Battle(std::vector <Bot> bots)
{
    Scene scene(bots);
    for (int i = 0; i < 1000; i++)
    {
        scene.Iteration();
        //scene.Show();
    }
    return scene.GetWinners();
}
int min(int a, int b) {
  if (a > b) {
    return b;
  }
  return a;
}