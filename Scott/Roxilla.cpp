#include "Roxilla.h"
#include "Physics.h"
#include "Load.h"
#include "Audio.h"

Roxilla::Roxilla()
{
	fire = NULL;
}

Roxilla::~Roxilla()
{
	if (fire != NULL) delete fire;
}

void Roxilla::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	delay = 0.f;
	flip = fixAnim = fixPos = dying = dead = isBoss = active = false;
	speed = (int)(35 * scaleFactor);
	fireCooldown = 5.f;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.1f), &Load::instance().roxilla, shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(4 * 0.05f, 4 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(5 * 0.05f, 4 * 0.1f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(FIRE, 8);
	sprite->addKeyframe(FIRE, glm::vec2(0 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(1 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(2 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(3 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(4 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(5 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(6 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(7 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(8 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(9 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(10 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(11 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(FIRE, glm::vec2(12 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(MASKOFF, 8);
	sprite->addKeyframe(MASKOFF, glm::vec2(0 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(1 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(2 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(3 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(4 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(5 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(6 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(7 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(8 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(9 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(10 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(11 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(12 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(13 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(14 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(15 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(MASKOFF, glm::vec2(16 * 0.05f, 2 * 0.1f));

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(1 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(2 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(3 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(4 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(5 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(6 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(7 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(8 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(9 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(10 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(11 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(12 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(13 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(14 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(15 * 0.05f, 0 * 0.1f));
	sprite->addKeyframe(DOWN, glm::vec2(16 * 0.05f, 0 * 0.1f));

	// Add Boxes
	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(40 * scaleFactor, 70 * scaleFactor));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(40 * scaleFactor, 10 * scaleFactor));
	fire = Attack::createAttack(Box::ENEMY, pos, glm::vec2(80 * scaleFactor, -17 * scaleFactor), glm::vec2(50 * scaleFactor, 40 * scaleFactor), 4.5f / 8.f, 5.f / 8.f, 0.f / 8.f, false, false, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
	state = INACTIVE;
	alertRange = windowHeight;
	minAttackRange = glm::vec2(55.f * scaleFactor, 40.f * scaleFactor);
	maxAttackRange = glm::vec2(105.f * scaleFactor, -30.f * scaleFactor);

	// Random
	random.seed(random_device()());
}

void Roxilla::enemyIA(int deltaTime)
{
	fire->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (fireCooldownTimer > 0) fireCooldownTimer -= dt;

	switch (state)
	{
	case Roxilla::INACTIVE:
		if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
		if (Physics::instance().isCloseThan(this, alertRange))
		{
			state = WAIT;
			active = true;
		}
		break;
	case Roxilla::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
			if (fireCooldownTimer <= 0)
			{
				if (Physics::instance().isInAttackRange(this, minAttackRange, maxAttackRange)) state = ATK;
				else { movingAlongX = true; state = MOVE; }
			}
		}
		break;
	case Roxilla::MOVE:
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
				if(diff.y <= minAttackRange.y && diff.y >= maxAttackRange.y) movingAlongX = true;
				else if (randomNum < 10) movingAlongX = true;
				if (diff.y > minAttackRange.y) move(glm::vec2(0.f, -1.f), dt);
				else move(glm::vec2(0.f, 1.f), dt);
			}
		}
		break;
	case Roxilla::ATK:
		if (delay <= 0)
		{
			glm::vec2 playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x <= pos.x && !flip) flip = true;
			if (playerPos.x > pos.x && flip) flip = false;

			if (sprite->animation() != FIRE) sprite->changeAnimation(FIRE);
			fire->activate(pos, flip);
			Audio::instance().PlaySounds("audio/roxilla_fire.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			fireCooldownTimer = fireCooldown;
			delay = 12.5f / 8.f;
			state = MASK;
		}
		break;
	case Roxilla::MASK:
		if (delay <= 0)
		{
			if (sprite->animation() != MASKOFF) sprite->changeAnimation(MASKOFF);
			Audio::instance().PlaySounds("audio/tired_male.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

			delay = 16.5f / 8.f;
			state = WAIT;
		}
		break;
	default:
		break;
	}
}

void Roxilla::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	fire->box->increasePos(lastDeltaPos);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		fire->box->increasePos(-lastDeltaPos);
		movingAlongX = !movingAlongX;
	}
}

bool Roxilla::kill()
{
	// Down
	if (sprite->animation() == MASKOFF && !dying)
	{
		state = DEAD;
		hitBox->active = false;
		baseBox->active = false;
		fire->box->active = false;
		fixAnim = true;
		dying = true;
		delay = 16.5f / 8.f;
		if(sprite->animation() != DOWN) sprite->changeAnimation(DOWN);
		return true;
	}
	return false;
}

vector<Attack*> Roxilla::getAttacks()
{
	vector<Attack*> a;
	a.push_back(fire);
	return a;
}

