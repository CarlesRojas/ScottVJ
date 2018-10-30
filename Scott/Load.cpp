#include "Load.h"

void Load::init()
{
	// Screens
	screens.loadFromFile("sprites/screens/screens_960x540.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screens.setWrapS(GL_CLAMP_TO_EDGE);
	screens.setWrapT(GL_CLAMP_TO_EDGE);
	screens.setMinFilter(GL_NEAREST);
	screens.setMagFilter(GL_NEAREST);

	// UI
	boss.loadFromFile("sprites/ui/BossUI_670x110.png", TEXTURE_PIXEL_FORMAT_RGBA);
	boss.setWrapS(GL_CLAMP_TO_EDGE);
	boss.setWrapT(GL_CLAMP_TO_EDGE);
	boss.setMinFilter(GL_NEAREST);
	boss.setMagFilter(GL_NEAREST);

	ui.loadFromFile("sprites/ui/Scott_UI_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	ui.setWrapS(GL_CLAMP_TO_EDGE);
	ui.setWrapT(GL_CLAMP_TO_EDGE);
	ui.setMinFilter(GL_NEAREST);
	ui.setMagFilter(GL_NEAREST);

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

	// Outlines
	red.loadFromFile("sprites/debug/outline_red.png", TEXTURE_PIXEL_FORMAT_RGBA);
	red.setWrapS(GL_CLAMP_TO_EDGE);
	red.setWrapT(GL_CLAMP_TO_EDGE);
	red.setMinFilter(GL_NEAREST);
	red.setMagFilter(GL_NEAREST);

	green.loadFromFile("sprites/debug/outline_green.png", TEXTURE_PIXEL_FORMAT_RGBA);
	green.setWrapS(GL_CLAMP_TO_EDGE);
	green.setWrapT(GL_CLAMP_TO_EDGE);
	green.setMinFilter(GL_NEAREST);
	green.setMagFilter(GL_NEAREST);

	blue.loadFromFile("sprites/debug/outline_blue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	blue.setWrapS(GL_CLAMP_TO_EDGE);
	blue.setWrapT(GL_CLAMP_TO_EDGE);
	blue.setMinFilter(GL_NEAREST);
	blue.setMagFilter(GL_NEAREST);

	yellow.loadFromFile("sprites/debug/outline_yellow.png", TEXTURE_PIXEL_FORMAT_RGBA);
	yellow.setWrapS(GL_CLAMP_TO_EDGE);
	yellow.setWrapT(GL_CLAMP_TO_EDGE);
	yellow.setMinFilter(GL_NEAREST);
	yellow.setMagFilter(GL_NEAREST);

	scott.loadFromFile("sprites/scott/scott_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scott.setWrapS(GL_CLAMP_TO_EDGE);
	scott.setWrapT(GL_CLAMP_TO_EDGE);
	scott.setMinFilter(GL_NEAREST);
	scott.setMagFilter(GL_NEAREST);

	ramona.loadFromFile("sprites/ramona/ramona_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	ramona.setWrapS(GL_CLAMP_TO_EDGE);
	ramona.setWrapT(GL_CLAMP_TO_EDGE);
	ramona.setMinFilter(GL_NEAREST);
	ramona.setMagFilter(GL_NEAREST);

	kim.loadFromFile("sprites/kim/kim_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	kim.setWrapS(GL_CLAMP_TO_EDGE);
	kim.setWrapT(GL_CLAMP_TO_EDGE);
	kim.setMinFilter(GL_NEAREST);
	kim.setMagFilter(GL_NEAREST);
}

void Load::load(int lvl)
{
	if (lvl == 0) 
	{
		lvl0.loadFromFile("sprites/background/lvl0.png", TEXTURE_PIXEL_FORMAT_RGBA);
		lvl0.setWrapS(GL_CLAMP_TO_EDGE);
		lvl0.setWrapT(GL_CLAMP_TO_EDGE);
		lvl0.setMinFilter(GL_NEAREST);
		lvl0.setMagFilter(GL_NEAREST);

		roxanne.loadFromFile("sprites/roxanne/roxanne_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		roxanne.setWrapS(GL_CLAMP_TO_EDGE);
		roxanne.setWrapT(GL_CLAMP_TO_EDGE);
		roxanne.setMinFilter(GL_NEAREST);
		roxanne.setMagFilter(GL_NEAREST);

		roxanneWhip.loadFromFile("sprites/roxanne/roxanne_512x128.png", TEXTURE_PIXEL_FORMAT_RGBA);
		roxanneWhip.setWrapS(GL_CLAMP_TO_EDGE);
		roxanneWhip.setWrapT(GL_CLAMP_TO_EDGE);
		roxanneWhip.setMinFilter(GL_NEAREST);
		roxanneWhip.setMagFilter(GL_NEAREST);
	}
	else if (lvl == 1)
	{
		lvl1.loadFromFile("sprites/background/lvl1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		lvl1.setWrapS(GL_CLAMP_TO_EDGE);
		lvl1.setWrapT(GL_CLAMP_TO_EDGE);
		lvl1.setMinFilter(GL_NEAREST);
		lvl1.setMagFilter(GL_NEAREST);

		robot.loadFromFile("sprites/robot/robot_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		robot.setWrapS(GL_CLAMP_TO_EDGE);
		robot.setWrapT(GL_CLAMP_TO_EDGE);
		robot.setMinFilter(GL_NEAREST);
		robot.setMagFilter(GL_NEAREST);

		robotLaser.loadFromFile("sprites/robot/robot_laser_1024x64.png", TEXTURE_PIXEL_FORMAT_RGBA);
		robotLaser.setWrapS(GL_CLAMP_TO_EDGE);
		robotLaser.setWrapT(GL_CLAMP_TO_EDGE);
		robotLaser.setMinFilter(GL_NEAREST);
		robotLaser.setMagFilter(GL_NEAREST);
	}
	else
	{
		lvl2.loadFromFile("sprites/background/lvl2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		lvl2.setWrapS(GL_CLAMP_TO_EDGE);
		lvl2.setWrapT(GL_CLAMP_TO_EDGE);
		lvl2.setMinFilter(GL_NEAREST);
		lvl2.setMagFilter(GL_NEAREST);

		todd.loadFromFile("sprites/todd/todd_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		todd.setWrapS(GL_CLAMP_TO_EDGE);
		todd.setWrapT(GL_CLAMP_TO_EDGE);
		todd.setMinFilter(GL_NEAREST);
		todd.setMagFilter(GL_NEAREST);

		toddMutant.loadFromFile("sprites/todd/todd768x320.png", TEXTURE_PIXEL_FORMAT_RGBA);
		toddMutant.setWrapS(GL_CLAMP_TO_EDGE);
		toddMutant.setWrapT(GL_CLAMP_TO_EDGE);
		toddMutant.setMinFilter(GL_NEAREST);
		toddMutant.setMagFilter(GL_NEAREST);
	}

}

void Load::unload()
{
	lvl0.unload();
	lvl1.unload();
	lvl2.unload();

	robot.unload();
	robotLaser.unload();
	roxanne.unload();
	roxanneWhip.unload();
	todd.unload();
	toddMutant.unload();
}
