#include <SDL.h>
#include <math.h>
#include "RT_Pixel.h"
#include "RT_Vector.h"
#include <iostream>

#define FOV 100
#define RES_X 1280
#define RES_Y 720

int main(int ac, char **av)
{
	RT_Window	*window = new RT_Window("Raytracer", RES_X, RES_Y);

	RT_Pixel	*pixel = new RT_Pixel(window);
	RT_Vector	*camera = new RT_Vector(-300, 0, 0);
	RT_Vector	*screen = new RT_Vector(0, 0, 0);
	RT_Vector	*vect = new RT_Vector(0, 0, 0);

	int a, b, c, d;
	pixel->setColor(255, 0, 0);
	
	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{
			screen->setValue(x - (RES_X / 2), y - (RES_Y / 2), FOV);
			vect->setValue(screen->_x - camera->_x, screen->_y - camera->_y, screen->_z - camera->_z);
			a = (vect->_x * vect->_x) + (vect->_y * vect->_y) + (vect->_z * vect->_z);		
			b = 2 * ((camera->_x * vect->_x) + (camera->_y * vect->_y) + (camera->_z * vect->_z));
			c = (camera->_x * camera->_x) + (camera->_y * camera->_y) + (camera->_z * camera->_z) - (10 * 10);
			std::cout << a << b << c << std::endl;
			d = (b * b) - (4 * a * c);
			if (d >= 0) {
				pixel->drawPixel(x, y);
			}
		}
	}
	SDL_RenderPresent(pixel->getRenderer());
	while (1) {
		window->waitEvent();
		if (window->checkEvent(SDL_WINDOWEVENT_CLOSE))
			return (1);
	}
	return (0);
}