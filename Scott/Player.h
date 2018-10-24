#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include <vector>
#include "Sprite.h"
#include "UI.h"
#include "Attack.h"

class Player
{

public:
	enum PlayerAnims { DOWN, REVIVE, SPIN, SPECIAL, PUNCH3, PUNCH2, PUNCH1, RUN, WALK, IDLE };

	static Player *createPlayer(const int player, const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram *program);
	Player() { }

	virtual void init(const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram *shaderProgram);
	void update(int deltaTime);
	void render();

	void move(glm::vec2 deltaPos, float deltaTime);
	void kill();
	vector<Attack*> getAttacks();

	Box *hitBox;
	Box *baseBox;
	Attack *punch;
	Attack *spin;
	Attack *special;

	Sprite *sprite;
	glm::vec2 pos;
	bool flip, fixAnim, fixPos, dying, reviving;

protected:
	virtual float getSpecialAttackDuration();
	glm::vec2 lastDeltaPos;
	Texture spriteSheet;
	UI *ui;

	int speed, runSpeed, hp;
	float delay, scaleFactor;
};

#endif // _PLAYER_INCLUDE


