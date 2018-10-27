#ifndef _KIM_INCLUDE
#define _KIM_INCLUDE

#include "Player.h"

class Kim : public Player
{
public:
	Kim() { }
	virtual void init(const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram *shaderProgram);
	virtual float getSpecialAttackDuration();

private:
	float monsterSpeed;
};

#endif // _KIM_INCLUDE
