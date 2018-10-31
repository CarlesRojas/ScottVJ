#ifndef _TODD_INCLUDE
#define _TODD_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Todd : public Enemy
{
public:

	enum ToddAnims { IDLE, FINGER, WALK, FALLDOWN, PUNCH, EXPLOSION_START, EXPLOSION_END, ARM_START, ARM_END, DYING_START, NONE };
	enum MutantAnims { EXPLOSION, ARM, DYING, NONE_MUTANT };
	enum ToddState { INACTIVE, GIVE_FINGER, WAIT, MOVE, ATK1, ATK2, ATK3, FALLING, DEAD };


	Todd();
	~Todd();
	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();
	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	virtual bool kill();
	virtual vector<Attack*> getAttacks();

	ToddState state;
	ToddState nextAction;

	Sprite *mutantSprite;

	Attack *atk1;
	Attack *atk2;
	Attack *atk3;

	float atkCooldownTimer;

	glm::vec2 maxAttackRangeExpl, minAttackRangeExpl;
	glm::vec2 maxAttackRangeArm, minAttackRangeArm;

	int hp, explStage, armStage, deadStage;
};

#endif //_TODD_INCLUDE