#ifndef INTERPOLATION_NOISE_H
#define INTERPOLATION_NOISE_H
#include <stdlib.h>
#include <stdint.h>

#define IN_RANDOMFLOAT ((rand()%100)/100.f)

void interpolation_noise(float** ret, uint16_t size, uint16_t frequency, float* corners){ //Size represents the size of the array. Frequency represents the space between the random pixels (lower frequency, more randomness)
  if(size%frequency != 0 || size == 0 || frequency == 0 || frequency > size){
    return;
  }
  uint16_t y, x;

  for(y=0;y<size;y++){
    if(y%frequency == 0 || y == size - 1){
      for(x=0;x<size;x++){
        if(x%frequency == 0 || x == size - 1){
          if(corners != NULL){
            if(x == 0 && y == 0 && corners[0] >= 0.0f && corners[0] <= 1.0f){
              ret[y][x] = corners[0];
              continue;
            }

            if(x == 0 && y == size - 1 && corners[1] >= 0.0f && corners[1] <= 1.0f){
              ret[y][x] = corners[1];
              continue;
            }

            if(x == size - 1 && y == 0 && corners[2] >= 0.0f && corners[2] <= 1.0f){
              ret[y][x] = corners[2];
              continue;
            }

            if(x == size - 1 && y == size - 1 && corners[3] >= 0.0f && corners[3] <= 1.0f){
              ret[y][x] = corners[3];
              continue;
            }
          }
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
}
#endif //INTERPOLATION_NOISE_H
