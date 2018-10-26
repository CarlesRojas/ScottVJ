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
	enum PlayerAnims { SCOTT_SHOW, SCOTT_HIDE, SCOTT, KIM_SHOW, KIM_HIDE, KIM, RAMONA_SHOW, RAMONA_HIDE, RAMONA, P_NONE };
	enum BossAnims { ROXANNE_SHOW, ROXANNE_HIDE, ROXANNE, ROBOT_SHOW, ROBOT_HIDE, ROBOT, TODD_SHOW, TODD_HIDE, TODD, B_NONE };
	enum BGAnims { SHOW, HIDE, LOOP, BG_NONE };

	UI();
	~UI();

	static UI * createUI(int playerCharacter, int boss, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program);
	UI(int playerCharacter, int boss, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program);

	void render() const;
	void update(int deltaTime, glm::vec2 camPos);

	bool canAttack();
	bool canSpin();
	bool canSpecial();
	void changeHP(int hp);
	void showBossIntro();

private:
	// Static UI
	ShaderProgram *program;
	GLuint vao, vbo;
	GLint posLocation, texCoordLocation;
	float tileTexSize;
	glm::vec2 winSize, posDispl, textDispl, bossDispl;
	vector<float> vertices;

	// Animatied UI
	Sprite *hpSprite, *attackSprite, *spinSprite, *specialSprite, *bossSprite, *playerSprite, *bgSprite;

	// Cooldowns
	int player, boss;
	float attackCooldown, spinCooldown, specialCooldown;
	float attackCooldownTimer, spinCooldownTimer, specialCooldownTimer;

	// Boss intro
	bool showingBossIntro;
	float introDelay;
	int introStage;
};

#endif // _UI_INCLUDE

