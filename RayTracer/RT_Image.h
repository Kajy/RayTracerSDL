
#ifndef RT_SCREEN_H_
#define RT_SCREEN_H_

#include "RT.h"
#include "RT_Scene.h"

namespace RT {

	class Image
	{
	public:
		Image(Scene *scene);
		~Image() {};
		void		setColor(int x, int y, uint32_t color);
		uint32_t	getColor(int x, int y);
		void		calcThread(Scene *scene);
		static void	calcAll(int limitMin, int limitMax, RT::Scene *scene, RT::Image *image);
		uint32_t	Antialiasing(RT::Scene const &scene, int x, int y);

	private:
		uint32_t	image[RES_Y][RES_X];
	};
}

#endif // !RT_SCREEN_H_

