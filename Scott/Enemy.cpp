#include "Enemy.h"
#include "Physics.h"
#include "Malcolm.h"
#include "Turret.h"
#include "Roxilla.h"
#include "Robot.h"
#include "Roxanne.h"

Enemy::Enemy()
{
	hitBox = NULL;
	baseBox = NULL;
	sprite = NULL;
}

Enemy::~Enemy()
{
	if (hitBox != NULL) delete hitBox;
	if (baseBox != NULL) delete baseBox;
	if (sprite != NULL) delete sprite;
}

Enemy * Enemy::createEnemy(const int enemy, const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * program)
{
	switch (enemy) 
	{
	case 0:
	{
		Malcolm *m = new Malcolm();
		m->init(initialPos, windowHeight, program);
		return m;
		break;
	}
	case 1:
	{
		Turret *t = new Turret();
		t->init(initialPos, windowHeight, program);
		return t;
		break;
	}
	case 2:
	{
		Roxilla *r = new Roxilla();
		r->init(initialPos, windowHeight, program);
		return r;
		break;
	}
	case 3:
	{
		Roxanne *r = new Roxanne();
		r->init(initialPos, windowHeight, program);
		return r;
		break;
	}
	case 4:
	{
		Robot *r = new Robot();
		r->init(initialPos, windowHeight, program);
		return r;
		break;
	}
	default:
	{
		Robot *r = new Robot();
		r->init(initialPos, windowHeight, program);
		return r;
		break;
	}
	}
}

void Enemy::init(const glm::vec2 & initialPos, const int windowHeight, ShaderProgram * shaderProgram) { }

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	float dt = deltaTime / 1000.f;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = false;
		if (dying) { dying = false; dead = true; }
	}

	enemyIA(deltaTime);
	sprite->setPosition(pos);
}

void Enemy::render() 
{ 
	sprite->render(flip); 
}

void Enemy::enemyIA(int deltaTime) { }

void Enemy::move(glm::vec2 deltaPos, float deltaTime) { }

void Enemy::kill() { }

vector<Attack*> Enemy::getAttacks() { return vector<Attack*>(); }

