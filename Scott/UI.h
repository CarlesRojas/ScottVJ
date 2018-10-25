#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "ShaderProgram.h"

class UI
{
public:
	enum UIAnims { WHITE, COOLDOWN };

	UI();
	~UI();

	static UI * createUI(int playerCharacter, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program);
	UI(int playerCharacter, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program);

	void render() const;
	void update(int deltaTime, glm::vec2 camPos);

	bool canAttack();
	bool canSpin();
	bool canSpecial();
	void changeHP(int hp);

private:
	// Static UI
	ShaderProgram *program;
	GLuint vao, vbo;
	GLint posLocation, texCoordLocation;
	float tileTexSize;
	glm::vec2 winSize, posDispl, textDispl;;
	vector<float> vertices;

	// Animatied UI
	Sprite *hpSprite, *attackSprite, *spinSprite, *specialSprite;

	// Cooldowns
	int player;
	float attackCooldown, spinCooldown, specialCooldown;
	float attackCooldownTimer, spinCooldownTimer, specialCooldownTimer;


};

#endif // _UI_INCLUDE

