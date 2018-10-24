#ifndef _RAMONA_INCLUDE
#define _RAMONA_INCLUDE

#include "Player.h"

class Ramona : public Player
{
public:
	Ramona() { }
	virtual void init(const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram *shaderProgram);
	virtual float getSpecialAttackDuration();
};

#endif // _RAMONA_INCLUDE
