#ifndef _ROXANNE_INCLUDE
#define _ROXANNE_INCLUDE

#include "Enemy.h"
#include "Attack.h"

class Roxanne : public Enemy
{
public:

	enum RoxanneAnims { IDLE, WALK, TIRED, FALLDOWN, ATK1, ATK2, ATK3, ATK4, ATK5, SWORD_ATK_START, SWORD_ATK_END, TP_DISAPPEAR, TP_APPEAR, DYING, NONE };
	enum SwordAnims { SWORD, NOSWORD };
	enum RoxanneState { INACTIVE, WAIT, MOVE, TP, COMBO, S_TIRED, FALLING, DEAD };


	Roxanne();
	~Roxanne();
	virtual void init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();
	virtual void enemyIA(int deltaTime);
	virtual void move(glm::vec2 deltaPos, float deltaTime);
	bool tp(glm::vec2 deltaPos);
	virtual bool kill();
	virtual vector<Attack*> getAttacks();

	RoxanneState state;
	RoxanneState nextAction;

	Sprite *spriteSword;

	Attack *atk1;
	Attack *atk2;
	Attack *atk3;
	Attack *atk4;
	Attack *atk5;
	Attack *sword;

	int hp, comboStage;
	bool tping;

};

#endif //_ROXANNE_INCLUDE