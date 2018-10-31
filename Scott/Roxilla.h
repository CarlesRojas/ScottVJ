#ifndef _ROXILLA_INCLUDE
#define _ROXILLA_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Roxilla: public Enemy
{
public:
	enum RoxillaAnims { DOWN, FIRE, WALK, IDLE, MASKOFF };
	enum RoxillaState { INACTIVE, WAIT, MOVE, ATK, MASK, DEAD };

	Roxilla();
	~Roxilla();
	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	virtual bool kill();
	virtual vector<Attack*> getAttacks();

	RoxillaState state;
	
	Attack *fire;
	float fireCooldown, fireCooldownTimer;
};

#endif _ROXILLA_INCLUDE
