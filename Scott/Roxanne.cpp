#include "Roxanne.h"
#include "Physics.h"
#include "Load.h"

Roxanne::Roxanne()
{
	atk1 = NULL;
	atk2 = NULL;
	atk3 = NULL;
	atk4 = NULL;
	atk5 = NULL;
	sword = NULL;
}

Roxanne::~Roxanne()
{
	if (atk1 != NULL) delete atk1;
	if (atk2 != NULL) delete atk2;
	if (atk3 != NULL) delete atk3;
	if (atk4 != NULL) delete atk4;
	if (atk5 != NULL) delete atk5;
	if (sword != NULL) delete sword;
}

void Roxanne::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	delay = 0.f;
	fixAnim = fixPos = dying = dead = active = tping = false;
	flip = true;
	isBoss = true;
	speed = (int)(45 * scaleFactor);
	hp = 1;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.1f), &Load::instance().roxanne, shaderProgram);
	sprite->setNumberAnimations(15);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(4 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(5 * 0.05f, 0 * 0.1f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(TIRED, 8);
	sprite->addKeyframe(TIRED, glm::vec2(0 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(TIRED, glm::vec2(1 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(TIRED, glm::vec2(2 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(TIRED, glm::vec2(3 * 0.05f, 2 * 0.1f));

	sprite->setAnimationSpeed(FALLDOWN, 8);
	sprite->addKeyframe(FALLDOWN, glm::vec2(0 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(1 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(2 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(3 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(4 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(5 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(6 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(7 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(8 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(9 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(10 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(11 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(12 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(13 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(14 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(15 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(16 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(ATK1, 8);
	sprite->addKeyframe(ATK1, glm::vec2(0 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK1, glm::vec2(1 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK1, glm::vec2(2 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK1, glm::vec2(3 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK1, glm::vec2(4 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(ATK2, 8);
	sprite->addKeyframe(ATK2, glm::vec2(5 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK2, glm::vec2(6 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK2, glm::vec2(7 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK2, glm::vec2(8 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK2, glm::vec2(9 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(ATK3, 8);
	sprite->addKeyframe(ATK3, glm::vec2(10 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK3, glm::vec2(11 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK3, glm::vec2(12 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK3, glm::vec2(13 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK3, glm::vec2(14 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(ATK4, 8);
	sprite->addKeyframe(ATK4, glm::vec2(15 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK4, glm::vec2(16 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK4, glm::vec2(17 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK4, glm::vec2(18 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(ATK4, glm::vec2(19 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(ATK5, 8);
	sprite->addKeyframe(ATK5, glm::vec2(0 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(ATK5, glm::vec2(1 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(ATK5, glm::vec2(2 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(ATK5, glm::vec2(3 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(ATK5, glm::vec2(4 * 0.05f, 5 * 0.1f));

	sprite->setAnimationSpeed(SWORD_ATK_START, 8);
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(5 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(6 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(7 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(8 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(9 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(10 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(11 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(12 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_START, glm::vec2(13 * 0.05f, 5 * 0.1f));

	sprite->setAnimationSpeed(SWORD_ATK_END, 8);
	sprite->addKeyframe(SWORD_ATK_END, glm::vec2(14 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(SWORD_ATK_END, glm::vec2(15 * 0.05f, 5 * 0.1f));

	sprite->setAnimationSpeed(TP_DISAPPEAR, 8);
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(0 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(1 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(2 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(3 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(4 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(5 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(6 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(7 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(8 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(9 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(10 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(11 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(12 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(13 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(14 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(15 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(16 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_DISAPPEAR, glm::vec2(17 * 0.05f, 6 * 0.1f));

	sprite->setAnimationSpeed(TP_APPEAR, 8);
	sprite->addKeyframe(TP_APPEAR, glm::vec2(18 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_APPEAR, glm::vec2(19 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(TP_APPEAR, glm::vec2(0 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TP_APPEAR, glm::vec2(1 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TP_APPEAR, glm::vec2(2 * 0.05f, 7 * 0.1f));

	sprite->setAnimationSpeed(DYING, 8);
	sprite->addKeyframe(DYING, glm::vec2(0 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(1 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(2 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(3 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(4 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(5 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(6 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(7 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(8 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(9 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(10 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(11 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(12 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(13 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(14 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(15 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(16 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(17 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(18 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(19 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(0 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(1 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(2 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(3 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(4 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(5 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(6 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(7 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(8 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(9 * 0.05f, 9 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(10 * 0.05f, 9 * 0.1f));

	sprite->setAnimationSpeed(NONE, 8);
	sprite->addKeyframe(NONE, glm::vec2(9 * 0.05f, 9 * 0.1f));

	// Sprite Laser
	spriteSword = Sprite::createSprite(true, glm::vec2(512.f * scaleFactor, 128.f * scaleFactor), glm::vec2(1, .25f), &Load::instance().roxanneWhip, shaderProgram);
	spriteSword->setNumberAnimations(2);

	spriteSword->setAnimationSpeed(SWORD, 8);
	spriteSword->addKeyframe(SWORD, glm::vec2(0, 0 * .25f));
	spriteSword->addKeyframe(SWORD, glm::vec2(0, 1 * .25f));
	spriteSword->addKeyframe(SWORD, glm::vec2(0, 2 * .25f));

	spriteSword->setAnimationSpeed(NOSWORD, 8);
	spriteSword->addKeyframe(NOSWORD, glm::vec2(0, 3 * .25f));

	// Add Boxes
	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(38 * scaleFactor, 53 * scaleFactor));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(38 * scaleFactor, 10 * scaleFactor));
	atk1 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(28 * scaleFactor, 0 * scaleFactor), glm::vec2(54 * scaleFactor, 78 * scaleFactor), 4.5f / 8.f, 0, 1.5f / 8.f, false, false, glm::vec2(0, 0));
	atk2 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(12 * scaleFactor, -19 * scaleFactor), glm::vec2(129 * scaleFactor, 25 * scaleFactor), 4.5f / 8.f, 0, 0.5f / 8.f, false, false, glm::vec2(0, 0));
	atk3 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(30 * scaleFactor, -4 * scaleFactor), glm::vec2(60 * scaleFactor, 83 * scaleFactor), 4.5f / 8.f, 0, 0.5f / 8.f, false, false, glm::vec2(0, 0));
	atk4 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(46 * scaleFactor, -21 * scaleFactor), glm::vec2(115 * scaleFactor, 24 * scaleFactor), 4.5f / 8.f, 0, 0.5f / 8.f, false, false, glm::vec2(0, 0));
	atk5 = Attack::createAttack(Box::ENEMY, pos, glm::vec2(22 * scaleFactor, -11 * scaleFactor), glm::vec2(136 * scaleFactor, 54 * scaleFactor), 4.5f / 8.f, 0, 1.5f / 8.f, false, false, glm::vec2(0, 0));
	sword = Attack::createAttack(Box::ENEMY, pos, glm::vec2(127 * scaleFactor, 0 * scaleFactor), glm::vec2(253 * scaleFactor, 40 * scaleFactor), 13.5f / 8.f, 0, 9.5f / 8.f, false, false, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);

	spriteSword->changeAnimation(NOSWORD);
	spriteSword->setPosition(pos);

	state = INACTIVE;
	alertRange = (int)windowHeight;
	minAttackRange = glm::vec2(10.f * scaleFactor, 65.f * scaleFactor);
	maxAttackRange = glm::vec2(50.f * scaleFactor, -30.f * scaleFactor);

	// Random
	random.seed(random_device()());
}

void Roxanne::update(int deltaTime)
{
	sprite->update(deltaTime);
	spriteSword->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = false;
		if (dying) { dying = false; dead = true; }
	}

	enemyIA(deltaTime);
	sprite->setPosition(pos);
	spriteSword->setPosition(pos);
}

void Roxanne::render()
{
	sprite->render(flip);
	spriteSword->render(flip);
}

void Roxanne::enemyIA(int deltaTime)
{
	atk1->update(deltaTime);
	atk2->update(deltaTime);
	atk3->update(deltaTime);
	atk4->update(deltaTime);
	atk5->update(deltaTime);
	sword->update(deltaTime);

	float dt = deltaTime / 1000.f;
	glm::vec2 playerPos;

	switch (state)
	{
	case Roxanne::INACTIVE:
		if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
		if (Physics::instance().isCloseThan(this, alertRange))
		{
			state = WAIT;
			active = true;
			delay = 2.f;
		}
		break;
	case Roxanne::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);

			if (!Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) 
			{ 
				if (randomNum < 0) { movingAlongX = true; state = MOVE; }
				else state = TP;
			}
			else { state = COMBO; comboStage = 1; }
			
		}
		break;

	case Roxanne::MOVE:
		if (sprite->animation() != WALK) sprite->changeAnimation(WALK);

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
		break;

	case Roxanne::TP:
		if (delay <= 0)
		{
			if (!tping) 
			{
				if (sprite->animation() != TP_DISAPPEAR) sprite->changeAnimation(TP_DISAPPEAR);
				delay = 17.5f / 8.f;
				tping = true;
			}
			else
			{
				//Move
				playerPos = Physics::instance().getPlayerPos();
				glm::vec2 newPos = playerPos;
				if (playerPos.x <= pos.x) newPos.x -= 45.f * scaleFactor;
				if (playerPos.x > pos.x) newPos.x += 45.f * scaleFactor;
				if (!tp(newPos - pos)) 
				{
					if (playerPos.x <= pos.x) newPos.x += 90.f * scaleFactor;
					if (playerPos.x > pos.x) newPos.x -= 90.f * scaleFactor;
					tp(newPos - pos);
				}
				if (sprite->animation() != TP_APPEAR) sprite->changeAnimation(TP_APPEAR);
				delay = 4.5f / 8.f; 
				tping = false;
				state = COMBO;
				comboStage = 1;
			}
		}
		break;

	case Roxanne::COMBO:
		if (delay <= 0)
		{
			if (comboStage == 1) 
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ATK1) sprite->changeAnimation(ATK1);
				atk1->activate(pos, flip);
				delay = 4.5f / 8.f;
				comboStage++;
			}
			else if (comboStage == 2)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ATK2) sprite->changeAnimation(ATK2);
				if (!atk1->playerHit) atk2->activate(pos, flip);
				delay = 4.5f / 8.f;
				comboStage++;
			}
			else if (comboStage == 3)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ATK3) sprite->changeAnimation(ATK3);
				if (!atk1->playerHit && !atk2->playerHit) atk3->activate(pos, flip);
				delay = 4.5f / 8.f;
				comboStage++;
			}
			else if (comboStage == 4)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ATK4) sprite->changeAnimation(ATK4);
				if (!atk1->playerHit && !atk2->playerHit && !atk3->playerHit) atk4->activate(pos, flip);
				delay = 4.5f / 8.f;
				comboStage++;
			}
			else if (comboStage == 5)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != ATK5) sprite->changeAnimation(ATK5);
				if (!atk1->playerHit && !atk2->playerHit && !atk3->playerHit && !atk4->playerHit) atk5->activate(pos, flip);
				delay = 4.5f / 8.f;
				comboStage++;
			}
			else  if (comboStage == 6)
			{
				playerPos = Physics::instance().getPlayerPos();
				if (playerPos.x <= pos.x && !flip) flip = true;
				if (playerPos.x > pos.x && flip) flip = false;

				if (sprite->animation() != SWORD_ATK_START) sprite->changeAnimation(SWORD_ATK_START);
				if (!atk1->playerHit && !atk2->playerHit && !atk3->playerHit && !atk4->playerHit && !atk5->playerHit) sword->activate(pos, flip);
				delay = 8.5f / 8.f;
				comboStage++;
			}
			else  if (comboStage == 7)
			{
				if (sprite->animation() != NONE) sprite->changeAnimation(NONE);
				if (spriteSword->animation() != SWORD) spriteSword->changeAnimation(SWORD);
				delay = 2.5f / 8.f;
				comboStage++;
			}
			else  if (comboStage == 8)
			{
				if (sprite->animation() != SWORD_ATK_END) sprite->changeAnimation(SWORD_ATK_END);
				if (spriteSword->animation() != NOSWORD) spriteSword->changeAnimation(NOSWORD);
				delay = 1.5f / 8.f;
				comboStage = 0;
				state = S_TIRED;

				atk1->playerHit = false;
				atk2->playerHit = false;
				atk3->playerHit = false;
				atk4->playerHit = false;
				atk5->playerHit = false;
				sword->playerHit = false;
			}
		}
		break;

	case Roxanne::S_TIRED:
		if (delay <= 0)
		{
			if (sprite->animation() != TIRED) sprite->changeAnimation(TIRED);
			delay = 2.f;
			state = WAIT;
		}
		break;

	case Roxanne::FALLING:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != FALLDOWN) sprite->changeAnimation(FALLDOWN);
			delay = 16.5f / 8.f;
			state = WAIT;
		}
		break;
	default:
		break;
	}
}


void Roxanne::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	atk1->box->increasePos(lastDeltaPos);
	atk2->box->increasePos(lastDeltaPos);
	atk3->box->increasePos(lastDeltaPos);
	atk4->box->increasePos(lastDeltaPos);
	atk5->box->increasePos(lastDeltaPos);
	sword->box->increasePos(lastDeltaPos);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		atk1->box->increasePos(-lastDeltaPos);
		atk2->box->increasePos(-lastDeltaPos);
		atk3->box->increasePos(-lastDeltaPos);
		atk4->box->increasePos(-lastDeltaPos);
		atk5->box->increasePos(-lastDeltaPos);
		sword->box->increasePos(-lastDeltaPos);
		movingAlongX = !movingAlongX;
	}
}

bool Roxanne::tp(glm::vec2 deltaPos)
{
	pos += deltaPos;
	hitBox->increasePos(deltaPos);
	baseBox->increasePos(deltaPos);
	atk1->box->increasePos(deltaPos);
	atk2->box->increasePos(deltaPos);
	atk3->box->increasePos(deltaPos);
	atk4->box->increasePos(deltaPos);
	atk5->box->increasePos(deltaPos);
	sword->box->increasePos(deltaPos);

	if (!Physics::instance().correctPosition(baseBox)) 
	{
		pos -= deltaPos;
		hitBox->increasePos(-deltaPos);
		baseBox->increasePos(-deltaPos);
		atk1->box->increasePos(-deltaPos);
		atk2->box->increasePos(-deltaPos);
		atk3->box->increasePos(-deltaPos);
		atk4->box->increasePos(-deltaPos);
		atk5->box->increasePos(-deltaPos);
		sword->box->increasePos(-deltaPos);
		return false;
	}
	return true;
}

void Roxanne::kill()
{

	// Down
	if (sprite->animation() != ATK1 &&
		sprite->animation() != ATK2 &&
		sprite->animation() != ATK3 &&
		sprite->animation() != ATK4 &&
		sprite->animation() != ATK5 &&
		sprite->animation() != SWORD_ATK_START &&
		sprite->animation() != SWORD_ATK_END &&
		sprite->animation() != FALLDOWN &&
		sprite->animation() != TP_APPEAR &&
		sprite->animation() != TP_DISAPPEAR &&
		sprite->animation() != DYING &&
		spriteSword->animation() != SWORD &&
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
			hitBox->active = false;
			baseBox->active = false;
			atk1->box->active = false;
			atk2->box->active = false;
			atk3->box->active = false;
			atk4->box->active = false;
			atk5->box->active = false;
			sword->box->active = false;
			fixAnim = true;
			dying = true;
			delay = 30.5f / 8.f;
			if (sprite->animation() != DYING) sprite->changeAnimation(DYING);
		}
	}
}

vector<Attack*> Roxanne::getAttacks()
{
	vector<Attack*> a;
	a.push_back(atk1);
	a.push_back(atk2);
	a.push_back(atk3);
	a.push_back(atk4);
	a.push_back(atk5);
	a.push_back(sword);
	return a;
}
