
#ifndef RT_SCREEN_H_
#define RT_SCREEN_H_

#include "RT.h"

class RT_Screen
{
public:
	RT_Screen() {
		for (int y = 0; y < RES_Y; ++y) {
			for (int x = 0; x < RES_X; ++x) {
				screen[y][x] = 0;
			}
		}
	};
	~RT_Screen() {};
	void		setColor(int x, int y, uint32_t color) { screen[y][x] = color; }
	uint32_t	getColor(int x, int y) { return screen[y][x]; }

private:
	uint32_t	screen[RES_Y][RES_X];
};

#endif // !RT_SCREEN_H_

