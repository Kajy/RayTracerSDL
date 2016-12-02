#include "RT.h"
#include "RT_Scene.h"
#include "RT_Pixel.h"
#include "RT_Sphere.h"
#include "RT_Plane.h"
#include "RT_Screen.h"

typedef struct dataThread
{
	RT_Window	*window;
	RT_Scene	*scene;
	RT_Screen	*screen;
	int			limitMin;
	int			limitMax;
}				dataThread_t;

uint32_t	Antialiasing(RT_Scene const &scene, int x, int y)
{
	RT_Intersec		tmp_inter;
	tmp_inter = scene.checkCollisionAll(x, y);
	int tmp = sqrt(ANTIALIASING);
	float sub = 1./ ANTIALIASING;
	float R = 0, G = 0, B = 0;
	int x2 = 1;
	int y2;
		while (x2 <= tmp) {
			y2 = 1;
			while (y2 <= tmp) {
				tmp_inter = scene.checkCollisionAll(x + sub * x2, y + sub * y2);
				R += ((tmp_inter.getColor() & 0xff000000) >> 24);
				G += ((tmp_inter.getColor() & 0x00ff0000) >> 16);
				B += ((tmp_inter.getColor() & 0x0000ff00) >> 8);
				++y2;
			}
			++x2;
	}
	R /= ANTIALIASING;
	G /= ANTIALIASING;
	B /= ANTIALIASING;
	return (((unsigned int)R << 24) + ((unsigned int)G << 16) + ((unsigned int)B << 8));
}

void	test_light(RT_Scene *scene)
{
	RT_Sphere	*testSphere = new RT_Sphere(0, -20, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere2 = new RT_Sphere(0, 0, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere3 = new RT_Sphere(0, 20, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere4 = new RT_Sphere(0, -40, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere5 = new RT_Sphere(0, 40, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere6 = new RT_Sphere(0, -60, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere7 = new RT_Sphere(0, 60, 0, 10, 0xFFFF0000);
	RT_Sphere	*testSphere8 = new RT_Sphere(0, 0, 20, 10, 0xFFFF0000);
	RT_Sphere	*testSphere9 = new RT_Sphere(0, 0, -20, 10, 0xFFFF0000);
	RT_Sphere	*testSphere10 = new RT_Sphere(0, -20, 20, 5, 0x00FFFF00);
	RT_Sphere	*testSphere11 = new RT_Sphere(0, 20, 20, 5, 0x00FFFF00);
	RT_Sphere	*testSphere12 = new RT_Sphere(0, -20, -20, 5, 0x00FFFF00);
	RT_Sphere	*testSphere13 = new RT_Sphere(0, 20, -20, 5, 0x00FFFF00);
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
	scene->addLightOnScene(-300, 0, 0, 0xFFFFFFFF, 0.5);
	//scene->addLightOnScene(-30, -100, 50, 0xFFFFFFFF);
}

void	calcAll(dataThread_t *data)
{
	for (int y = 0; y < RES_Y; ++y)
	{
		for (int x = data->limitMin; x < data->limitMax; ++x)
		{
			if (ANTIALIASING == 1) {
				RT_Intersec inter = data->scene->checkCollisionAll(x, y);
				data->screen->setColor(x, y, inter.getColor());
			}
			else {
				data->screen->setColor(x, y, Antialiasing(*(data->scene), x, y));
			}
		}
	}
}

void	drawAll(RT_Pixel *pixel, RT_Screen *screen)
{
	for (int y = 0; y < RES_Y; ++y)
	{
		for (int x = 0; x < RES_X; ++x)
		{
			pixel->setColor(screen->getColor(x, y));
			pixel->drawPixel(x, y);
		}
	}
	SDL_RenderPresent(pixel->getRenderer());
}

void	calcThread(RT_Window *window, RT_Scene *scene, RT_Screen *screen, RT_Pixel *pixel, std::thread *tabThreads)
{
	for (int i = 0; i < NB_THREAD; ++i) {
		dataThread_t	*data = new dataThread_t;

		data->scene = scene;
		data->window = window;
		data->screen = screen;
		data->limitMin = (RES_X / NB_THREAD) * i;
		data->limitMax = (RES_X / NB_THREAD) * (i + 1);
		tabThreads[i] = std::thread(calcAll, data);
	}
	for (int i = 0; i < NB_THREAD; ++i)
		tabThreads[i].join();
	drawAll(pixel, screen);
}

int		main(int ac, char **av)
{
	RT_Window	*window= new RT_Window("Raytracer", RES_X, RES_Y);
	RT_Scene	*scene = new RT_Scene;
	RT_Screen	*screen = new RT_Screen;
	RT_Pixel	*pixel = new RT_Pixel(window);
	std::thread		tabThreads[NB_THREAD];

	scene->setCamera(-500, 0, 0);

	test_light(scene);

	calcThread(window, scene, screen, pixel, tabThreads);
	while (1) {
		SDL_Event	ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
				return 1;
			else if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y + 0.1, scene->getCamera()._z);
				calcThread(window, scene, screen, pixel, tabThreads);
			}
			else if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y - 0.1, scene->getCamera()._z);
				calcThread(window, scene, screen, pixel, tabThreads);
			}
			else if (ev.key.keysym.scancode == SDL_SCANCODE_UP) {
				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y, scene->getCamera()._z + 0.1);
				calcThread(window, scene, screen, pixel, tabThreads);
			}
			else if (ev.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				scene->setCamera(scene->getCamera()._x, scene->getCamera()._y, scene->getCamera()._z - 0.1);
				calcThread(window, scene, screen, pixel, tabThreads);
			}
		}
	}
	return (0);
}