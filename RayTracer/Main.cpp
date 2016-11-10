#include "RT.h"

int main(int ac, char **av)
{
	RT_Window	*window = new RT_Window("Raytracer", RES_X, RES_Y);

	RT_Pixel	*pixel = new RT_Pixel(window);
	RT_Scene	*scene = new RT_Scene();
	RT_Vector3df *vect = new RT_Vector3df(0, 0, 0);

	scene->setCamera(-300, 0, 0);
	pixel->setColor(255, 0, 0);
	
	RT_Sphere	*testSphere = new RT_Sphere(100);
	RT_Sphere	*testSphere2 = new RT_Sphere(50);
	
	scene->addObjectOnScene(testSphere);
	scene->addObjectOnScene(testSphere2);
	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{
			vect->setValue(FOV - scene->getCamera()->_x, ((RES_X / 2) - x) - scene->getCamera()->_y, ((RES_Y / 2) - y) - scene->getCamera()->_z);
			float k = scene->checkCollisionAll(vect, scene->getCamera());
			if (k > 0)
			{
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