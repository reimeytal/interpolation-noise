#ifndef INTERPOLATION_NOISE_H
#define INTERPOLATION_NOISE_H
#include <stdlib.h>
#include <stdint.h>

#define IN_RANDOMFLOAT ((rand()%100)/100.f)

float** interpolation_noise(uint16_t size, uint16_t frequency){ //Size represents the size of the array. Frequency represents the space between the random pixels (lower frequency, more randomness)
  if(size%frequency != 0 || size == 0 || frequency == 0 || frequency > size){
    return NULL;
  }
  uint16_t y, x;

  float** ret = (float**) malloc(sizeof(float*) * size);
  for(y=0;y<size;y++){
    ret[y] = (float*) malloc(sizeof(float) * size);
    if(y%frequency == 0 || y == size - 1){
      for(x=0;x<size;x++){
        if(x%frequency == 0 || x == size - 1){
          ret[y][x] = IN_RANDOMFLOAT;
        }
      }
    }
  }

  for(y=0;y<size;y++){
    if(y%frequency == 0 || y == size-1){
      for(x=0;x<size;x++){
        if(x%frequency != 0 && x != size - 1){
          if(x+(frequency-(x%frequency)) == size){
            ret[y][x] = ret[y][x-(x%frequency)] + (((ret[y][size-1] - ret[y][x-(x%frequency)])/frequency) * (x%(frequency)));//interpolate the x values
          } else{
            ret[y][x] = ret[y][x-(x%frequency)] + (((ret[y][x+(frequency-(x%frequency))] - ret[y][x-(x%frequency)])/frequency) * (x%(frequency)));//interpolate the x values
          }
        }
      }
    }
  }

  for(x=0;x<size;x++){
      for(y=0;y<size;y++){
        if(y+(frequency-(y%frequency)) == size){
          ret[y][x] = ret[y-(y%frequency)][x] + (((ret[size-1][x] - ret[y-(y%frequency)][x])/frequency) * (y%frequency));//interpolate the y values
        } else{
          ret[y][x] = ret[y-(y%frequency)][x] + (((ret[y+(frequency-(y%frequency))][x] - ret[y-(y%frequency)][x])/frequency) * (y%frequency));//interpolate the y values
        }
      }
  }

  return ret;
}
#endif //INTERPOLATION_NOISE_H
