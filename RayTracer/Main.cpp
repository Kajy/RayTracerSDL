#include "RT.h"

int main(int ac, char **av)
{
	RT_Window	*window = new RT_Window("Raytracer", RES_X, RES_Y);

	RT_Pixel	*pixel = new RT_Pixel(window);
	RT_Scene	*scene = new RT_Scene();

	scene->setCamera(-300, 0, 0);
	scene->addLightOnScene(-300, -200, 0, 0xFFFFFFFF);
	pixel->setColor(0);
	
	RT_Sphere	*testSphere = new RT_Sphere(0, 0, 0, 5, 0xFFFF0000);
	//RT_Sphere	*testSphere2 = new RT_Sphere(0, 0, 0, 3, 0x0000FF00);
	
	scene->addObjectOnScene(testSphere);
	//scene->addObjectOnScene(testSphere2);
	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{
			RT_Intersec *inter = scene->checkCollisionAll(x, y);
			if (inter->getDist() > 0)
			{
				pixel->setColor(inter->getColor());
				pixel->drawPixel(x, y);
			}
			else {
				pixel->setColor(0xFFFFFF00);
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