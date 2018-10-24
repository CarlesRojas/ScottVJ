#include "Scott.h"

void Scott::init(const glm::vec2 & initialPos, UI * ui, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->ui = ui;
	this->pos = initialPos;
	speed = 250;
	runSpeed = 500;
	hp = 3;
	delay = 0.f;
	flip = fixAnim = fixPos = dying = reviving = false;
	scaleFactor = ((float)windowHeight / 256.f);

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
	
	// Add Boxes
	hitBox = Box::createBox(Box::PLAYER, Box::HIT, pos, glm::vec2(20 * scaleFactor, 60 * scaleFactor));
	baseBox = Box::createBox(Box::PLAYER, Box::BASE, pos, glm::vec2(20 * scaleFactor, 10 * scaleFactor));

	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
}

float Scott::getSpecialAttackDuration()
{
	return 8.5f / 8.f;
}
