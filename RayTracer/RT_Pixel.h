#ifndef RT_PIXEL_H_
#define RT_PIXEL_H_

#include "RT.h"
#include "RT_Window.h"

namespace RT {

	class Window;

	class Pixel
	{
	public:
		Pixel(RT::Window *window);
		~Pixel();

		SDL_Renderer	*getRenderer() const;
		void			setColor(uint32_t tmp_color);
		void			drawPixel(int x, int y) const;

	private:
		SDL_Renderer	*_Renderer;
	};
}

#endif // !RT_PIXEL_H_