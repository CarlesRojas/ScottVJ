#include "Background.h"
#include <glm/gtc/matrix_transform.hpp>


Background *Background::createBackground(const int lvlNum, const glm::vec2 windowSize, ShaderProgram * program)
{
	Background *bg = new Background(lvlNum, windowSize, program);
	return bg;
}

Background::Background(const int lvlNum, const glm::vec2 windowSize, ShaderProgram * program)
{
	this->program = program;
	texture.loadFromFile("sprites/background/lvl" + to_string(lvlNum) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
	texture.setWrapS(GL_CLAMP_TO_EDGE);
	texture.setWrapT(GL_CLAMP_TO_EDGE);
	texture.setMinFilter(GL_NEAREST);
	texture.setMagFilter(GL_NEAREST);

	winSize = windowSize;
	backgroundSize.y = winSize.y;
	numHorizontalTiles = (int)(texture.width() / 256.f);
	backgroundSize.x = backgroundSize.y * numHorizontalTiles;
	tileTexSize = glm::vec2(1.f / (float)numHorizontalTiles, 1.f);
	numTilesVisible = ceil((float)winSize.x / (float)winSize.y) + 1;

	// First triangle
	vertices.push_back(0); vertices.push_back(0);
	vertices.push_back(0); vertices.push_back(0);
	vertices.push_back(backgroundSize.y); vertices.push_back(0);
	vertices.push_back(tileTexSize.x); vertices.push_back(0);
	vertices.push_back(backgroundSize.y); vertices.push_back(backgroundSize.y);
	vertices.push_back(tileTexSize.x); vertices.push_back(tileTexSize.y);

	// Second triangle
	vertices.push_back(0); vertices.push_back(0);
	vertices.push_back(0); vertices.push_back(0);
	vertices.push_back(backgroundSize.y); vertices.push_back(backgroundSize.y);
	vertices.push_back(tileTexSize.x); vertices.push_back(tileTexSize.y);
	vertices.push_back(0); vertices.push_back(backgroundSize.y);
	vertices.push_back(0); vertices.push_back(tileTexSize.y);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));

	// Add walls
	walls.push_back(Box::createBox(Box::BACKGROUND, Box::BASE, -backgroundSize.x * 0.1f, 0.f, -backgroundSize.y * 0.1f, backgroundSize.y + backgroundSize.y * 0.1f)); // Left
	walls.push_back(Box::createBox(Box::BACKGROUND, Box::BASE, backgroundSize.x * 0.95f, backgroundSize.x + backgroundSize.x * 0.1f, -backgroundSize.y * 0.1f, backgroundSize.y + backgroundSize.y * 0.1f)); // Right
	walls.push_back(Box::createBox(Box::BACKGROUND, Box::BASE, -backgroundSize.x * 0.1f, backgroundSize.x + backgroundSize.x * 0.1f, -backgroundSize.y * 0.02f, backgroundSize.y * 0.53f)); // Top
	walls.push_back(Box::createBox(Box::BACKGROUND, Box::BASE, -backgroundSize.x * 0.1f, backgroundSize.x + backgroundSize.x * 0.1f, backgroundSize.y, backgroundSize.y + backgroundSize.y * 0.1f)); // Bot
}

void Background::render()
{
	for (int i = firstTile; i < firstTile + numTilesVisible; ++i)
	{
		posDispl = glm::vec2(winSize.y * i, 0);
		textDispl = glm::vec2(tileTexSize.x * i, 0);

		glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(posDispl.x, posDispl.y, 0.f));
		program->setUniformMatrix4f("modelview", modelview);
		program->setUniform2f("texCoordDispl", textDispl.x, textDispl.y);

		glEnable(GL_TEXTURE_2D);
		texture.use();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6 * numHorizontalTiles);
		glDisable(GL_TEXTURE_2D);
	}
}

void Background::update(int deltaTime, glm::vec2 camPos)
{
	firstTile = floor((camPos.x - (winSize.x / 2.f)) / backgroundSize.y);
	if (firstTile < 0) firstTile = 0;
	if (firstTile >= numHorizontalTiles) firstTile = numHorizontalTiles - 1;

}

void Background::free()
{
	glDeleteBuffers(1, &vbo);
}

glm::vec2 Background::getSize()
{
	return glm::vec2(backgroundSize.y * numHorizontalTiles, backgroundSize.y);
}
