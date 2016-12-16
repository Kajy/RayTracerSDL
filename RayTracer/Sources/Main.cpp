#include "RT.h"
#include "RT_Scene.h"
#include "RT_Sphere.h"
#include "RT_Plane.h"
#include "RT_Image.h"





void	test_light(RT::Scene *scene)
{
	RT::Sphere	*testSphere = new RT::Sphere(0, -20, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere2 = new RT::Sphere(0, 0, 0, 10, 0xFF000000);
	RT::Sphere	*testSphere3 = new RT::Sphere(0, 20, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere4 = new RT::Sphere(-100, 0, 20, 10, 0xFFFF0000);
	/*RT::Sphere	*testSphere4 = new RT::Sphere(0, -40, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere5 = new RT::Sphere(0, 40, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere6 = new RT::Sphere(0, -60, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere7 = new RT::Sphere(0, 60, 0, 10, 0xFFFF0000);
	RT::Sphere	*testSphere8 = new RT::Sphere(0, 0, 20, 10, 0xFFFF0000);
	RT::Sphere	*testSphere9 = new RT::Sphere(0, 0, -20, 10, 0xFFFF0000);
	RT::Sphere	*testSphere10 = new RT::Sphere(0, -20, 20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere11 = new RT::Sphere(0, 20, 20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere12 = new RT::Sphere(0, -20, -20, 5, 0x00FFFF00);
	RT::Sphere	*testSphere13 = new RT::Sphere(0, 20, -20, 5, 0x00FFFF00);*/
	RT::Plane	*testPlane = new RT::Plane(0, 0, 1, -15, 0xFFFFFFFF);

	scene->addObjectOnScene(testSphere);
	scene->addObjectOnScene(testSphere3);
	scene->addObjectOnScene(testSphere2);
	scene->addObjectOnScene(testSphere4);
	/*scene->addObjectOnScene(testSphere5);
	scene->addObjectOnScene(testSphere6);
	scene->addObjectOnScene(testSphere7);
	scene->addObjectOnScene(testSphere8);
	scene->addObjectOnScene(testSphere9);
	scene->addObjectOnScene(testSphere10);
	scene->addObjectOnScene(testSphere11);
	scene->addObjectOnScene(testSphere12);
	scene->addObjectOnScene(testSphere13);*/
	scene->addObjectOnScene(testPlane);
	scene->addLightOnScene(-200, 0, 100, 0xFFFFFFFF);
	//scene->addLightOnScene(-30, -100, 50, 0xFFFFFFFF);
}

void	test_4k(RT::Scene *scene)
{
	RT::Sphere	*testSphere2 = new RT::Sphere(0, 0, 0, 50, 0xFFFF0000);
	scene->addLightOnScene(-300, 0, 0, 0xFFFFFFFF);
	scene->addObjectOnScene(testSphere2);
}

void	cleanScreen(RT::Window *window)
{
	for (int y = 0; y < RES_Y; y++)
	{
		for (int x = 0; x < RES_X; x++)
		{
			window->drawPixel(0, x, y);
		}
	}
	SDL_RenderPresent(window->getRenderer());
}

void	drawAll(RT::Window *window, RT::Image *screen, int testEcart = TEST_ECART)
{
	//cleanScreen(window);
	for (int y = 0; y < RES_Y; y += testEcart)
	{
		for (int x = 0; x < RES_X; x += testEcart)
		{
			window->drawPixel(screen->getColor(x, y), x, y);
			if (testEcart > 1) {
				window->drawPixel(screen->getColor(x, y), x - 1, y);
				window->drawPixel(screen->getColor(x, y), x + 1, y);
				window->drawPixel(screen->getColor(x, y), x, y + 1);
				window->drawPixel(screen->getColor(x, y), x, y - 1);
			}
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

	int testEcart = 8;
	int test = 0;
	while (1) {
		SDL_Event	ev;
		while (SDL_PollEvent(&ev)) {
			testEcart = 4;
			if (test >= 1000000 && (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_DOWN))
				cleanScreen(window);	
			if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
				return 1;
			else if (ev.key.keysym.sym == SDLK_LEFT) {

				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y + MOVESPEED, scene->getCamera()._z);
				image->calcThread(scene);
				drawAll(window, image);
			}
			else if (ev.key.keysym.sym == SDLK_RIGHT) {
				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y - MOVESPEED, scene->getCamera()._z);
				image->calcThread(scene);
				drawAll(window, image);
			}
			else if (ev.key.keysym.sym == SDLK_UP) {
				scene->setCamera(scene->getCamera()._x + MOVESPEED * 5, scene->getCamera()._y, scene->getCamera()._z);
				image->calcThread(scene);
				drawAll(window, image);
			}
			else if (ev.key.keysym.sym == SDLK_DOWN) {
				scene->setCamera(scene->getCamera()._x - MOVESPEED * 5, scene->getCamera()._y, scene->getCamera()._z);
				image->calcThread(scene);
				drawAll(window, image);
			}
			test = 0;
		}
		//test = false;
		if (testEcart >= 1 && test >= 1000000) {
			image->calcThread(scene, testEcart);
			drawAll(window, image, testEcart);
			testEcart = testEcart == 1 ? 0 : testEcart;
			testEcart /= 2;			
		}
		test++;
	}
	return (0);
}