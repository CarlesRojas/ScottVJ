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

class Level
{

public:

	Level();
	~Level();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

	// Render
	float currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;

	// Components
	Physics *physics;
	Background *background;
	Camera *cam;
	UI *ui;
	Player *player;
	vector<Enemy*> enemies;

	// Level Info
	int character, lvl;
};


#endif // _SCENE_INCLUDE

