#ifndef GENETICALGORITHM_EVOLUTION_H
#define GENETICALGORITHM_EVOLUTION_H

#endif //GENETICALGORITHM_EVOLUTION_H

#include <string>
#include <vector>
#include <iostream>
#include "Scene.h"

void Evolution(std::string old_generetion_file_name, std::string new_generetion_file_name, int numeber_of_battles);

std::vector <Bot> Battle(std::vector <Bot> bots);

std::vector <Bot> Mutation(std::vector <Bot> bots);


