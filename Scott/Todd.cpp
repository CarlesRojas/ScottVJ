#include "Todd.h"
#include "Physics.h"
#include "Load.h"

Todd::Todd()
{
	atk1 = NULL;
	atk2 = NULL;
	atk3 = NULL;
}

Todd::~Todd()
{
	if (atk1 != NULL) delete atk1;
	if (atk2 != NULL) delete atk2;
	if (atk3 != NULL) delete atk3;
}

void Todd::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	delay = 0.f;
	fixAnim = fixPos = dying = dead = active = false;
	flip = true;
	isBoss = true;
	speed = (int)(45 * scaleFactor);
	hp = 4; 
	deadStage = 0;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.1f), &Load::instance().todd, shaderProgram);
	sprite->setNumberAnimations(11);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 0 * 0.1f));

	sprite->setAnimationSpeed(FINGER, 8);
	sprite->addKeyframe(FINGER, glm::vec2(4 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(FINGER, glm::vec2(5 * 0.05f, 0 * 0.1f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(FALLDOWN, 8);
	sprite->addKeyframe(FALLDOWN, glm::vec2(0 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(1 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(2 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(3 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(4 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(5 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(6 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(7 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(8 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(9 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(10 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(11 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(12 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(13 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(14 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(15 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(16 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(17 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(18 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(19 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(PUNCH, 8);
	sprite->addKeyframe(PUNCH, glm::vec2(0 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(1 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(2 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(3 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(4 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(5 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(6 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(7 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(8 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(9 * 0.05f, 2 * 0.1f));

	sprite->setAnimationSpeed(EXPLOSION_START, 8);
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(0 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(1 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(2 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(3 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(4 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(5 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(6 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(7 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(8 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(9 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(10 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(11 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_START, glm::vec2(12 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(EXPLOSION_END, 8);
	sprite->addKeyframe(EXPLOSION_END, glm::vec2(12 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_END, glm::vec2(11 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(EXPLOSION_END, glm::vec2(10 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(ARM_START, 8);
	sprite->addKeyframe(ARM_START, glm::vec2(0 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(1 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(2 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(3 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(4 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(5 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(6 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(7 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(8 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(9 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(10 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(11 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(12 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(13 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(14 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(15 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(16 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(17 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(18 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(ARM_START, glm::vec2(19 * 0.05f, 7 * 0.1f));

	sprite->setAnimationSpeed(ARM_END, 8);
	sprite->addKeyframe(ARM_END, glm::vec2(0 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(1 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(2 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(3 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(4 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(5 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(6 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(7 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(8 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(9 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(ARM_END, glm::vec2(10 * 0.05f, 8 * 0.1f));


	sprite->setAnimationSpeed(DYING_START, 8);
	sprite->addKeyframe(DYING_START, glm::vec2(0 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(1 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(2 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(3 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(4 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(5 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(6 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(7 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(8 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(9 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(10 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(11 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(12 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(13 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(14 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(15 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(16 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(17 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(18 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(19 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(0 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(1 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(2 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(3 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(4 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(5 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(6 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(7 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(8 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(9 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(10 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(11 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(12 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(13 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(14 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(15 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(16 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(17 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING_START, glm::vec2(18 * 0.05f, 6 * 0.1f));

	sprite->setAnimationSpeed(NONE, 8);
	sprite->addKeyframe(NONE, glm::vec2(9 * 0.05f, 19 * 0.1f));

	// Sprite Laser
	mutantSprite = Sprite::createSprite(true, glm::vec2(768.f * scaleFactor, 320.f * scaleFactor), glm::vec2(.2f, 1 / 6.f), &Load::instance().toddMutant, shaderProgram);
	mutantSprite->setNumberAnimations(4);

	mutantSprite->setAnimationSpeed(EXPLOSION, 8);
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(0 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(1 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(2 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(3 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(2 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(1 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(EXPLOSION, glm::vec2(0 * .2f, 0 / 6.f));

	mutantSprite->setAnimationSpeed(ARM, 8);
	mutantSprite->addKeyframe(ARM, glm::vec2(4 * .2f, 0 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(0 * .2f, 1 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(1 * .2f, 1 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(2 * .2f, 1 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(3 * .2f, 1 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(4 * .2f, 1 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(0 * .2f, 2 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(1 * .2f, 2 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(2 * .2f, 2 / 6.f));
	mutantSprite->addKeyframe(ARM, glm::vec2(3 * .2f, 2 / 6.f));

	mutantSprite->setAnimationSpeed(DYING, 8);
	mutantSprite->addKeyframe(DYING, glm::vec2(4 * .2f, 2 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(0 * .2f, 3 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(1 * .2f, 3 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(2 * .2f, 3 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(3 * .2f, 3 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(4 * .2f, 3 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(0 * .2f, 4 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(1 * .2f, 4 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(2 * .2f, 4 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(3 * .2f, 4 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(4 * .2f, 4 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(0 * .2f, 5 / 6.f));
	mutantSprite->addKeyframe(DYING, glm::vec2(1 * .2f, 5 / 6.f));

	mutantSprite->setAnimationSpeed(NONE_MUTANT, 8);
	mutantSprite->addKeyframe(NONE_MUTANT, glm::vec2(4 * .2f, 5 / 6.f));

	// Add Boxes
	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(38 * scaleFactor, 53 * scaleFactor));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(38 * scaleFactor, 10 * scaleFactor));
	atk1 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(12 * scaleFactor, -25 * scaleFactor), glm::vec2(92 * scaleFactor, 66 * scaleFactor), 9.5f / 8.f, 0, 4.5f / 8.f, false, false, glm::vec2(0, 0));
	atk2 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(0.f), glm::vec2(270 * scaleFactor, 120 * scaleFactor), 17.5f / 8.f, 0, 14.5f / 8.f, false, false, glm::vec2(0, 0));
	atk3 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(178 * scaleFactor, -44 * scaleFactor), glm::vec2(286 * scaleFactor, 42 * scaleFactor), 30.5f / 8.f, 0, 19.5f / 8.f, false, false, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);

	mutantSprite->changeAnimation(NONE_MUTANT);
	mutantSprite->setPosition(pos);

	state = INACTIVE;
	alertRange = (int)(windowHeight * 1.5f);

	minAttackRange = glm::vec2(30.f * scaleFactor, 70.f * scaleFactor);
	maxAttackRange = glm::vec2(55.f * scaleFactor, -15.f * scaleFactor);

	minAttackRangeExpl = glm::vec2(100.f * scaleFactor, 15.f * scaleFactor);
	maxAttackRangeExpl = glm::vec2(125.f * scaleFactor, -30.f * scaleFactor);

	minAttackRangeArm = glm::vec2(50.f * scaleFactor, 90.f * scaleFactor);
	maxAttackRangeArm = glm::vec2(310.f * scaleFactor, -15.f * scaleFactor);

	// Random
	random.seed(random_device()());
}


void Todd::update(int deltaTime)
{
	sprite->update(deltaTime);
	mutantSprite->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = false;
		if (dying) { dying = false; dead = true; }
	}

	enemyIA(deltaTime);
	sprite->setPosition(pos);
	mutantSprite->setPosition(pos);
}

void Todd::render()
{
	sprite->render(flip);
	mutantSprite->render(flip);
}


void Todd::enemyIA(int deltaTime)
{
	atk1->update(deltaTime);
	atk2->update(deltaTime);
	atk3->update(deltaTime);

	float dt = deltaTime / 1000.f;

	if (atkCooldownTimer > 0) atkCooldownTimer -= dt;
	glm::vec2 playerPos;

	switch (state)
	{
	case Todd::INACTIVE:
		if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
		if (Physics::instance().isCloseThan(this, alertRange))
		{
			state = GIVE_FINGER;
			active = true;
		}
		break;
	case Todd::GIVE_FINGER:
		if (delay <= 0)
		{
			if (sprite->animation() != FINGER) sprite->changeAnimation(FINGER);
			delay = 3.f;
			state = WAIT;
		}
		break;
	case Todd::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
			if (mutantSprite->animation() != NONE_MUTANT) mutantSprite->changeAnimation(NONE_MUTANT);
			if (atkCooldownTimer <= 0)
			{
				uniform_int_distribution<mt19937::result_type> random100(1, 100);
				int randomNum = random100(random);
				if (randomNum < 33) nextAction = Todd::ATK1;
				else if (randomNum < 66) nextAction = Todd::ATK2;
				else nextAction = Todd::ATK3;

				if (nextAction == Todd::ATK1)
				{
					if (!Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) { movingAlongX = true; state = MOVE; }
					else state = nextAction;
				}
				else if (nextAction == Todd::ATK2)
				{
					if (!Physics::instance().isInAttackRange(this, minAttackRangeExpl, maxAttackRangeExpl)) { movingAlongX = true; state = MOVE; }
					else { state = nextAction; explStage = 1; }
				}
				else if (nextAction == Todd::ATK3)
				{
					if (!Physics::instance().isInAttackRange(this, minAttackRangeArm, maxAttackRangeArm)) { movingAlongX = true; state = MOVE; }
					else { state = nextAction; armStage = 1; }
				}
			}
		}
		break;

	case Todd::MOVE:
		if (sprite->animation() != WALK) sprite->changeAnimation(WALK);

		if (nextAction == Todd::ATK1)
		{
			if (Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) state = WAIT;
			else
			{
				glm::vec2 diff = Physics::instance().distToPlayer(this);
				uniform_int_distribution<mt19937::result_type> random600(1, 600); // if (randNum < 10) means once per second
				int randomNum = random600(random);
				if (movingAlongX)
				{
					// Player too close -> Move Away
					if (diff.x > -minAttackRange.x && diff.x < minAttackRange.x)
					{
						if (diff.x < 0)
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
						else
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
					}
					else
					{
						if (abs(diff.x) >= minAttackRange.x && abs(diff.x) <= maxAttackRange.x) movingAlongX = false;
						else if (randomNum < 10) movingAlongX = false;
						else if (diff.x < 0)
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
						else
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
					}
				}
				else
				{
					if (diff.y <= minAttackRange.y && diff.y >= maxAttackRange.y) movingAlongX = true;
					else if (randomNum < 10) movingAlongX = true;
					if (diff.y > minAttackRange.y) move(glm::vec2(0.f, -1.f), dt);
					else move(glm::vec2(0.f, 1.f), dt);
				}
			}
		}
		else if(nextAction == Todd::ATK2)
		{

			if (Physics::instance().isInAttackRange(this, minAttackRangeExpl, maxAttackRangeExpl)) state = WAIT;
			else
			{
				glm::vec2 diff = Physics::instance().distToPlayer(this);
				uniform_int_distribution<mt19937::result_type> random600(1, 600); // if (randNum < 10) means once per second
				int randomNum = random600(random);
				if (movingAlongX)
				{
					// Player too close -> Move Away
					if (diff.x > -minAttackRangeExpl.x && diff.x < minAttackRangeExpl.x)
					{
						if (diff.x < 0)
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
						else
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
					}
					else
					{
						if (abs(diff.x) >= minAttackRangeExpl.x && abs(diff.x) <= maxAttackRangeExpl.x) movingAlongX = false;
						else if (randomNum < 10) movingAlongX = false;
						else if (diff.x < 0)
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
						else
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
					}
				}
				else
				{
					if (diff.y <= minAttackRangeExpl.y && diff.y >= maxAttackRangeExpl.y) movingAlongX = true;
					else if (randomNum < 10) movingAlongX = true;
					if (diff.y > minAttackRangeExpl.y) move(glm::vec2(0.f, -1.f), dt);
					else move(glm::vec2(0.f, 1.f), dt);
				}
			}
		}
		else
		{

			if (Physics::instance().isInAttackRange(this, minAttackRangeArm, maxAttackRangeArm)) state = WAIT;
			else
			{
				glm::vec2 diff = Physics::instance().distToPlayer(this);
				uniform_int_distribution<mt19937::result_type> random600(1, 600); // if (randNum < 10) means once per second
				int randomNum = random600(random);
				if (movingAlongX)
				{
					// Player too close -> Move Away
					if (diff.x > -minAttackRangeArm.x && diff.x < minAttackRangeArm.x)
					{
						if (diff.x < 0)
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
						else
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
					}
					else
					{
						if (abs(diff.x) >= minAttackRangeArm.x && abs(diff.x) <= maxAttackRangeArm.x) movingAlongX = false;
						else if (randomNum < 10) movingAlongX = false;
						else if (diff.x < 0)
						{
							if (flip) flip = false;
							move(glm::vec2(1.f, 0.f), dt);
						}
						else
						{
							if (!flip) flip = true;
							move(glm::vec2(-1.f, 0.f), dt);
						}
					}
				}
				else
				{
					if (diff.y <= minAttackRangeArm.y && diff.y >= maxAttackRangeArm.y) movingAlongX = true;
					else if (randomNum < 10) movingAlongX = true;
					if (diff.y > minAttackRangeArm.y) move(glm::vec2(0.f, -1.f), dt);
					else move(glm::vec2(0.f, 1.f), dt);
				}
			}
		}

		break;
	case Todd::ATK1:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != PUNCH) sprite->changeAnimation(PUNCH);
			atk1->activate(pos, flip);
			atkCooldownTimer = 2.f;
			delay = 9.5f / 8.f;
			state = WAIT;
		}
		break;
	case Todd::ATK2:
		if (delay <= 0)
		{
			if (explStage == 1)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != EXPLOSION_START) sprite->changeAnimation(EXPLOSION_START);

				atk2->activate(pos, flip);
				delay = 12.5f / 8.f;
				explStage++;
			}
			else if (explStage == 2)
			{
				if (sprite->animation() != NONE) sprite->changeAnimation(NONE);
				if (mutantSprite->animation() != EXPLOSION) mutantSprite->changeAnimation(EXPLOSION);

				delay = 6.5f / 8.f;
				explStage++;
			}
			else if (explStage == 3)
			{
				if (sprite->animation() != EXPLOSION_END) sprite->changeAnimation(EXPLOSION_END);
				if (mutantSprite->animation() != NONE_MUTANT) mutantSprite->changeAnimation(NONE_MUTANT);

				delay = 6.5f / 8.f;
				explStage++;
				atkCooldownTimer = 2.f;
				state = WAIT;
			}
		}
		break;
	case Todd::ATK3:
		if (delay <= 0)
		{
			if (armStage == 1)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ARM_START) sprite->changeAnimation(ARM_START);

				atk3->activate(pos, flip);
				delay = 19.5f / 8.f;
				armStage++;
			}
			else if (armStage == 2)
			{
				if (sprite->animation() != NONE) sprite->changeAnimation(NONE);
				if (mutantSprite->animation() != ARM) mutantSprite->changeAnimation(ARM);

				delay = 9.5f / 8.f;
				armStage++;
			}
			else if (armStage == 3)
			{
				if (sprite->animation() != ARM_END) sprite->changeAnimation(ARM_END);
				if (mutantSprite->animation() != NONE_MUTANT) mutantSprite->changeAnimation(NONE_MUTANT);

				delay = 10.5f / 8.f;
				armStage++;
				atkCooldownTimer = 2.f;
				state = WAIT;
			}
		}
		break;
	case Todd::FALLING:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != FALLDOWN) sprite->changeAnimation(FALLDOWN);
			delay = 19.5f / 8.f;
			state = WAIT;
		}
		break;

	case Todd::DEAD:
		if (delay <= 0)
		{
			if (deadStage == 1)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != DYING_START) sprite->changeAnimation(DYING_START);
				if (mutantSprite->animation() != NONE_MUTANT) mutantSprite->changeAnimation(NONE_MUTANT);

				delay = 38.5f / 8.f;
				deadStage++;
			}
			else if (deadStage == 2)
			{
				if (sprite->animation() != NONE) sprite->changeAnimation(NONE);
				if (mutantSprite->animation() != DYING) mutantSprite->changeAnimation(DYING);
				delay = 12.5f / 8.f;
				deadStage++;
				dying = true;
			}
		}
		break;
	default:
		break;
	}
}


void Todd::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	atk1->box->increasePos(lastDeltaPos);
	atk2->box->increasePos(lastDeltaPos);
	atk3->box->increasePos(lastDeltaPos);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		atk1->box->increasePos(-lastDeltaPos);
		atk2->box->increasePos(-lastDeltaPos);
		atk3->box->increasePos(-lastDeltaPos);
		movingAlongX = !movingAlongX;
	}
}

void Todd::kill()
{

	// Down
	if (sprite->animation() != FINGER &&
		sprite->animation() != FALLDOWN &&
		sprite->animation() != DYING_START &&
		sprite->animation() != PUNCH &&
		sprite->animation() != EXPLOSION_START &&
		sprite->animation() != EXPLOSION_END &&
		sprite->animation() != ARM_START &&
		mutantSprite->animation() != EXPLOSION &&
		mutantSprite->animation() != ARM &&
		mutantSprite->animation() != DYING &&
		!dying)
	{
		if (hp > 1)
		{
			--hp;
			delay = 0;
			state = FALLING;
		}
		else
		{
			state = DEAD;
			deadStage = 1;
			hitBox->active = false;
			baseBox->active = false;
			atk1->box->active = false;
			atk2->box->active = false;
			atk3->box->active = false;
			fixAnim = true;
		}
	}
}

vector<Attack*> Todd::getAttacks()
{
	vector<Attack*> a;
	a.push_back(atk1);
	a.push_back(atk2);
	a.push_back(atk3);
	return a;
}


