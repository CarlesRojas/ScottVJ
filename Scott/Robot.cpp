#include "Robot.h"
#include "Physics.h"
#include "Load.h"
#include "Audio.h"

Robot::Robot()
{
	laser = NULL;
	punch = NULL;
}

Robot::~Robot()
{
	if (laser != NULL) delete laser;
	if (punch != NULL) delete punch;
}

void Robot::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	delay = 0.f;
	fixAnim = fixPos = dying = dead = active = false;
	flip = true;
	isBoss = true;
	speed = (int)(45 * scaleFactor);
	hp = 4;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.1f), &Load::instance().robot, shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 0 * 0.1f));

	sprite->setAnimationSpeed(TOAST, 8);
	sprite->addKeyframe(TOAST, glm::vec2(0 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(1 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(2 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(3 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(4 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(5 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(6 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(7 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(8 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(9 * 0.05f, 7 * 0.1f));
	sprite->addKeyframe(TOAST, glm::vec2(10 * 0.05f, 7 * 0.1f));

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
	sprite->addKeyframe(FALLDOWN, glm::vec2(0 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(1 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(2 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(3 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(4 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(5 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(6 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(7 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(8 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(9 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(10 * 0.05f, 5 * 0.1f));
	sprite->addKeyframe(FALLDOWN, glm::vec2(11 * 0.05f, 5 * 0.1f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(6 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(7 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(PUNCH, 8);
	sprite->addKeyframe(PUNCH, glm::vec2(0 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(1 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(2 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(3 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(4 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(5 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(PUNCH, glm::vec2(6 * 0.05f, 2 * 0.1f));

	sprite->setAnimationSpeed(SHIELD, 8);
	sprite->addKeyframe(SHIELD, glm::vec2(0 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(1 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(2 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(3 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(4 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(5 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(6 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(SHIELD, glm::vec2(7 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(DYING, 8);
	sprite->addKeyframe(DYING, glm::vec2(0 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(1 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(2 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(3 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(4 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(5 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(6 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(7 * 0.05f, 6 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(0 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(1 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(2 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(3 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(4 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(5 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(6 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(7 * 0.05f, 8 * 0.1f));
	sprite->addKeyframe(DYING, glm::vec2(15 * 0.05f, 15 * 0.1f));

	sprite->setAnimationSpeed(NONE, 8);
	sprite->addKeyframe(NONE, glm::vec2(9 * 0.05f, 19 * 0.1f));

	// Sprite Laser
	spriteLaser = Sprite::createSprite(true, glm::vec2(1024.f * scaleFactor, 64.f * scaleFactor), glm::vec2(1, .05f), &Load::instance().robotLaser, shaderProgram);
	spriteLaser->setNumberAnimations(2);

	spriteLaser->setAnimationSpeed(LASER, 8);
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 0 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 1 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 2 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 3 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 4 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 5 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 6 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 7 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 8 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 9 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 10 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 11 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 12 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 13 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 14 * .05f));
	spriteLaser->addKeyframe(LASER, glm::vec2(0, 15 * .05f));

	spriteLaser->setAnimationSpeed(NOLASER, 8);
	spriteLaser->addKeyframe(NOLASER, glm::vec2(0, 16 * .05f));

	// Add Boxes
	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(38 * scaleFactor, 53 * scaleFactor));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(38 * scaleFactor, 10 * scaleFactor));
	punch = Attack::createAttack(Box::ENEMY, pos, glm::vec2(29 * scaleFactor, -12 * scaleFactor), glm::vec2(58 * scaleFactor, 21 * scaleFactor), 6.5f / 8.f, 0, 4.5f / 8.f, false, false, glm::vec2(0, 0));
	laser = Attack::createAttack(Box::ENEMY, pos, glm::vec2(256 * scaleFactor, -18 * scaleFactor), glm::vec2(512 * scaleFactor, 17 * scaleFactor), 15.5f / 8.f, 0, 6.5f / 8.f, false, false, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);

	spriteLaser->changeAnimation(NOLASER);
	spriteLaser->setPosition(pos);

	state = INACTIVE;
	alertRange = (int)(windowHeight * 1.5f);
	minAttackRange = glm::vec2(30.f * scaleFactor, 20.f * scaleFactor);
	maxAttackRange = glm::vec2(55.f * scaleFactor, -30.f * scaleFactor);

	minAttackRangeLaser = glm::vec2(70.f * scaleFactor, 25.f * scaleFactor);
	maxAttackRangeLaser = glm::vec2(500.f * scaleFactor, -30.f * scaleFactor);

	// Random
	random.seed(random_device()());
}

void Robot::update(int deltaTime)
{
	sprite->update(deltaTime);
	spriteLaser->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = false;
		if (dying) { dying = false; dead = true; }
	}

	enemyIA(deltaTime);
	sprite->setPosition(pos);
	spriteLaser->setPosition(pos);
}

void Robot::render()
{
	sprite->render(flip);
	spriteLaser->render(flip);
}

void Robot::enemyIA(int deltaTime)
{
	laser->update(deltaTime);
	punch->update(deltaTime);

	float dt = deltaTime / 1000.f;

	if (atkCooldownTimer > 0) atkCooldownTimer -= dt;
	glm::vec2 playerPos;

	switch (state)
	{
	case Robot::INACTIVE:
		if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
		if (Physics::instance().isCloseThan(this, alertRange))
		{
			delay = 1.f;
			state = TOASTING;
			active = true;
		}
		break;
	case Robot::TOASTING:
		if (delay <= 0)
		{
			Audio::instance().PlaySounds("audio/robot_toast.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

			if (sprite->animation() != TOAST) sprite->changeAnimation(TOAST);
			delay = 10.5f / 8.f;
			state = WAIT;

			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);
			if (randomNum < 33) nextAction = Robot::ATK1;
			else if (randomNum < 66) nextAction = Robot::ATK2;
			else nextAction = Robot::BLOCKING;
		}
		break;
	case Robot::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
			if (spriteLaser->animation() != NOLASER) spriteLaser->changeAnimation(NOLASER);
			if (atkCooldownTimer <= 0)
			{
				if (nextAction == Robot::ATK2)
				{
					if (!Physics::instance().isInAttackRange(this, minAttackRangeLaser, maxAttackRangeLaser)) { movingAlongX = true; state = MOVE; }
					else state = nextAction;
				}
				else 
				{
					if (!Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) { movingAlongX = true; state = MOVE; }
					else state = nextAction;
				}
			}
		}
		break;

	case Robot::MOVE:
		if (sprite->animation() != WALK) sprite->changeAnimation(WALK);

		if (nextAction == Robot::ATK2)
		{
			if (Physics::instance().isInAttackRange(this, minAttackRangeLaser, maxAttackRangeLaser)) state = WAIT;
			else
			{
				glm::vec2 diff = Physics::instance().distToPlayer(this);
				uniform_int_distribution<mt19937::result_type> random600(1, 600); // if (randNum < 10) means once per second
				int randomNum = random600(random);
				if (movingAlongX)
				{
					// Player too close -> Move Away
					if (diff.x > -minAttackRangeLaser.x && diff.x < minAttackRangeLaser.x)
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
						if (abs(diff.x) >= minAttackRangeLaser.x && abs(diff.x) <= maxAttackRangeLaser.x) movingAlongX = false;
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
					if (diff.y <= minAttackRangeLaser.y && diff.y >= maxAttackRangeLaser.y) movingAlongX = true;
					else if (randomNum < 10) movingAlongX = true;
					if (diff.y > minAttackRangeLaser.y) move(glm::vec2(0.f, -1.f), dt);
					else move(glm::vec2(0.f, 1.f), dt);
				}
			}
		}
		else
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

		break;
	case Robot::ATK1:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != PUNCH) sprite->changeAnimation(PUNCH);
			punch->activate(pos, flip);
			Audio::instance().PlaySounds("audio/punch_air.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

			atkCooldownTimer = 3.f;
			delay = 6.5f / 8.f;
			state = WAIT;

			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);
			if (randomNum < 33) nextAction = Robot::ATK1;
			else if (randomNum < 66) nextAction = Robot::ATK2;
			else nextAction = Robot::BLOCKING;
		}
		break;
	case Robot::ATK2:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != NONE) sprite->changeAnimation(NONE);
			if (spriteLaser->animation() != LASER) spriteLaser->changeAnimation(LASER);

			laser->activate(pos, flip);
			Audio::instance().PlaySounds("audio/robot_laser.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

			atkCooldownTimer = 5.f;
			delay = 15.5f / 8.f;
			
			state = WAIT;

			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);
			if (randomNum < 33) nextAction = Robot::ATK1;
			else if (randomNum < 66) nextAction = Robot::ATK2;
			else nextAction = Robot::BLOCKING;
			
		}
		break;
	case Robot::BLOCKING:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != SHIELD) sprite->changeAnimation(SHIELD);
			delay = 7.5f / 8.f;
			atkCooldownTimer = 2.f;
			state = WAIT;

			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);
			if (randomNum < 33) nextAction = Robot::ATK1;
			else if (randomNum < 66) nextAction = Robot::ATK2;
			else nextAction = Robot::BLOCKING;
		}
		break;
	case Robot::FALLING:
		if (delay <= 0)
		{
			playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != FALLDOWN) sprite->changeAnimation(FALLDOWN);
			delay = 21.5f / 8.f;
			state = WAIT;

			uniform_int_distribution<mt19937::result_type> random100(1, 100);
			int randomNum = random100(random);
			if (randomNum < 33) nextAction = Robot::ATK1;
			else if (randomNum < 66) nextAction = Robot::ATK2;
			else nextAction = Robot::BLOCKING;
		}
		break;
	default:
		break;
	}
}

void Robot::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	punch->box->increasePos(lastDeltaPos);
	laser->box->increasePos(lastDeltaPos);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		punch->box->increasePos(-lastDeltaPos);
		laser->box->increasePos(-lastDeltaPos);
		movingAlongX = !movingAlongX;
	}
}

bool Robot::kill()
{
	
	// Down
	if (sprite->animation() != SHIELD &&
		sprite->animation() != FALLDOWN &&
		sprite->animation() != DYING &&
		sprite->animation() != PUNCH &&
		sprite->animation() != TOAST &&
		spriteLaser->animation() != LASER &&
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
			Audio::instance().PlaySounds("audio/robot_dead.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

			state = DEAD;
			hitBox->active = false;
			baseBox->active = false;
			punch->box->active = false;
			laser->box->active = false;
			fixAnim = true;
			dying = true;
			delay = 16.5f / 8.f;
			if (sprite->animation() != DYING) sprite->changeAnimation(DYING);
		}
		return true;
	}
	return false;
}

vector<Attack*> Robot::getAttacks()
{
	vector<Attack*> a;
	a.push_back(punch);
	a.push_back(laser);
	return a;
}

