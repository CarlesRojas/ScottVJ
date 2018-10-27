#include "Malcolm.h"
#include "Physics.h"
#include "Load.h"

Malcolm::Malcolm() 
{
	punch = NULL;
	kick = NULL;
}

Malcolm::~Malcolm() 
{
	if (punch != NULL) delete punch;
	if (kick != NULL) delete kick;
}

void Malcolm::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	delay = 0.f;
	flip = fixAnim = fixPos = dying = dead = false;
	speed = 50 * scaleFactor;
	atkCooldown = 3.f;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &Load::instance().malcolm, shaderProgram);
	sprite->setNumberAnimations(7);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 4 * 0.05f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 4 * 0.05f));
	sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 4 * 0.05f));
	sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 4 * 0.05f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(6 * 0.05f, 1 * 0.05f));
	sprite->addKeyframe(WALK, glm::vec2(7 * 0.05f, 1 * 0.05f));

	sprite->setAnimationSpeed(THREATING, 8);
	sprite->addKeyframe(THREATING, glm::vec2(0 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(1 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(2 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(3 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(4 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(5 * 0.05f, 2 * 0.05f));
	sprite->addKeyframe(THREATING, glm::vec2(6 * 0.05f, 2 * 0.05f));

	sprite->setAnimationSpeed(PUNCH, 8);
	sprite->addKeyframe(PUNCH, glm::vec2(0 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(PUNCH, glm::vec2(1 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(PUNCH, glm::vec2(2 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(PUNCH, glm::vec2(3 * 0.05f, 3 * 0.05f));

	sprite->setAnimationSpeed(KICK, 8);
	sprite->addKeyframe(KICK, glm::vec2(4 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(KICK, glm::vec2(5 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(KICK, glm::vec2(6 * 0.05f, 3 * 0.05f));
	sprite->addKeyframe(KICK, glm::vec2(7 * 0.05f, 3 * 0.05f));

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(1 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(2 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(3 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(4 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(5 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(6 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(7 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(8 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(9 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(10 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(11 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(12 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(13 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(14 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(15 * 0.05f, 0 * 0.05f));
	sprite->addKeyframe(DOWN, glm::vec2(16 * 0.05f, 0 * 0.05f));

	sprite->setAnimationSpeed(BLOCK, 8);
	sprite->addKeyframe(BLOCK, glm::vec2(0 * 0.05f, 5 * 0.05f));
	sprite->addKeyframe(BLOCK, glm::vec2(1 * 0.05f, 5 * 0.05f));

	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(35 * ((float)windowHeight / 256.f), 70 * ((float)windowHeight / 256.f)));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(35 * ((float)windowHeight / 256.f), 10 * ((float)windowHeight / 256.f)));
	punch = Attack::createAttack(Box::ENEMY, pos, glm::vec2(42 * scaleFactor, -35 * scaleFactor), glm::vec2(44 * scaleFactor, 13 * scaleFactor), 3.5f / 8.f, 0, 1.f / 8.f, true, false, glm::vec2(0, 0));
	kick = Attack::createAttack(Box::ENEMY, pos, glm::vec2(53 * scaleFactor, -33 * scaleFactor), glm::vec2(44 * scaleFactor, 13 * scaleFactor), 3.5f / 8.f, 0, 1.f / 8.f, true, false, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
	state = INACTIVE;
	alertRange = windowHeight;
	minAttackRange = glm::vec2(20.f * scaleFactor, 20.f * scaleFactor);
	maxAttackRange = glm::vec2(64.f * scaleFactor, -10.f * scaleFactor);

	// Random
	random.seed(random_device()());
}

void Malcolm::enemyIA(int deltaTime)
{
	punch->update(deltaTime);
	kick->update(deltaTime);

	float dt = deltaTime / 1000.f;

	if (atkCooldownTimer > 0) atkCooldownTimer -= dt;
	glm::vec2 playerPos;

	switch (state)
	{
	case Malcolm::INACTIVE:
		if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
		if (Physics::instance().isCloseThan(this, alertRange)) state = WAIT;
		break;
	case Malcolm::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
			if (atkCooldownTimer <= 0)
			{
				if (!Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) { movingAlongX = true; state = MOVE; }
				else
				{
					uniform_int_distribution<mt19937::result_type> random100(1, 100);
					int randomNum = random100(random);
					if (randomNum < 50) state = THREAT;
					else state = BLOCKING;
				}
			}
		}
		break;
	case Malcolm::MOVE:
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
	case Malcolm::ATK1:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != PUNCH) sprite->changeAnimation(PUNCH);
			punch->activate(pos, flip);
			atkCooldownTimer = atkCooldown;
			delay = 3.5f / 8.f;
			state = ATK2;
		}
		break;
	case Malcolm::ATK2:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != KICK) sprite->changeAnimation(KICK);
			kick->activate(pos, flip);
			delay = 3.5f / 8.f;
			state = WAIT;
		}
		break;
	case Malcolm::BLOCKING:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != BLOCK) sprite->changeAnimation(BLOCK);
			uniform_int_distribution<mt19937::result_type> random2(1, 2);
			delay = random2(random);
			state = WAIT;
		}
		break;
	case Malcolm::THREAT:
		playerPos = Physics::instance().getPlayerPos();
		if (playerPos.x <= pos.x && !flip) flip = true;
		if (playerPos.x > pos.x && flip) flip = false;

		if (sprite->animation() != THREATING) sprite->changeAnimation(THREATING);

		delay = 6.5f / 8.f;
		state = ATK1;
		break;
	default:
		break;
	}
}

void Malcolm::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	punch->box->increasePos(lastDeltaPos);
	kick->box->increasePos(lastDeltaPos);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		punch->box->increasePos(-lastDeltaPos);
		kick->box->increasePos(-lastDeltaPos);
		movingAlongX = !movingAlongX;
	}
}

void Malcolm::kill()
{
	// Down
	if (sprite->animation() != BLOCK && !dying)
	{
		state = DEAD;
		hitBox->active = false;
		baseBox->active = false;
		punch->box->active = false;
		kick->box->active = false;
		fixAnim = true;
		dying = true;
		delay = 16.5f / 8.f;
		if (sprite->animation() != DOWN) sprite->changeAnimation(DOWN);
	}
}

vector<Attack*> Malcolm::getAttacks()
{
	vector<Attack*> a;
	a.push_back(punch);
	a.push_back(kick);
	return a;
}
