#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Scott.h"
#include "Kim.h"
#include "Ramona.h"
#include "Audio.h"

Player::Player()
{
	hitBox = NULL;
	baseBox = NULL;
	punch0 = NULL;
	punch1 = NULL;
	punch2 = NULL;
	spin = NULL;
	special = NULL;
	sprite = NULL;
}

Player::~Player()
{
	if (hitBox != NULL) delete hitBox;
	if (baseBox != NULL) delete baseBox;
	if (punch0 != NULL) delete punch0;
	if (punch1 != NULL) delete punch1;
	if (punch2 != NULL) delete punch2;
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
		s->character = player;
		return s;
		break;
	}
	case 1:
	{
		Ramona *r = new Ramona();
		r->init(initialPos, ui, windowHeight, program);
		r->character = player;
		return r;
		break;
	}
	default:
	{
		Kim *k = new Kim();
		k->init(initialPos, ui, windowHeight, program);
		k->character = player;
		return k;
		break;
	}
	}
}

void Player::init(const glm::vec2 & initialPos, UI * ui, const int windowHeight, ShaderProgram * shaderProgram) { }

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	punch0->update(deltaTime);
	punch1->update(deltaTime);
	punch2->update(deltaTime);
	spin->update(deltaTime);
	special->update(deltaTime);

	float dt = deltaTime / 1000.f;
	if (punchTimer > 0) punchTimer -= dt;
	else punchType = 0;

	if (delay > 0) delay -= dt;
	else
	{
		fixAnim = fixPos = reviving = false;
		if (dying)
		{
			dying = false;
			if (hp > 0)
			{
				reviving = true;
				delay = 9.5f / 8.f;
				if(sprite->animation() != REVIVE) sprite->changeAnimation(REVIVE);
				if(character == 0)
					Audio::instance().PlaySounds("audio/tired_male.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
				else 
					Audio::instance().PlaySounds("audio/tired_female.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
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
		if (Game::instance().getKey('i') && !fixAnim && ui->canAttack())
		{
			if (punchType == 0)
			{
				Audio::instance().PlaySounds("audio/punch_air.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
				
				punch0->activate(pos, flip);
				delay = 3.5f / 8.f;
				punchType = 1;
				punchTimer = 1.f;
				if(sprite->animation() != PUNCH1) sprite->changeAnimation(PUNCH1);
			}
			else if (punchType == 1)
			{
				Audio::instance().PlaySounds("audio/punch_air.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

				punch1->activate(pos, flip);
				delay = 3.5f / 8.f;
				punchType = 2;
				punchTimer = 1.f;
				if (sprite->animation() != PUNCH2) sprite->changeAnimation(PUNCH2);
			}
			else
			{
				Audio::instance().PlaySounds("audio/punch_air.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));

				punch2->activate(pos, flip);
				delay = getLastPunchDuration() / 8.f;
				punchType = 0;
				punchTimer = -1.f;
				if (sprite->animation() != PUNCH3) sprite->changeAnimation(PUNCH3);
			}

			fixAnim = true;
			fixPos = true;
		}

		// Spin
		if (Game::instance().getKey('o') && sprite->animation() != SPIN && !fixAnim && ui->canSpin())
		{
			spin->activate(pos, flip);
			Audio::instance().PlaySounds("audio/spin.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(2.0f));

			fixAnim = true;
			delay = 16.5f / 8.f;
			sprite->changeAnimation(SPIN);
		}

		// Special
		if (Game::instance().getKey('p') && sprite->animation() != SPECIAL && !fixAnim && ui->canSpecial())
		{
			special->activate(pos, flip);
			if (character == 2)
				Audio::instance().PlaySounds("audio/kim_monster.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			else
				Audio::instance().PlaySounds("audio/scott_ramona_fire.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
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

bool Player::kill()
{
	// Down
	if (!dying && !reviving && sprite->animation() != DOWN && !fixAnim)
	{
		punch0->deactivate();
		punch1->deactivate();
		punch2->deactivate();
		spin->deactivate();
		special->deactivate();

		--hp;
		ui->changeHP(hp);
		fixAnim = true;
		dying = true;
		delay = 18.5f / 8.f;
		sprite->changeAnimation(DOWN);
		return true;
	}
	return false;
}

vector<Attack*> Player::getAttacks()
{
	vector<Attack*> a;
	a.push_back(punch0);
	a.push_back(punch1);
	a.push_back(punch2);
	a.push_back(spin);
	a.push_back(special);
	return a;
}

float Player::getSpecialAttackDuration() { return 0.f; }

float Player::getLastPunchDuration() { return 3.5f; }
