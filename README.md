# GeneticAlgorithm #
---
## We are trying to repeat genetic algoritm ##
  Genetic algorithm from this youtube video: [video](https://www.youtube.com/watch?v=SfEZSyvbj2w)
  
  Graphics was written with SFML
  
---
  Building on linux:
  
    #installing cmake
    sudo apt-get install cmake

    #installing sfml library
    sudo apt-get install libsfml-dev
    
    #clone github project
    git clone https://github.com/Vaniog/GeneticAlgorithm
    cd GeneticAlgorithm
    
    #building project
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    cd ..
    
    #and launch
    ./build/GeneticAlgorithm
