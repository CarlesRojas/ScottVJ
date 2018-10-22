#ifndef _BACKGROUND_INCLUDE
#define _BACKGROUND_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Box.h"

class Background
{

public:
	static Background *createBackground(const int lvlNum, const glm::vec2 windowSize, ShaderProgram *program);
	Background(const int lvlNum, const glm::vec2 windowSize, ShaderProgram *program);
	void render();
	void update(int deltaTime, glm::vec2 camPos);
	void free();

	glm::vec2 getSize();
	vector<Box *> walls;

private:
	GLuint vao, vbo;
	ShaderProgram *program;
	vector<float> vertices;
	GLint posLocation, texCoordLocation;
	glm::vec2 tileTexSize, backgroundSize, winSize, posDispl, textDispl;
	Texture texture;
	int numHorizontalTiles, numTilesVisible, firstTile;

};

#endif // _BACKGROUND_INCLUDE