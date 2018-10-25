#include "Load.h"

void Load::init()
{
	// Screens
	screens.loadFromFile("sprites/screens/screens_960x540.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screens.setWrapS(GL_CLAMP_TO_EDGE);
	screens.setWrapT(GL_CLAMP_TO_EDGE);
	screens.setMinFilter(GL_NEAREST);
	screens.setMagFilter(GL_NEAREST);

	// Backgrounds
	lvl0.loadFromFile("sprites/background/lvl0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lvl0.setWrapS(GL_CLAMP_TO_EDGE);
	lvl0.setWrapT(GL_CLAMP_TO_EDGE);
	lvl0.setMinFilter(GL_NEAREST);
	lvl0.setMagFilter(GL_NEAREST);

	lvl1.loadFromFile("sprites/background/lvl1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lvl1.setWrapS(GL_CLAMP_TO_EDGE);
	lvl1.setWrapT(GL_CLAMP_TO_EDGE);
	lvl1.setMinFilter(GL_NEAREST);
	lvl1.setMagFilter(GL_NEAREST);

	lvl2.loadFromFile("sprites/background/lvl2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lvl2.setWrapS(GL_CLAMP_TO_EDGE);
	lvl2.setWrapT(GL_CLAMP_TO_EDGE);
	lvl2.setMinFilter(GL_NEAREST);
	lvl2.setMagFilter(GL_NEAREST);

	// Characters
	scott.loadFromFile("sprites/scott/scott_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scott.setWrapS(GL_CLAMP_TO_EDGE);
	scott.setWrapT(GL_CLAMP_TO_EDGE);
	scott.setMinFilter(GL_NEAREST);
	scott.setMagFilter(GL_NEAREST);

	kim.loadFromFile("sprites/kim/kim_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	kim.setWrapS(GL_CLAMP_TO_EDGE);
	kim.setWrapT(GL_CLAMP_TO_EDGE);
	kim.setMinFilter(GL_NEAREST);
	kim.setMagFilter(GL_NEAREST);

	// Enemies
	malcolm.loadFromFile("sprites/malcolm/malcolm_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	malcolm.setWrapS(GL_CLAMP_TO_EDGE);
	malcolm.setWrapT(GL_CLAMP_TO_EDGE);
	malcolm.setMinFilter(GL_NEAREST);
	malcolm.setMagFilter(GL_NEAREST);

	roxilla.loadFromFile("sprites/roxilla/roxilla_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	roxilla.setWrapS(GL_CLAMP_TO_EDGE);
	roxilla.setWrapT(GL_CLAMP_TO_EDGE);
	roxilla.setMinFilter(GL_NEAREST);
	roxilla.setMagFilter(GL_NEAREST);

	turret.loadFromFile("sprites/turret/turret_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	turret.setWrapS(GL_CLAMP_TO_EDGE);
	turret.setWrapT(GL_CLAMP_TO_EDGE);
	turret.setMinFilter(GL_NEAREST);
	turret.setMagFilter(GL_NEAREST);

	// Bosses
}
