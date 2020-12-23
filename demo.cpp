#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "interpolation_noise.h"

#define ARR_SIZE 512

using namespace std;

int main(int argc, char** argv){
  srand(time(NULL));
  uint16_t y = 0, x = 0;
  uint64_t i;
  float** function_output = (float**)malloc(sizeof(float) * ARR_SIZE);
  for(i=0;i<ARR_SIZE;i++){
    function_output[i] = (float*)malloc(sizeof(float) * ARR_SIZE);
  }
  interpolation_noise(function_output, ARR_SIZE, 64);

  if(function_output == NULL){
    cout<<"ERROR: interpolation_noise function returned NULL."<<endl;
    return 1;
  }

  sf::Uint8* noiseimgarray = new sf::Uint8[ARR_SIZE*ARR_SIZE*4];
  for(i=0;i<ARR_SIZE*ARR_SIZE*4;i++){
    if((i+1) % 4 == 0){
      noiseimgarray[i] = function_output[y][x] * 255;
      x++;
      if(x == ARR_SIZE){
        x = 0;
        y++;
      }
    } else{
      noiseimgarray[i] = 0;
    }
  }

  for(y=0;y<ARR_SIZE;y++){
    free(function_output[y]);
  }
  free(function_output);

  sf::Image noise;
  noise.create(ARR_SIZE, ARR_SIZE, noiseimgarray);
  delete[] noiseimgarray;

  if(argc >= 2){
    if(strcmp(argv[1], "-img") == 0){
      noise.saveToFile("interpolation-noise.png");
      cout<<"Saved 'interpolation-noise.png'"<<endl;
      return 0;
    }
  }

  sf::Texture noisetexture;
  noisetexture.loadFromImage(noise);

  sf::Sprite noisesprite(noisetexture);
  noisesprite.setPosition(sf::Vector2<float>(0.f, 0.f));
  noisesprite.setScale(sf::Vector2<float>(1.f, 1.f));

  sf::RenderWindow window(sf::VideoMode(ARR_SIZE, ARR_SIZE), "Interpolation Noise Demo", sf::Style::Close | sf::Style::Titlebar);

  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      switch(event.type){
        case sf::Event::Closed:
          window.close();
      }
    }

    window.clear(sf::Color::White);
    window.draw(noisesprite);
    window.display();
  }
  return 0;
}
