#include "RT.h"
#include "RT_Scene.h"
#include "RT_Sphere.h"
#include "RT_Plane.h"
#include "RT_Image.h"





void	test_light(RT::Scene *scene)
{
	RT::Sphere	*testSphere = new RT::Sphere(0, -20, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere2 = new RT::Sphere(0, 0, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere3 = new RT::Sphere(0, 20, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere4 = new RT::Sphere(0, -40, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere5 = new RT::Sphere(0, 40, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere6 = new RT::Sphere(0, -60, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere7 = new RT::Sphere(0, 60, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere8 = new RT::Sphere(0, 0, 20, 10, 0xFFFF0000);
	RT::Sphere	*testSphere9 = new RT::Sphere(0, 0, -20, 10, 0xFFFF0000);
	RT::Sphere	*testSphere10 = new RT::Sphere(0, -20, 20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere11 = new RT::Sphere(0, 20, 20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere12 = new RT::Sphere(0, -20, -20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere13 = new RT::Sphere(0, 20, -20, 5, 0x00FFFF00);
	//RT_Plane	*testPlane = new RT_Plane(1, 0, 0, 10, 0xFFFFFFFF);

	scene->addObjectOnScene(testSphere);
	scene->addObjectOnScene(testSphere2);
	scene->addObjectOnScene(testSphere3);
	scene->addObjectOnScene(testSphere4);
	scene->addObjectOnScene(testSphere5);
	scene->addObjectOnScene(testSphere6);
	scene->addObjectOnScene(testSphere7);
	scene->addObjectOnScene(testSphere8);
	scene->addObjectOnScene(testSphere9);
	scene->addObjectOnScene(testSphere10);
	scene->addObjectOnScene(testSphere11);
	scene->addObjectOnScene(testSphere12);
	scene->addObjectOnScene(testSphere13);
	//scene->addObjectOnScene(testPlane);
	scene->addLightOnScene(-300, 0, 0, 0xFFFFFFFF);
	//scene->addLightOnScene(-30, -100, 50, 0xFFFFFFFF);
}



void	drawAll(RT::Window *window, RT::Image *screen)
{
	for (int y = 0; y < RES_Y; ++y)
	{
		for (int x = 0; x < RES_X; ++x)
		{
			window->drawPixel(screen->getColor(x, y), x, y);
		}
	}
	SDL_RenderPresent(window->getRenderer());
}



int		main(int ac, char **av)
{
	RT::Window	*window= new RT::Window("Raytracer", RES_X, RES_Y);
	RT::Scene	*scene = new RT::Scene;	

	scene->setCamera(-500, 0, 0);
	test_light(scene);

	RT::Image	*image = new RT::Image(scene);

	drawAll(window, image);
	while (1) {
		SDL_Event	ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
				return 1;
		}
	}
	return (0);
}