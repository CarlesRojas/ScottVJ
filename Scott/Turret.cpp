#include "Turret.h"
#include "Physics.h"
#include "Load.h"
#include "Audio.h"

Turret::Turret()
{
	shoot = NULL;
}

Turret::~Turret()
{
	if (shoot != NULL) delete shoot;
}

void Turret::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->pos = initialPos;
	scaleFactor = ((float)windowHeight / 256.f);
	shootSpeed = 240 * scaleFactor;
	delay = 0.f;
	flip = true;
	fixAnim = fixPos = dying = dead = isBoss = active = false;

	sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05f, 0.1f), &Load::instance().turret, shaderProgram);
	sprite->setNumberAnimations(6);

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

	sprite->setAnimationSpeed(DEPLOY, 8);
	sprite->addKeyframe(DEPLOY, glm::vec2(0 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(5 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(6 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(7 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(8 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(DEPLOY, glm::vec2(9 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(HIDE, 8);
	sprite->addKeyframe(HIDE, glm::vec2(9 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(8 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(7 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(6 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(5 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(4 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(3 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(2 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(1 * 0.05f, 1 * 0.1f));
	sprite->addKeyframe(HIDE, glm::vec2(0 * 0.05f, 1 * 0.1f));

	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0 * 0.05f, 2 * 0.1f));
	sprite->addKeyframe(SHOOT, glm::vec2(1 * 0.05f, 2 * 0.1f));
	
	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 3 * 0.1f));
	sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 3 * 0.1f));

	sprite->setAnimationSpeed(HIDDEN, 8);
	sprite->addKeyframe(HIDDEN, glm::vec2(0 * 0.05f, 1 * 0.1f));

	// Add Boxes
	hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(80 * scaleFactor, 77 * scaleFactor));
	baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(80 * scaleFactor, 15 * scaleFactor));
	shoot = Attack::createAttack(Box::ENEMY, pos, glm::vec2(-46 * scaleFactor, -46 * scaleFactor), glm::vec2(8 * scaleFactor, 8 * scaleFactor), 3, 0, 0, true, false, glm::vec2(-shootSpeed, 0));

	// Shoot Attack Sprite
	Sprite * shot = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.1f), &Load::instance().turret, shaderProgram);
	shot->setNumberAnimations(1);

	shot->setAnimationSpeed(0, 8);
	shot->addKeyframe(0, glm::vec2(0 * 0.05f, 4 * 0.1f));
	shot->addKeyframe(0, glm::vec2(1 * 0.05f, 4 * 0.1f));
	shot->addKeyframe(0, glm::vec2(2 * 0.05f, 4 * 0.1f));

	shot->changeAnimation(0);
	shoot->setSprite(shot, glm::vec2(0, 0));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
	state = INACTIVE;
	alertRange = windowHeight * 5;

	// Random
	random.seed(random_device()());
}

void Turret::enemyIA(int deltaTime)
{
	shoot->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (shootCooldownTimer > 0) shootCooldownTimer -= dt;

	switch (state)
	{
	case Turret::INACTIVE:
		if (delay <= 0)
		{
			if (sprite->animation() != HIDDEN) sprite->changeAnimation(HIDDEN);

			glm::vec2 playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x - pos.x > 0 && Physics::instance().isCloseThan(this, alertRange))
			{
				if (sprite->animation() != DEPLOY) sprite->changeAnimation(DEPLOY);
				Audio::instance().PlaySounds("audio/turret_deploy.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
				delay = 9.5f / 8.f;
				state = WAIT;
				active = true;
			}
		}
		break;
	case Turret::WAIT:
		if (delay <= 0)
		{
			if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);

			glm::vec2 playerPos = Physics::instance().getPlayerPos();
			if (playerPos.x - pos.x < 0 || !Physics::instance().isCloseThan(this, alertRange))
			{
				if (sprite->animation() != HIDE) sprite->changeAnimation(HIDE);
				delay = 9.5f / 8.f;
				state = INACTIVE;
			}
			else if (shootCooldownTimer <= 0) state = ATK;
		}
		break;
	case Turret::ATK:
		if (delay <= 0)
		{
			if (sprite->animation() != SHOOT) sprite->changeAnimation(SHOOT);
			shoot->activate(pos, flip);
			Audio::instance().PlaySounds("audio/turret_shot.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			shootCooldownTimer = 1.5f;
			delay = 1.5f / 8.f;
			state = WAIT;
		}
		break;
	default:
		break;
	}
}

bool Turret::kill()
{
	// Down
	if (sprite->animation() != HIDDEN && !dying)
	{
		state = DEAD;
		hitBox->active = false;
		baseBox->active = false;
		shoot->box->active = false;
		fixAnim = true;
		dying = true;
		delay = 10.5f / 8.f;
		if (sprite->animation() != DOWN) sprite->changeAnimation(DOWN);
		Audio::instance().PlaySounds("audio/turret_destroy.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
		return true;
	}
	return false;
}

vector<Attack*> Turret::getAttacks()
{
	vector<Attack*> a;
	a.push_back(shoot);
	return a;
}
