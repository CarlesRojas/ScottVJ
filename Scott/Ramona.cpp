#include "Ramona.h"
#include "Load.h"

void Ramona::init(const glm::vec2 & initialPos, UI * ui, const int windowHeight, ShaderProgram * shaderProgram)
{
	this->ui = ui;
	this->pos = initialPos;
	speed = 250;
	runSpeed = 500;
	hp = 3;
	delay = 0.f;
	flip = fixAnim = fixPos = dying = reviving = false;
	scaleFactor = ((float)windowHeight / 256.f);



	// Add Boxes
	hitBox = Box::createBox(Box::PLAYER, Box::HIT, pos, glm::vec2(20 * scaleFactor, 60 * scaleFactor));
	baseBox = Box::createBox(Box::PLAYER, Box::BASE, pos, glm::vec2(20 * scaleFactor, 10 * scaleFactor));
	
	sprite->changeAnimation(IDLE);
	sprite->setPosition(pos);
}

float Ramona::getSpecialAttackDuration()
{
	return 9.5f / 8.f;
}

