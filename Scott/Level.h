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
#include "Physics.h"

class Level
{

public:

	Level();
	~Level();

	static Level * createLevel(int character, bool hardDifficulty, int lvl, ShaderProgram * program);
	Level(int character, bool hardDifficulty, int lvl, ShaderProgram * program);

	void update(int deltaTime);
	void render();
	vector< vector<char> > loadLevel(const string & levelFile, bool hard);
	void gameOver(int deltaTime);
	void theEnd(int deltaTime);

private:
	ShaderProgram * program;

	// Components
	Background *background;
	UI *ui;
	Player *player;
	vector<Enemy*> enemies;

	// Level Info
	int character, lvl;
	bool hardDifficulty;
	vector< vector<char> > layout;

	// Fade
	float fadeDelay;
	bool fadding;
};


#endif // _SCENE_INCLUDE

