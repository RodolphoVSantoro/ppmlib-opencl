# About PPM
PPM is one of the most simple ways to store uncompressed images.

It's similar to a csv, with it's contents being the pixel values

# About this lib
This is a fork from my original ppmlib using opencl

Since image manipulation are heavily comprised of matrix manipulation, using gpus can greatly improve the lib's processing speed

Opencl is the alternative i chose to do the gpu computations, since it may support a greater number of gpus than cuda
