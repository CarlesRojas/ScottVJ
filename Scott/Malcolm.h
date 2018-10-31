#ifndef _MALCOLM_INCLUDE
#define _MALCOLM_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Malcolm : public Enemy
{
public:
	enum MalcolmAnims { DOWN, THREATING, WALK, IDLE, PUNCH, KICK, BLOCK};
	enum MalcolmState { INACTIVE, WAIT, MOVE, ATK1, ATK2, BLOCKING, THREAT, DEAD };
	
	Malcolm();
	~Malcolm();

	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	virtual bool kill();
	virtual vector<Attack*> getAttacks();

	MalcolmState state;

	Attack *punch;
	Attack *kick;
	float atkCooldown, atkCooldownTimer;
};

#endif _MALCOLM_INCLUDE