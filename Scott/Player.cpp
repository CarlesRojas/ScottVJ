#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


Player * Player::createPlayer(const int player, const glm::vec2 & initialPos, UI *ui, const int windowHeight, ShaderProgram * program)
{
	Player *p = new Player(player, initialPos, ui, windowHeight, program);
	return p;
}

Player::Player(const int player, const glm::vec2 &initialPos, UI *ui, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->ui = ui;
	this->playerType = player;
	this->pos = initialPos;

	speed = 250;
	runSpeed = 500;
	hp = 3;
	delay = 0.f;
	flip = fixAnim = fixPos = dying = reviving = false;
	scaleFactor = ((float)windowHeight / 256.f);

	// Scott 
	if (playerType == 0)
	{
		spriteSheet.loadFromFile("sprites/scott/scott_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spriteSheet.setWrapS(GL_CLAMP_TO_EDGE);
		spriteSheet.setWrapT(GL_CLAMP_TO_EDGE);
		spriteSheet.setMinFilter(GL_NEAREST);
		spriteSheet.setMagFilter(GL_NEAREST);

		sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &spriteSheet, shaderProgram);
		sprite->setNumberAnimations(10);

		sprite->setAnimationSpeed(IDLE, 8);
		sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(4 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(5 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(6 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(7 * 0.05f, 2 * 0.05f));

		sprite->setAnimationSpeed(WALK, 8);
		sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 7 * 0.05f));

		sprite->setAnimationSpeed(RUN, 8);
		sprite->addKeyframe(RUN, glm::vec2(0 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(1 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(2 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(3 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(4 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(5 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(6 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(7 * 0.05f, 5 * 0.05f));

		sprite->setAnimationSpeed(PUNCH1, 8);
		sprite->addKeyframe(PUNCH1, glm::vec2(0 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(1 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(2 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(3 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(PUNCH2, 8);
		sprite->addKeyframe(PUNCH2, glm::vec2(4 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(5 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(6 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(7 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(PUNCH3, 8);
		sprite->addKeyframe(PUNCH3, glm::vec2(8 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(9 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(10 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(11 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(SPECIAL, 8);
		sprite->addKeyframe(SPECIAL, glm::vec2(0 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(1 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(2 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(3 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(4 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(5 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(6 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(7 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(8 * 0.05f, 0 * 0.05f));

		sprite->setAnimationSpeed(SPIN, 8);
		sprite->addKeyframe(SPIN, glm::vec2(0 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(1 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(2 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(3 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(4 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(5 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(6 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(7 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(8 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(9 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(10 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(11 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(12 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(13 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(14 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(15 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(16 * 0.05f, 6 * 0.05f));

		sprite->setAnimationSpeed(DOWN, 8);
		sprite->addKeyframe(DOWN, glm::vec2(0 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(1 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(2 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(3 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(4 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(5 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(6 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(7 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(8 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(9 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(10 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(11 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(12 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(13 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(14 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(15 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(16 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(17 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(18 * 0.05f, 1 * 0.05f));

		sprite->setAnimationSpeed(REVIVE, 4);
		sprite->addKeyframe(REVIVE, glm::vec2(0 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(1 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(2 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(3 * 0.05f, 4 * 0.05f));

		// Add Attacks
		punch = Attack::createAttack(Box::PLAYER, pos, glm::vec2(20 * scaleFactor, -25 * scaleFactor), glm::vec2(40 * scaleFactor, 20 * scaleFactor), 3.5f / 8.f, 0, 1.5f / 8.f, true, false, glm::vec2(0, 0));
		spin = Attack::createAttack(Box::PLAYER, pos, glm::vec2(0, 0), glm::vec2(120 * scaleFactor, 50 * scaleFactor), 16.5f / 8.f, 0, .5f / 8.f, false, true, glm::vec2(0, 0));
		special = Attack::createAttack(Box::PLAYER, pos, glm::vec2(0, 0), glm::vec2(120 * scaleFactor, 120 * scaleFactor), 8.5f / 8.f, 0, 4.f / 8.f, false, false, glm::vec2(0, 0));
	}

	// Ramona
	else if (playerType == 1)
	{

	}

	// Kim
	else
	{
		spriteSheet.loadFromFile("sprites/kim/kim_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spriteSheet.setWrapS(GL_CLAMP_TO_EDGE);
		spriteSheet.setWrapT(GL_CLAMP_TO_EDGE);
		spriteSheet.setMinFilter(GL_NEAREST);
		spriteSheet.setMagFilter(GL_NEAREST);

		sprite = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &spriteSheet, shaderProgram);
		sprite->setNumberAnimations(10);

		sprite->setAnimationSpeed(IDLE, 8);
		sprite->addKeyframe(IDLE, glm::vec2(0 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(1 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(2 * 0.05f, 2 * 0.05f));
		sprite->addKeyframe(IDLE, glm::vec2(3 * 0.05f, 2 * 0.05f));

		sprite->setAnimationSpeed(WALK, 8);
		sprite->addKeyframe(WALK, glm::vec2(0 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(1 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(2 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(3 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(4 * 0.05f, 7 * 0.05f));
		sprite->addKeyframe(WALK, glm::vec2(5 * 0.05f, 7 * 0.05f));

		sprite->setAnimationSpeed(RUN, 8);
		sprite->addKeyframe(RUN, glm::vec2(0 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(1 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(2 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(3 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(4 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(5 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(6 * 0.05f, 5 * 0.05f));
		sprite->addKeyframe(RUN, glm::vec2(7 * 0.05f, 5 * 0.05f));

		sprite->setAnimationSpeed(PUNCH1, 8);
		sprite->addKeyframe(PUNCH1, glm::vec2(0 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(1 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(2 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH1, glm::vec2(3 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(PUNCH2, 8);
		sprite->addKeyframe(PUNCH2, glm::vec2(4 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(5 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(6 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH2, glm::vec2(7 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(PUNCH3, 8);
		sprite->addKeyframe(PUNCH3, glm::vec2(8 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(9 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(10 * 0.05f, 3 * 0.05f));
		sprite->addKeyframe(PUNCH3, glm::vec2(11 * 0.05f, 3 * 0.05f));

		sprite->setAnimationSpeed(SPECIAL, 8);
		sprite->addKeyframe(SPECIAL, glm::vec2(0 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(1 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(2 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(3 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(4 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(5 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(6 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(7 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(8 * 0.05f, 0 * 0.05f));
		sprite->addKeyframe(SPECIAL, glm::vec2(9 * 0.05f, 0 * 0.05f));

		sprite->setAnimationSpeed(SPIN, 8);
		sprite->addKeyframe(SPIN, glm::vec2(0 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(1 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(2 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(3 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(4 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(5 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(6 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(7 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(8 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(9 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(10 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(11 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(12 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(13 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(14 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(15 * 0.05f, 6 * 0.05f));
		sprite->addKeyframe(SPIN, glm::vec2(16 * 0.05f, 6 * 0.05f));

		sprite->setAnimationSpeed(DOWN, 8);
		sprite->addKeyframe(DOWN, glm::vec2(0 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(1 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(2 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(3 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(4 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(5 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(6 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(7 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(8 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(9 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(10 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(11 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(12 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(13 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(14 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(15 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(16 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(17 * 0.05f, 1 * 0.05f));
		sprite->addKeyframe(DOWN, glm::vec2(18 * 0.05f, 1 * 0.05f));

		sprite->setAnimationSpeed(REVIVE, 4);
		sprite->addKeyframe(REVIVE, glm::vec2(0 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(1 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(2 * 0.05f, 4 * 0.05f));
		sprite->addKeyframe(REVIVE, glm::vec2(3 * 0.05f, 4 * 0.05f));

		punch = Attack::createAttack(Box::PLAYER, pos, glm::vec2(20 * scaleFactor, -25 * scaleFactor), glm::vec2(40 * scaleFactor, 20 * scaleFactor), 3.5f / 8.f, 0, 1.5f / 8.f, true, false, glm::vec2(0, 0));
		spin = Attack::createAttack(Box::PLAYER, pos, glm::vec2(0, 0), glm::vec2(120 * scaleFactor, 50 * scaleFactor), 16.5f / 8.f, 0, .5f / 8.f, false, true, glm::vec2(0, 0));
		special = Attack::createAttack(Box::PLAYER, pos, glm::vec2(53 * scaleFactor, -8 * scaleFactor), glm::vec2(60 * scaleFactor, 50 * scaleFactor), 8.5f / 8.f, 5.f / 8.f, .5f / 8.f, false, true, glm::vec2(800.f, 0));

		// Special Attack Sprite
		Sprite * monster = Sprite::createSprite(true, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05, 0.05), &spriteSheet, shaderProgram);
		monster->setNumberAnimations(1);

		monster->setAnimationSpeed(0, 8);
		monster->addKeyframe(0, glm::vec2(0 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(1 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(2 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(3 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(4 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(5 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(6 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(7 * 0.05f, 8 * 0.05f));
		monster->addKeyframe(0, glm::vec2(8 * 0.05f, 8 * 0.05f));

		monster->changeAnimation(0);
		special->setSprite(monster, glm::vec2(20 * scaleFactor, 29 * scaleFactor));
	}

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);

	// Add Boxes
	hitBox = Box::createBox(Box::PLAYER, Box::HIT, pos, glm::vec2(20 * scaleFactor, 60 * scaleFactor));
	baseBox = Box::createBox(Box::PLAYER, Box::BASE, pos, glm::vec2(20 * scaleFactor, 10 * scaleFactor));
}

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
				sprite->changeAnimation(REVIVE);
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
			if (playerType == 0) delay = 8.5f / 8.f; // Scott
			else if (playerType == 1)  delay = 8.5f / 8.f; // Ramona
			else delay = 9.5f / 8.f; // Kim
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

	// BORRAR
	if (Game::instance().getKey('k')) kill();

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
