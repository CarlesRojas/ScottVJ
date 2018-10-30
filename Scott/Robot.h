#ifndef _ROBOT_INCLUDE
#define _ROBOT_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Robot : public Enemy
{
public:

	enum RobotAnims { IDLE, TOAST, FALLDOWN, WALK, PUNCH, SHIELD, DYING, NONE };
	enum LaserAnims { LASER, NOLASER };
	enum RobotState { INACTIVE, TOASTING, MOVE, WAIT, ATK1, ATK2, BLOCKING, FALLING, DEAD };


	Robot();
	~Robot();
	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();
	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	virtual void kill();
	virtual vector<Attack*> getAttacks();

	RobotState state;
	RobotState nextAction;

	Sprite *spriteLaser;

	Attack *laser;
	Attack *punch;
	float atkCooldownTimer;
	glm::vec2 maxAttackRangeLaser, minAttackRangeLaser;
	int hp;

};

#endif //_ROBOT_INCLUDE