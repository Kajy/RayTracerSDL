#include <SDL.h>
#include "RT_Window.h"
#include <iostream>

int main(int ac, char **av)
{
	RT_Window	*window = new RT_Window("Raytracer", 1280, 720);

	while (1) {
		window->waitEvent();
		if (window->checkEvent(SDL_WINDOWEVENT_CLOSE))
			return (1);
	}
	return (0);
}