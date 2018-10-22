#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"


Sprite *Sprite::createSprite(bool displace, const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(displace, quadSize, sizeInSpritesheet, spritesheet, program);
	return quad;
}


Sprite::Sprite(bool displace, const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	flipped = false;

	glm::vec2 displacement = glm::vec2(0.f, 0.f);
	if (displace) displacement = glm::vec2(quadSize.x / 2.f, quadSize.y);
	bool flip = false;

	vertices = {
		0.f - displacement.x, 0.f - displacement.y,
		0.f, 0.f,
		quadSize.x - displacement.x, 0.f - displacement.y,
		sizeInSpritesheet.x, 0.f,
		quadSize.x - displacement.x, quadSize.y - displacement.y,
		sizeInSpritesheet.x, sizeInSpritesheet.y,
		0.f - displacement.x, 0.f - displacement.y,
		0.f, 0.f,
		quadSize.x - displacement.x, quadSize.y - displacement.y,
		sizeInSpritesheet.x, sizeInSpritesheet.y,
		0.f - displacement.x, quadSize.y - displacement.y,
		0.f, sizeInSpritesheet.y };

	flippedVertices = {
		0.f - displacement.x, 0.f - displacement.y,
		sizeInSpritesheet.x, 0.f,
		quadSize.x - displacement.x, 0.f - displacement.y,
		0.f, 0.f,
		quadSize.x - displacement.x, quadSize.y - displacement.y,
		0.f, sizeInSpritesheet.y,
		0.f - displacement.x, 0.f - displacement.y,
		sizeInSpritesheet.x, 0.f,
		quadSize.x - displacement.x, quadSize.y - displacement.y,
		0.f, sizeInSpritesheet.y,
		0.f - displacement.x, quadSize.y - displacement.y,
		sizeInSpritesheet.x, sizeInSpritesheet.y };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	position = glm::vec2(0.f);
}

void Sprite::update(int deltaTime)
{
	if (currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render(bool flip)
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);

	if (flipped && !flip) {
		flipped = false;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 24 * sizeof(float), &vertices[0]);
	}

	if (!flipped && flip) {
		flipped = true;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 24 * sizeof(float), &flippedVertices[0]);
	}

	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, float keyframesPerSec)
{
	if (animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if (animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if (animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

void Sprite::setPosition(const glm::vec2 &pos)
{
	position = pos;
}

glm::vec2 Sprite::getPosition()
{
	return position;
}



