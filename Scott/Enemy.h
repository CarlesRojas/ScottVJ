#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include <vector>
#include "Sprite.h"
#include "Attack.h"


class Enemy
{

public:
	enum EnemyAnims { DOWN, ATTACK, RUN, WALK, IDLE, SPECIAL };

	static Enemy * createEnemy(const int enemy, const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * program);
	Enemy(const int enemy, const glm::vec2 &initialPos, const int windowHeight, ShaderProgram * shaderProgram);

	void update(int deltaTime);
	void render();

	void enemyIA();
	void move(glm::vec2 deltaPos, float deltaTime);
	void revertMove();
	void kill();
	vector<Attack*> getAttacks();

	Box *hitBox;
	Box *baseBox;
	Attack *fire;

	bool dead, flip, fixAnim, fixPos, dying;
	glm::vec2 pos;

private:
	glm::vec2 lastDeltaPos;
	Texture spritesheet;
	Sprite *sprite;

	int enemyType, speed;
	float delay, delay2, scaleFactor;

	enum enemyState { IDLE, MOVE, ATTACK, MASK };
	enemyState state;
};


#endif // _ENEMY_INCLUDE


