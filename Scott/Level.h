#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "UI.h"
#include "Texture.h"
#include "Physics.h"
#include "Screen.h"

class Level
{

public:

	Level();
	~Level();

	static Level * createLevel(int character, int difficulty, int lvl, ShaderProgram * program);
	Level(int character, int difficulty, int lvl, ShaderProgram * program);

	void update(int deltaTime);
	void render();

	void gameOver();
	void theEnd();

private:
	ShaderProgram * program;

	// Components
	Background *background;
	UI *ui;
	Player *player;
	vector<Enemy*> enemies;

	// Level Info
	int character, lvl, difficulty;
};


#endif // _SCENE_INCLUDE

