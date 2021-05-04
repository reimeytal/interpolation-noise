# Interpolation Noise
A simple noise algorithm in C (+ a demo in C++)

### Algorithm
The algorithm is meant to be an alternative to Perlin Noise. The algorithm is free to use everywhere. It would be highly appreciated if you could credit me and let me know where the algorithm is used.

### Information
The function `interpolation_noise` takes in 4 parameters. They are array, size, frequency and corners respectively.

The array parameter takes in a 2D array. The size of the dimensions of the array should be the size parameter in both dimensions.

The size parameter defines the size of the dimensions of the array.

The frequency parameter changes the 'frequency' of the randomness. The number passed into it is the number of pixels in between each random pixel. It is also an unsigned 16-bit integer.

The corners parameter takes in a float array (float pointer). The array must be 4 floats long. The floats in the array represent the values of the corners of the array. If the parameter is set to ```NULL```, then the values of the corners will be randomly generated. If the value of a corner is set to a number smaller than 0 or greater than 1, then the value of the corner will be randomly generated. The order of the corners in the array are: top-left, top-right, bottom-left, bottom-right.

The `interpolation_noise.h` file has no dependencies other than the C standard library. It is not platform specific.

__Make sure to call the `srand` function (from `stdlib.h`) since the `interpolation_noise` function relies on `rand`.__

### Restrictions

* If the frequency parameter is larger than or equal to the size parameter, the function will return.
* If there is a remainder after dividing the size parameter by the frequency parameter, the function will return.
* If the frequency or size parameters are equal to 0, the function will return.

### demo.cpp

The demo.cpp file is a demo of the algorithm. It uses the [SFML library](https://www.sfml-dev.org/) to visualize the return value. The specific binaries required by the program are listed below.

_The binaries for the SFML library aren't included with this repository. Download them [here](https://www.sfml-dev.org/download.php)._

_The SFML header files are included in the `include` folder. **The `include` folder is required only by the demo.cpp file. There is no need to include it when including the `interpolation_noise.h` file in your program.**_

If you pass in `-img` as a command-line parameter to demo.cpp, it will save an image called `interpolation-noise.png` (in the current directory) instead of displaying the noise using SFML.

###### Dependencies (only for demo.cpp)
* sfml-window
* sfml-system
* sfml-graphics
* and all of the dependencies of these libraries. More information [here](https://www.sfml-dev.org/faq.php#grl-dependencies).
