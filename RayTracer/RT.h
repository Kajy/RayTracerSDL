#ifndef  RT_H_

#define RT_H_

#include <SDL.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <thread>
#include "RT_Window.h"

#define FOV 6000
#define RES_X 1280
#define RES_Y 720
#define COLOR_BACKGROUND 0x00000000
#define ANTIALIASING 4
#define NB_THREAD 8

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#endif // ! RT_H_
