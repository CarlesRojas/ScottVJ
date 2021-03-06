#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include <vector>
#include <random>
#include "Sprite.h"
#include "Attack.h"

class Enemy
{

public:
	Enemy();
	~Enemy();
	static Enemy * createEnemy(const int enemy, const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * program);

	virtual void init(const glm::vec2 &initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();

	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	virtual bool kill();
	virtual vector<Attack*> getAttacks();

	Box *hitBox;
	Box *baseBox;

	Sprite *sprite;
	bool dead, isBoss, active, flip, fixAnim, fixPos, dying;
	glm::vec2 pos;

protected:
	glm::vec2 lastDeltaPos;

	int speed, alertRange, movingAlongX;
	glm::vec2 maxAttackRange, minAttackRange;
	float delay, scaleFactor;
	mt19937 random;
};


#endif // _ENEMY_INCLUDE


