#ifndef _SCREEN_INCLUDE
#define _SCREEN_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"

class Screen
{
public:
	enum ScreenAnim { S_MAIN, S_TRIA_SCOTT, S_TRIA_RAMONA , S_TRIA_KIM, S_GO_SCOTT, S_GO_RAMONA, S_GO_KIM, S_THEEND };

	static Screen * createScreen(int id, const glm::vec2 windowSize, ShaderProgram * program);
	Screen(int id, const glm::vec2 windowSize, ShaderProgram * program);

	void update(int deltaTime);
	void render();

private:
	int id;

	Texture texture;
	Sprite *sprite;

	float scaleFactor;
};

#endif //_SCREEN_INCLUDE

