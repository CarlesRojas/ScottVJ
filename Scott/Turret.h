#ifndef _TURRET_INCLUDE
#define _TURRET_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Turret : public Enemy
{
public:
	enum TurretAnims { DOWN, SHOOT, DEPLOY, HIDE, IDLE, HIDDEN };
	enum TurretState { INACTIVE, WAIT, ATK, DEAD };

	Turret();
	~Turret();
	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void enemyIA(int deltaTime);
	virtual void kill();
	virtual vector<Attack*> getAttacks();

	TurretState state;

	Attack *shoot;
	float shootCooldownTimer, shootSpeed;
};

#endif _TURRET_INCLUDE