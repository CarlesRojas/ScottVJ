#ifndef _ATTACK_INCLUDE
#define _ATTACK_INCLUDE

#include "Box.h"
#include "Sprite.h"

class Attack
{
public:
	static Attack * createAttack(Box::BoxOwner owner, glm::vec2 playerOrigin, glm::vec2 displacement, glm::vec2 size, float duration, float startDelay, float impactDelay, bool oneKillOnly, bool multiHits, glm::vec2 deltaPos);
	Attack(Box::BoxOwner owner, glm::vec2 playerOrigin, glm::vec2 displacement, glm::vec2 size, float duration, float startDelay, float impactDelay, bool oneKillOnly, bool multiHits, glm::vec2 deltaPos);

	void update(int deltaTime);
	void render();

	void activate(glm::vec2 entityOrigin, bool flip);
	void deactivate();
	void flipXAxis(glm::vec2 point);
	bool entityHit();
	void increasePos(glm::vec2 deltaPos, bool flip);
	void moveTo(glm::vec2 entityOrigin);
	void setSprite(Sprite * sprite, glm::vec2 spriteDispl);

	Box *box;

private:
	Sprite *sprite;


	float duration, durationTimer, impactDelay, impactDelayTimer, startDelay, startDelayTimer;
	bool multiHits, oneKillOnly, active, flipped;
	glm::vec2 deltaPos, originBoxDispl, originSpriteDispl;
};

#endif // _ATTACK_INCLUDE