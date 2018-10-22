#include "Enemy.h"
#include "Physics.h"


Enemy * Enemy::createEnemy(const int enemy, const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * program)
{
	Enemy *e = new Enemy(enemy, initialPos, windowHeight, program);
	return e;
}

Enemy::Enemy(const int enemy, const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->state = enemyState::IDLE;
	this->enemyType = enemy;
	this->pos = initialPos;

	delay = 0.f;
	flip = fixAnim = fixPos = dying = dead = false;
	scaleFactor = ((float)windowHeight / 256.f);

	switch (enemyType)
	{
	case 0: // Malcolm
		speed = 250;

		spritesheet.loadFromFile("sprites/malcolm/malcolm_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
		spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
		spritesheet.setMinFilter(GL_NEAREST);
		spritesheet.setMagFilter(GL_NEAREST);

		sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &spritesheet, shaderProgram);
		sprite->setNumberAnimations(10);

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

		sprite->setAnimationSpeed(SPECIAL, 8);
		sprite->addKeyframe(SPECIAL, glm::vec2(0 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(1 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(2 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(3 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(4 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(5 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(6 * 0.05f, 2 * 0.05f));

		sprite->setAnimationSpeed(ATTACK, 8);
		sprite->addKeyframe(ATTACK, glm::vec2(0 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(1 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(2 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(3 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(4 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(5 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(6 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(7 * 0.05f, 3 * 0.05f));

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

		hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(35 * ((float)windowHeight / 256.f), 70 * ((float)windowHeight / 256.f)));
		baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(35 * ((float)windowHeight / 256.f), 10 * ((float)windowHeight / 256.f)));
		break;
	case 1: // ??
	default: // Roxilla
		speed = 150;

		spritesheet.loadFromFile("sprites/roxilla/roxilla_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
		spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
		spritesheet.setMinFilter(GL_NEAREST);
		spritesheet.setMagFilter(GL_NEAREST);

		sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &spritesheet, shaderProgram);
		sprite->setNumberAnimations(10);

		sprite->setAnimationSpeed(IDLE, 8);
		sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(4 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(5 * 0.05f, 4 * 0.05f));

		sprite->setAnimationSpeed(WALK, 8);
		sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 1 * 0.05f));

		sprite->setAnimationSpeed(ATTACK, 8);
		sprite->addKeyframe(ATTACK, glm::vec2(0 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(1 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(2 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(3 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(4 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(5 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(6 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(7 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(8 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(9 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(10 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(11 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(ATTACK, glm::vec2(12 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(SPECIAL, 8);
		sprite->addKeyframe(SPECIAL, glm::vec2(0 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(1 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(2 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(3 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(4 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(5 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(6 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(7 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(8 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(9 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(10 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(11 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(12 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(13 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(14 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(15 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(16 * 0.05f, 2 * 0.05f));

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

		// Add Boxes
		hitBox = Box::createBox(Box::ENEMY, Box::HIT, pos, glm::vec2(40 * scaleFactor, 70 * scaleFactor));
		baseBox = Box::createBox(Box::ENEMY, Box::BASE, pos, glm::vec2(40 * scaleFactor, 10 * scaleFactor));
		fire = Attack::createAttack(Box::ENEMY, pos, glm::vec2(80 * scaleFactor, -7 * scaleFactor), glm::vec2(70 * scaleFactor, 60 * scaleFactor), 12.5f / 8.f, 5.f / 8.f, 3.5f / 8.f, true, false, glm::vec2(0, 0));
		break;
	}

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (delay <= 0 && delay2 > 0) delay2 -= dt;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = false;
		if (dying)
		{
			dying = false;
			dead = true;
		}
	}
	enemyIA();
	sprite->setPosition(pos);
}

void Enemy::render()
{
	sprite->render(flip);
}

void Enemy::enemyIA() 
{
	switch (state)
	{
	case Enemy::IDLE:
		if (delay > 0) 
		{
			sprite->changeAnimation(EnemyAnims::IDLE);
			if (delay2 > 0)
			{
				if (Physics::instance().isCloseThan(this, 20)) state = enemyState::ATTACK;
				else if (Physics::instance().isCloseThan(this, 400)) state = MOVE;
			}
		}
		break;
	case Enemy::MOVE:

		break;
	case Enemy::ATTACK:
		if (delay > 0) 
		{
			fire->activate(pos, flip);
			delay = 12.5f / 8.f;
			fixAnim = true;
			fixPos = true;
			sprite->changeAnimation(EnemyAnims::ATTACK);
			state = MASK;
		}
		break;
	case Enemy::MASK:
		if (delay > 0)
		{
			delay = 16.5f / 8.f;
			delay2 = 12.f / 8.f;
			fixAnim = true;
			fixPos = true;
			sprite->changeAnimation(EnemyAnims::SPECIAL);
			state = IDLE;
		}
		break;
	default:
		break;
	}
}

void Enemy::move(glm::vec2 deltaPos, float deltaTime)
{
	if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
	lastDeltaPos = glm::vec2(deltaPos.x * speed, deltaPos.y * speed) * deltaTime;

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
}

void Enemy::revertMove()
{
	pos -= lastDeltaPos;
	hitBox->increasePos(-lastDeltaPos);
	baseBox->increasePos(-lastDeltaPos);
}

void Enemy::kill()
{
	// Down
	if ((state == IDLE || state == MASK) && !dying && sprite->animation() != DOWN && !fixAnim)
	{
		hitBox->active = false;
		baseBox->active = false;
		fixAnim = true;
		dying = true;
		delay = 16.5f / 8.f;
		sprite->changeAnimation(DOWN);
	}
}

vector<Attack*> Enemy::getAttacks()
{
	vector<Attack*> a;
	return a;
}
