#include "RT.h"

#define FOV 100
#define RES_X 1280
#define RES_Y 720

int main(int ac, char **av)
{
	RT_Window	*window = new RT_Window("Raytracer", RES_X, RES_Y);

	RT_Pixel	*pixel = new RT_Pixel(window);
	RT_Vector3df	*camera = new RT_Vector3df(-300, 0, 0);
	RT_Vector3df	*screen = new RT_Vector3df(0, 0, 0);
	RT_Vector3df	*vect = new RT_Vector3df(0, 0, 0);

	float a, b, c, d;
	float k;
	pixel->setColor(255, 0, 0);
	
	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{
			screen->setValue(FOV, (RES_X / 2) - x, (RES_Y / 2) - y);
			vect->setValue(screen->_x - camera->_x, screen->_y - camera->_y, screen->_z - camera->_z);
			vect->normalize();
			a = (vect->_x * vect->_x) + (vect->_y * vect->_y) + (vect->_z * vect->_z);		
			b = 2 * ((camera->_x * vect->_x) + (camera->_y * vect->_y) + (camera->_z * vect->_z));
			c = (camera->_x * camera->_x) + (camera->_y * camera->_y) + (camera->_z * camera->_z) - (150 * 150);
			d = (b * b) - (4 * a * c);

			k = (-b + sqrt(d)) / (2 * a);
			if (k > 0) {
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