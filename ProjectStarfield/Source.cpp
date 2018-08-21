// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;
vector<vec3> stars(1000);
const int f = SCREEN_HEIGHT / 2;
int t;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS
void Update()
{
	int t2 = SDL_GetTicks();
	float dt = float(t2 - t);
	t = t2;

	for (int s = 0; s<stars.size(); ++s)
	{
		//Add code for update of stars
		stars[s].z = stars[s].z - 0.002*dt;

		if (stars[s].z <= 0)
			stars[s].z += 1;
		if (stars[s].z > 1)
			stars[s].z -= 1;
	}
}

int main(int argc, char* argv[])
{
	t = SDL_GetTicks();

	for (int i = 0; i < stars.size(); ++i)
	{
		float x = float(rand()) / float(RAND_MAX) * 2 - 1;
		float y = float(rand()) / float(RAND_MAX) * 2 - 1;
		float z = float(rand()) / float(RAND_MAX) * 2 - 1;
		stars[i].x = x;
		stars[i].y = y;
		stars[i].z = z;
	}

	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (NoQuitMessageSDL())
	{
		Update();
		Draw();
	}
	SDL_SaveBMP(screen, "screenshot.bmp");
	return 0;
}

void Draw()
{
	//Fills the screen in black
	SDL_FillRect(screen, 0, 0);

	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	for (size_t s = 0; s < stars.size(); ++s)
	{
		int x = f * stars[s].x / stars[s].z + SCREEN_WIDTH / 2;
		int y = f * stars[s].y / stars[s].z + SCREEN_HEIGHT / 2;
		vec3 color = 0.5f* vec3(1, 1, 1) / (stars[s].z * stars[s].z);
		PutPixelSDL(screen, x, y, color);
	}

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);

}