#ifndef _SCOTT_INCLUDE
#define _SCOTT_INCLUDE

#include "Player.h"

class Scott : public Player
{
public:
	Scott() { }
	virtual void init(const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram *shaderProgram);
	virtual float getSpecialAttackDuration();
};

#endif // _SCOTT_INCLUDE