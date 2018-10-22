#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 

class Sprite
{
public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(bool displace, const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	Sprite(bool displace, const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	void update(int deltaTime);
	void render(bool flip);
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, float keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;

	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();

private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;

	vector<float> vertices;
	vector<float> flippedVertices;
	bool flipped;
};


#endif // _SPRITE_INCLUDE

