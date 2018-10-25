#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Scott.h"
#include "Kim.h"
#include "Ramona.h"

Player::Player()
{
	hitBox = NULL;
	baseBox = NULL;
	punch = NULL;
	spin = NULL;
	special = NULL;
	sprite = NULL;
}

Player::~Player()
{
	if (hitBox != NULL) delete hitBox;
	if (baseBox != NULL) delete baseBox;
	if (punch != NULL) delete punch;
	if (spin != NULL) delete spin;
	if (special != NULL) delete special;
	if (sprite != NULL) delete sprite;
}

Player * Player::createPlayer(const int player, const glm::vec2 & initialPos, UI *ui, const int windowHeight, ShaderProgram * program)
{
	switch (player)
	{
	case 0:
	{
		Scott *s = new Scott();
		s->init(initialPos, ui, windowHeight, program);
		return s;
		break;
	}
	case 1:
	{
		Ramona *r = new Ramona();
		r->init(initialPos, ui, windowHeight, program);
		return r;
		break;
	}
	default:
	{
		Kim *k = new Kim();
		k->init(initialPos, ui, windowHeight, program);
		return k;
		break;
	}
	}
}

void Player::init(const glm::vec2 & initialPos, UI * ui, const int windowHeight, ShaderProgram * shaderProgram) { }

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	punch->update(deltaTime);
	spin->update(deltaTime);
	special->update(deltaTime);

	float dt = deltaTime / 1000.f;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = reviving = false;
		if (dying)
		{
			dying = false;
			ui->changeHP(hp);
			if (hp > 0)
			{
				reviving = true;
				delay = 9.5f / 8.f;
				if(sprite->animation() != REVIVE) sprite->changeAnimation(REVIVE);
			}
			else
			{
				// Anim Fade
				// Game Over
			}
		}
	}

	if (!dying && !reviving && !fixPos) {

		// Move Left
		if (Game::instance().getKey('a'))
		{
			if (!flip) flip = true;
			move(glm::vec2(-1.f, 0.f), dt);
		}

		// Move Right
		else if (Game::instance().getKey('d'))
		{
			if (flip) flip = false;
			move(glm::vec2(1.f, 0.f), dt);
		}

		// Move Up
		if (Game::instance().getKey('w'))
			move(glm::vec2(0.f, -1.f), dt);

		// Move Down
		else if (Game::instance().getKey('s'))
			move(glm::vec2(0.f, 1.f), dt);

		// Punch
		if (Game::instance().getKey('i') && sprite->animation() != PUNCH1 && !fixAnim && ui->canAttack())
		{
			punch->activate(pos, flip);

			fixAnim = true;
			fixPos = true;
			delay = 3.5f / 8.f;
			sprite->changeAnimation(PUNCH1);
		}

		// Spin
		if (Game::instance().getKey('o') && sprite->animation() != SPIN && !fixAnim && ui->canSpin())
		{
			spin->activate(pos, flip);

			fixAnim = true;
			delay = 16.5f / 8.f;
			sprite->changeAnimation(SPIN);
		}

		// Special
		if (Game::instance().getKey('p') && sprite->animation() != SPECIAL && !fixAnim && ui->canSpecial())
		{
			special->activate(pos, flip);

			fixAnim = true;
			fixPos = true;
			delay = getSpecialAttackDuration();
			sprite->changeAnimation(SPECIAL);
		}

		// Stand idle
		if (!Game::instance().getKey('w') &&
			!Game::instance().getKey('a') &&
			!Game::instance().getKey('s') &&
			!Game::instance().getKey('d') &&
			sprite->animation() != IDLE
			&& !fixAnim)
			sprite->changeAnimation(IDLE);
	}
	
	sprite->setPosition(pos);
}

void Player::render()
{
	sprite->render(flip);
}

void Player::move(glm::vec2 deltaPos, float deltaTime)
{
	if (Game::instance().getKey(' '))
	{
		if (sprite->animation() != RUN && !fixAnim) sprite->changeAnimation(RUN);
		lastDeltaPos = deltaPos * (float)runSpeed * deltaTime;
	}
	else
	{
		if (sprite->animation() != WALK && !fixAnim) sprite->changeAnimation(WALK);
		lastDeltaPos = deltaPos * (float)speed * deltaTime;
	}

	pos += lastDeltaPos;
	hitBox->increasePos(lastDeltaPos);
	baseBox->increasePos(lastDeltaPos);
	spin->increasePos(lastDeltaPos, false);

	if (!Physics::instance().correctPosition(baseBox)) {
		pos -= lastDeltaPos;
		hitBox->increasePos(-lastDeltaPos);
		baseBox->increasePos(-lastDeltaPos);
		spin->increasePos(-lastDeltaPos, false);
	}
}

void Player::kill()
{
	// Down
	if (!dying && !reviving && sprite->animation() != DOWN && !fixAnim)
	{
		punch->deactivate();
		spin->deactivate();
		special->deactivate();

		--hp;
		fixAnim = true;
		dying = true;
		delay = 18.5f / 8.f;
		sprite->changeAnimation(DOWN);
	}
}

vector<Attack*> Player::getAttacks()
{
	vector<Attack*> a;
	a.push_back(punch);
	a.push_back(spin);
	a.push_back(special);
	return a;
}

float Player::getSpecialAttackDuration() { return 0.f; }
