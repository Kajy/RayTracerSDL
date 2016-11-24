#include "RT.h"
#include "RT_Scene.h"
#include "RT_Pixel.h"
#include "RT_Sphere.h"
#include "RT_Plane.h"


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

	scene->addObjectOnScene(testSphere);
	scene->addObjectOnScene(testSphere2);
	scene->addObjectOnScene(testSphere3);
	scene->addObjectOnScene(testSphere4);
	scene->addObjectOnScene(testSphere5);
	scene->addObjectOnScene(testSphere6);
	scene->addObjectOnScene(testSphere7);
	scene->addObjectOnScene(testSphere8);
	scene->addObjectOnScene(testSphere9);
}

int main(int ac, char **av)
{
	RT_Window	window("Raytracer", RES_X, RES_Y);

	RT_Pixel	pixel(&window);
	RT_Scene	scene;

	scene.setCamera(-700, 0, 0);
	scene.addLightOnScene(-200, 50, 0, 0xFFFFFFFF);
	//scene.addLightOnScene(0, -70, 0, 0xFFFFFFFF);
	
	test_light(&scene);

	for (int x = 0; x < RES_X; ++x)
	{
		for (int y = 0; y < RES_Y; ++y)
		{
			if (ANTIALIASING == 1) {
				RT_Intersec inter = scene.checkCollisionAll(x, y);
				pixel.setColor(inter.getColor());
			}
			else {
				pixel.setColor(Antialiasing(scene, x, y));
			}
			pixel.drawPixel(x, y);
		}
	}
	SDL_RenderPresent(pixel.getRenderer());
	while (1) {
		window.waitEvent();
		if (window.checkEvent(SDL_WINDOWEVENT_CLOSE))
			return (1);
	}
	return (0);
}