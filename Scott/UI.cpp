#include "UI.h"
#include <glm/gtc/matrix_transform.hpp>


enum UIAnims
{
	WHITE, COOLDOWN
};

UI * UI::createUI(int playerCharacter, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program)
{
	UI *ui = new UI(playerCharacter, attackCD, spinCD, specialCD, windowSize, program);
	return ui;
}

UI::UI(int playerCharacter, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program)
{
	this->program = program;

	attackCooldown = attackCD;
	spinCooldown = spinCD;
	specialCooldown = specialCD;

	attackCooldownTimer = 0;
	spinCooldownTimer = 0;
	specialCooldownTimer = 0;

	// Static UI
	spriteSheet.loadFromFile("sprites/ui/Scott_UI_256.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSheet.setWrapS(GL_CLAMP_TO_EDGE);
	spriteSheet.setWrapT(GL_CLAMP_TO_EDGE);
	spriteSheet.setMinFilter(GL_NEAREST);
	spriteSheet.setMagFilter(GL_NEAREST);

	player = playerCharacter;
	winSize = windowSize;
	tileTexSize = 1.f / 20.f;

	glm::vec2 texCoordTile[2];
	texCoordTile[0] = glm::vec2(player * tileTexSize, 5 * tileTexSize);
	texCoordTile[1] = texCoordTile[0] + tileTexSize;

	// First triangle
	vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(winSize.y); vertices.push_back(0.f);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(winSize.y); vertices.push_back(winSize.y);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);

	// Second triangle
	vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(winSize.y); vertices.push_back(winSize.y);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
	vertices.push_back(0.f); vertices.push_back(winSize.y);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));

	// Animatied UI - Numbers
	hpSprite = Sprite::createSprite(false, glm::vec2(256.f * ((float)windowSize.y / 256.f), 256.f * ((float)windowSize.y / 256.f)), glm::vec2(0.05, 0.05), &spriteSheet, program);
	hpSprite->setNumberAnimations(4);

	hpSprite->setAnimationSpeed(0, 1);
	hpSprite->addKeyframe(0, glm::vec2(3 * 0.05f, 5 * 0.05f));
	hpSprite->setAnimationSpeed(1, 1);
	hpSprite->addKeyframe(1, glm::vec2(4 * 0.05f, 5 * 0.05f));
	hpSprite->setAnimationSpeed(2, 1);
	hpSprite->addKeyframe(2, glm::vec2(5 * 0.05f, 5 * 0.05f));
	hpSprite->setAnimationSpeed(3, 1);
	hpSprite->addKeyframe(3, glm::vec2(6 * 0.05f, 5 * 0.05f));
	hpSprite->changeAnimation(3);
	hpSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Attack
	attackSprite = Sprite::createSprite(false, glm::vec2(256.f * ((float)windowSize.y / 256.f), 256.f * ((float)windowSize.y / 256.f)), glm::vec2(0.05, 0.05), &spriteSheet, program);
	attackSprite->setNumberAnimations(2);

	attackSprite->setAnimationSpeed(WHITE, 1);
	attackSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, 0 * 0.05f));

	attackSprite->setAnimationSpeed(COOLDOWN, 16.f / attackCooldown);
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, 0 * 0.05f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, 0 * 0.05f));
	attackSprite->changeAnimation(WHITE);
	attackSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Spin
	spinSprite = Sprite::createSprite(false, glm::vec2(256.f * ((float)windowSize.y / 256.f), 256.f * ((float)windowSize.y / 256.f)), glm::vec2(0.05, 0.05), &spriteSheet, program);
	spinSprite->setNumberAnimations(2);

	spinSprite->setAnimationSpeed(WHITE, 1);
	spinSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, 1 * 0.05f));

	spinSprite->setAnimationSpeed(COOLDOWN, 16.f / spinCooldown);
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, 1 * 0.05f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, 1 * 0.05f));
	spinSprite->changeAnimation(WHITE);
	spinSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Special
	specialSprite = Sprite::createSprite(false, glm::vec2(256.f * ((float)windowSize.y / 256.f), 256.f * ((float)windowSize.y / 256.f)), glm::vec2(0.05, 0.05), &spriteSheet, program);
	specialSprite->setNumberAnimations(2);

	specialSprite->setAnimationSpeed(WHITE, 1);
	specialSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, (2 + player) * 0.05f));

	specialSprite->setAnimationSpeed(COOLDOWN, 16.f / specialCooldown);
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, (2 + player) * 0.05f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, (2 + player) * 0.05f));
	specialSprite->changeAnimation(WHITE);
	specialSprite->setPosition(glm::vec2(0.f, 0.f));
}

void UI::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(posDispl.x, posDispl.y, 0.f));
	program->setUniformMatrix4f("modelview", modelview);
	program->setUniform2f("texCoordDispl", textDispl.x, textDispl.y);

	glEnable(GL_TEXTURE_2D);
	spriteSheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);

	hpSprite->render(false);
	attackSprite->render(false);
	spinSprite->render(false);
	specialSprite->render(false);
}

void UI::update(int deltaTime, glm::vec2 camPos)
{
	// Follow Cam Static UI
	vector<float> updatedVertices = vertices;
	posDispl = glm::vec2(camPos.x - (winSize.x / 2.f), 0);
	textDispl = glm::vec2(0, 0);

	// Follow Cam Animated UI
	hpSprite->update(deltaTime);
	attackSprite->update(deltaTime);
	spinSprite->update(deltaTime);
	specialSprite->update(deltaTime);

	hpSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	attackSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	spinSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	specialSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));

	// Update cooldowns
	if (attackCooldownTimer > 0) attackCooldownTimer -= (deltaTime / 1000.f);
	else if (attackSprite->animation() != WHITE) attackSprite->changeAnimation(WHITE);

	if (spinCooldownTimer > 0) spinCooldownTimer -= (deltaTime / 1000.f);
	else if (spinSprite->animation() != WHITE) spinSprite->changeAnimation(WHITE);

	if (specialCooldownTimer > 0) specialCooldownTimer -= (deltaTime / 1000.f);
	else if (specialSprite->animation() != WHITE) specialSprite->changeAnimation(WHITE);
}

bool UI::canAttack()
{
	if (attackCooldownTimer <= 0)
	{
		attackCooldownTimer = attackCooldown;
		attackSprite->changeAnimation(COOLDOWN);
		return true;
	}
	return false;
}

bool UI::canSpin()
{
	if (spinCooldownTimer <= 0)
	{
		spinCooldownTimer = spinCooldown;
		spinSprite->changeAnimation(COOLDOWN);
		return true;
	}
	return false;
}

bool UI::canSpecial()
{
	if (specialCooldownTimer <= 0)
	{
		specialCooldownTimer = specialCooldown;
		specialSprite->changeAnimation(COOLDOWN);
		return true;
	}
	return false;
}

void UI::changeHP(int hp)
{
	if (hp < 0) hp = 0;
	if (hp > 3) hp = 3;
	if (hpSprite->animation() != hp) hpSprite->changeAnimation(hp);
}
