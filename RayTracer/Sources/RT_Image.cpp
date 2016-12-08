#include "RT_Image.h"

RT::Image::Image(RT::Scene *scene)
{
	for (int y = 0; y < RES_Y; ++y) {
		for (int x = 0; x < RES_X; ++x) {
			image[y][x] = 0;
		}
	}
	calcThread(scene);
};


void		RT::Image::setColor(int x, int y, uint32_t color)
{
	image[y][x] = color;
}

uint32_t	RT::Image::getColor(int x, int y)
{
	return image[y][x];
}

void	RT::Image::calcThread(RT::Scene *scene)
{
	std::thread		tabThreads[NB_THREAD];

	for (int i = 0; i < NB_THREAD; ++i)
		tabThreads[i] = std::thread(RT::Image::calcAll, (RES_X / NB_THREAD) * i, (RES_X / NB_THREAD) * (i + 1), scene, this);
	for (int i = 0; i < NB_THREAD; ++i)
		tabThreads[i].join();

}

void	RT::Image::calcAll(int limitMin, int limitMax, RT::Scene *scene, RT::Image *image)
{
	for (int y = 0; y < RES_Y; ++y)
	{
		for (int x = limitMin; x < limitMax; ++x)
		{
			if (ANTIALIASING == 1) {	
				RT::Intersec inter = scene->checkCollisionAll((float)x, (float)y);
				image->setColor(x, y, inter.getColor());
			}
			else {
				image->setColor(x, y, image->Antialiasing(*(scene), x, y));
			}
		}
	}
}

uint32_t	RT::Image::Antialiasing(RT::Scene const &scene, int x, int y)
{
	RT::Intersec		tmp_inter;
	tmp_inter = scene.checkCollisionAll((float)x, (float)y);
	float tmp = (float)(sqrt(ANTIALIASING));
	float sub = 1. / ANTIALIASING;
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