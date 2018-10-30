#include "Attack.h"
#include "Physics.h"


Attack::Attack()
{
	box = NULL;
	sprite = NULL;
}

Attack::~Attack()
{
	if (box != NULL) delete box;
	if (sprite != NULL) delete sprite;
}

Attack * Attack::createAttack(Box::BoxOwner owner, glm::vec2 playerOrigin, glm::vec2 displacement, glm::vec2 size, float duration, float startDelay, float impactDelay, bool oneKillOnly, bool multiHits, glm::vec2 deltaPos)
{
	Attack *a = new Attack(owner, playerOrigin, displacement, size, duration, startDelay, impactDelay, oneKillOnly, multiHits, deltaPos);
	return a;
}

Attack::Attack(Box::BoxOwner owner, glm::vec2 playerOrigin, glm::vec2 displacement, glm::vec2 size, float duration, float startDelay, float impactDelay, bool oneKillOnly, bool multiHits, glm::vec2 deltaPos)
{
	this->sprite = NULL;
	this->box = Box::createBox(owner, Box::ATTACK, playerOrigin + displacement, size);
	this->box->active = false;
	this->active = false;
	this->duration = duration;
	this->impactDelay = impactDelay;
	this->startDelay = startDelay;
	this->durationTimer = -1.f;
	this->impactDelayTimer = -1.f;
	this->startDelayTimer = -1.f;
	this->oneKillOnly = oneKillOnly;
	this->multiHits = multiHits;
	this->flipped = false;
	this->playerHit = false;
	this->deltaPos = deltaPos;
	this->originBoxDispl = displacement;
}

void Attack::update(int deltaTime)
{
	float dt = deltaTime / 1000.f;

	if (startDelayTimer > 0) startDelayTimer -= dt;
	else if (active)
	{
		if (durationTimer > 0)
		{
			increasePos(deltaPos * dt, flipped);
			if (sprite != NULL) sprite->update(deltaTime);

			durationTimer -= dt;
			if (impactDelayTimer > 0) impactDelayTimer -= dt;
			else
			{
				this->box->active = true;
				Physics::instance().attack(this);
			}
		}
		else deactivate();
	}

}

void Attack::render()
{
	if (sprite != NULL && active && startDelayTimer <= 0)
		sprite->render(flipped);
}

void Attack::activate(const glm::vec2 entityOrigin, bool flip)
{
	this->active = true;
	moveTo(entityOrigin);
	durationTimer = duration;
	impactDelayTimer = impactDelay;
	startDelayTimer = startDelay;

	this->flipped = flip;
	if (flipped) flipXAxis(entityOrigin);
}

void Attack::deactivate()
{
	this->box->active = false;
	this->active = false;
	durationTimer = -1.f;
	impactDelayTimer = -1.f;
	startDelayTimer = -1.f;
}

void Attack::flipXAxis(glm::vec2 point)
{
	box->increasePos(glm::vec2(2.f * point.x - box->left - box->right, 0.f));
	if (sprite != NULL) sprite->setPosition(glm::vec2(sprite->getPosition().x + 2.f * (point.x - sprite->getPosition().x), sprite->getPosition().y));
}

bool Attack::entityHit()
{
	if (multiHits)
	{
		impactDelayTimer = impactDelay;
		this->box->active = false;
	}
	else deactivate();
	return oneKillOnly;
}

void Attack::increasePos(glm::vec2 deltaPos, bool flip)
{
	if (flip)
	{
		if (sprite != NULL) sprite->setPosition(sprite->getPosition() - deltaPos);
		box->increasePos(-deltaPos);
	}
	else
	{
		if (sprite != NULL) sprite->setPosition(sprite->getPosition() + deltaPos);
		box->increasePos(deltaPos);
	}
}

void Attack::moveTo(glm::vec2 entityOrigin)
{
	if (sprite != NULL) sprite->setPosition(entityOrigin + originSpriteDispl);
	box->moveTo(entityOrigin + originBoxDispl);
}

void Attack::setSprite(Sprite * sprite, glm::vec2 spriteDispl)
{
	this->sprite = sprite;
	this->originSpriteDispl = spriteDispl;
}
