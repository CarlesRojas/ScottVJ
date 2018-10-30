#include "UI.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Load.h"

UI::UI()
{
	hpSprite = NULL;
	attackSprite = NULL;
	spinSprite = NULL;
	specialSprite = NULL;
	bossSprite = NULL;
	playerSprite = NULL;
	bgSprite = NULL;
}

UI::~UI()
{
	if (hpSprite != NULL) delete hpSprite;
	if (attackSprite != NULL) delete attackSprite;
	if (spinSprite != NULL) delete spinSprite;
	if (specialSprite != NULL) delete specialSprite;
	if (bossSprite != NULL) delete bossSprite;
	if (playerSprite != NULL) delete playerSprite;
	if (bgSprite != NULL) delete bgSprite;
}

UI * UI::createUI(int playerCharacter, int boss, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program)
{
	UI *ui = new UI(playerCharacter, boss, attackCD, spinCD, specialCD, windowSize, program);
	return ui;
}

UI::UI(int playerCharacter, int boss, float attackCD, float spinCD, float specialCD, const glm::vec2 windowSize, ShaderProgram * program)
{
	float scaleFactor = windowSize.y / 256.f;
	this->program = program;
	this->player = playerCharacter;
	this->boss = boss;
	this->showingBossIntro = false;

	attackCooldown = attackCD;
	spinCooldown = spinCD;
	specialCooldown = specialCD;

	attackCooldownTimer = 0;
	spinCooldownTimer = 0;
	specialCooldownTimer = 0;

	bossDispl = glm::vec2(0.f, windowSize.y / 5.5f);
	winSize = windowSize;
	tileTexSize = glm::vec2(1.f / 20.f, 1.f / 10.f);

	glm::vec2 texCoordTile[2];
	texCoordTile[0] = glm::vec2(player * tileTexSize.x, 5 * tileTexSize.y);
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
	hpSprite = Sprite::createSprite(false, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05f, 0.1f), &Load::instance().ui, program);
	hpSprite->setNumberAnimations(4);

	hpSprite->setAnimationSpeed(0, 1);
	hpSprite->addKeyframe(0, glm::vec2(3 * 0.05f, 5 * 0.1f));
	hpSprite->setAnimationSpeed(1, 1);
	hpSprite->addKeyframe(1, glm::vec2(4 * 0.05f, 5 * 0.1f));
	hpSprite->setAnimationSpeed(2, 1);
	hpSprite->addKeyframe(2, glm::vec2(5 * 0.05f, 5 * 0.1f));
	hpSprite->setAnimationSpeed(3, 1);
	hpSprite->addKeyframe(3, glm::vec2(6 * 0.05f, 5 * 0.1f));
	hpSprite->changeAnimation(3);
	hpSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Attack
	attackSprite = Sprite::createSprite(false, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05f, 0.1f), &Load::instance().ui, program);
	attackSprite->setNumberAnimations(2);

	attackSprite->setAnimationSpeed(WHITE, 1);
	attackSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, 0 * 0.1f));

	attackSprite->setAnimationSpeed(COOLDOWN, 16.f / attackCooldown);
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, 0 * 0.1f));
	attackSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, 0 * 0.1f));
	attackSprite->changeAnimation(WHITE);
	attackSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Spin
	spinSprite = Sprite::createSprite(false, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05f, 0.1f), &Load::instance().ui, program);
	spinSprite->setNumberAnimations(2);

	spinSprite->setAnimationSpeed(WHITE, 1);
	spinSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, 1 * 0.1f));

	spinSprite->setAnimationSpeed(COOLDOWN, 16.f / spinCooldown);
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, 1 * 0.1f));
	spinSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, 1 * 0.1f));
	spinSprite->changeAnimation(WHITE);
	spinSprite->setPosition(glm::vec2(0.f, 0.f));

	// Animatied UI - Special
	specialSprite = Sprite::createSprite(false, glm::vec2(256.f * scaleFactor, 256.f * scaleFactor), glm::vec2(0.05f, 0.1f), &Load::instance().ui, program);
	specialSprite->setNumberAnimations(2);

	specialSprite->setAnimationSpeed(WHITE, 1);
	specialSprite->addKeyframe(WHITE, glm::vec2(0 * 0.05f, (2 + player) * 0.1f));

	specialSprite->setAnimationSpeed(COOLDOWN, 16.f / specialCooldown);
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(1 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(2 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(3 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(4 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(5 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(6 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(7 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(8 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(9 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(10 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(11 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(12 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(13 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(14 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(15 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(16 * 0.05f, (2 + player) * 0.1f));
	specialSprite->addKeyframe(COOLDOWN, glm::vec2(17 * 0.05f, (2 + player) * 0.1f));
	specialSprite->changeAnimation(WHITE);
	specialSprite->setPosition(glm::vec2(0.f, 0.f));

	// BossSprite
	scaleFactor = (float)windowSize.x / 670.f;
	glm::vec2 bossTexSize = glm::vec2(1.f / 8.f, 1.f / 9.f);
	bossSprite = Sprite::createSprite(false, glm::vec2(670.f * scaleFactor, 110.f * scaleFactor), bossTexSize, &Load::instance().boss, program);
	bossSprite->setNumberAnimations(10);

	bossSprite->setAnimationSpeed(ROXANNE, 16);
	bossSprite->addKeyframe(ROXANNE, glm::vec2(7 * bossTexSize.x, 3 * bossTexSize.y));

	bossSprite->setAnimationSpeed(ROXANNE_SHOW, 16);
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(0 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(1 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(2 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(3 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(4 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(5 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(6 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_SHOW, glm::vec2(7 * bossTexSize.x, 3 * bossTexSize.y));
	
	bossSprite->setAnimationSpeed(ROXANNE_HIDE, 16);
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(7 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(6 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(5 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(4 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(3 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(2 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(1 * bossTexSize.x, 3 * bossTexSize.y));
	bossSprite->addKeyframe(ROXANNE_HIDE, glm::vec2(0 * bossTexSize.x, 3 * bossTexSize.y));
	
	bossSprite->setAnimationSpeed(TODD, 16);
	bossSprite->addKeyframe(TODD, glm::vec2(7 * bossTexSize.x, 5 * bossTexSize.y));

	bossSprite->setAnimationSpeed(TODD_SHOW, 16);
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(0 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(1 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(2 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(3 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(4 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(5 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(6 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_SHOW, glm::vec2(7 * bossTexSize.x, 5 * bossTexSize.y));

	bossSprite->setAnimationSpeed(TODD_HIDE, 16);
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(7 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(6 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(5 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(4 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(3 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(2 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(1 * bossTexSize.x, 5 * bossTexSize.y));
	bossSprite->addKeyframe(TODD_HIDE, glm::vec2(0 * bossTexSize.x, 5 * bossTexSize.y));

	bossSprite->setAnimationSpeed(ROBOT, 16);
	bossSprite->addKeyframe(ROBOT, glm::vec2(7 * bossTexSize.x, 4 * bossTexSize.y));

	bossSprite->setAnimationSpeed(ROBOT_SHOW, 16);
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(0 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(1 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(2 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(3 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(4 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(5 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(6 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_SHOW, glm::vec2(7 * bossTexSize.x, 4 * bossTexSize.y));

	bossSprite->setAnimationSpeed(ROBOT_HIDE, 16);
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(7 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(6 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(5 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(4 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(3 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(2 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(1 * bossTexSize.x, 4 * bossTexSize.y));
	bossSprite->addKeyframe(ROBOT_HIDE, glm::vec2(0 * bossTexSize.x, 4 * bossTexSize.y));
	
	bossSprite->setAnimationSpeed(B_NONE, 16);
	bossSprite->addKeyframe(B_NONE, glm::vec2(0 * bossTexSize.x, 8 * bossTexSize.y));

	bossSprite->changeAnimation(B_NONE);
	bossSprite->setPosition(bossDispl);

	// PlayerSprite
	playerSprite = Sprite::createSprite(false, glm::vec2(670.f * scaleFactor, 110.f * scaleFactor), bossTexSize, &Load::instance().boss, program);
	playerSprite->setNumberAnimations(10);

	playerSprite->setAnimationSpeed(SCOTT, 16);
	playerSprite->addKeyframe(SCOTT, glm::vec2(7 * bossTexSize.x, 0 * bossTexSize.y));

	playerSprite->setAnimationSpeed(SCOTT_SHOW, 16);
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(0 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(1 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(2 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(3 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(4 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(5 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(6 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_SHOW, glm::vec2(7 * bossTexSize.x, 0 * bossTexSize.y));

	playerSprite->setAnimationSpeed(SCOTT_HIDE, 16);
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(7 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(6 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(5 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(4 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(3 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(2 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(1 * bossTexSize.x, 0 * bossTexSize.y));
	playerSprite->addKeyframe(SCOTT_HIDE, glm::vec2(0 * bossTexSize.x, 0 * bossTexSize.y));

	playerSprite->setAnimationSpeed(RAMONA, 16);
	playerSprite->addKeyframe(RAMONA, glm::vec2(7 * bossTexSize.x, 1 * bossTexSize.y));

	playerSprite->setAnimationSpeed(RAMONA_SHOW, 16);
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(0 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(1 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(2 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(3 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(4 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(5 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(6 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_SHOW, glm::vec2(7 * bossTexSize.x, 1 * bossTexSize.y));

	playerSprite->setAnimationSpeed(RAMONA_HIDE, 16);
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(7 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(6 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(5 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(4 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(3 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(2 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(1 * bossTexSize.x, 1 * bossTexSize.y));
	playerSprite->addKeyframe(RAMONA_HIDE, glm::vec2(0 * bossTexSize.x, 1 * bossTexSize.y));

	playerSprite->setAnimationSpeed(KIM, 16);
	playerSprite->addKeyframe(KIM, glm::vec2(7 * bossTexSize.x, 2 * bossTexSize.y));

	playerSprite->setAnimationSpeed(KIM_SHOW, 16);
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(0 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(1 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(2 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(3 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(4 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(5 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(6 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_SHOW, glm::vec2(7 * bossTexSize.x, 2 * bossTexSize.y));

	playerSprite->setAnimationSpeed(KIM_HIDE, 16);
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(7 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(6 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(5 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(4 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(3 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(2 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(1 * bossTexSize.x, 2 * bossTexSize.y));
	playerSprite->addKeyframe(KIM_HIDE, glm::vec2(0 * bossTexSize.x, 2 * bossTexSize.y));

	playerSprite->setAnimationSpeed(P_NONE, 16);
	playerSprite->addKeyframe(P_NONE, glm::vec2(0 * bossTexSize.x, 8 * bossTexSize.y));

	playerSprite->changeAnimation(P_NONE);
	playerSprite->setPosition(bossDispl);

	// BGSprite
	bgSprite = Sprite::createSprite(false, glm::vec2(670.f * scaleFactor, 110.f * scaleFactor), bossTexSize, &Load::instance().boss, program);
	bgSprite->setNumberAnimations(4);

	bgSprite->setAnimationSpeed(BG_NONE, 16);
	bgSprite->addKeyframe(BG_NONE, glm::vec2(0 * bossTexSize.x, 8 * bossTexSize.y));

	bgSprite->setAnimationSpeed(SHOW, 16);
	bgSprite->addKeyframe(SHOW, glm::vec2(0 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(1 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(2 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(3 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(4 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(5 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(6 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(SHOW, glm::vec2(7 * bossTexSize.x, 6 * bossTexSize.y));

	bgSprite->setAnimationSpeed(HIDE, 16);
	bgSprite->addKeyframe(HIDE, glm::vec2(7 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(6 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(5 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(4 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(3 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(2 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(1 * bossTexSize.x, 6 * bossTexSize.y));
	bgSprite->addKeyframe(HIDE, glm::vec2(0 * bossTexSize.x, 6 * bossTexSize.y));
	
	bgSprite->setAnimationSpeed(LOOP, 16);
	bgSprite->addKeyframe(LOOP, glm::vec2(0 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(1 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(2 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(3 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(4 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(5 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(6 * bossTexSize.x, 7 * bossTexSize.y));
	bgSprite->addKeyframe(LOOP, glm::vec2(7 * bossTexSize.x, 7 * bossTexSize.y));

	bgSprite->changeAnimation(BG_NONE);
	bgSprite->setPosition(bossDispl);
}

void UI::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(posDispl.x, posDispl.y, 0.f));
	program->setUniformMatrix4f("modelview", modelview);
	program->setUniform2f("texCoordDispl", textDispl.x, textDispl.y);

	glEnable(GL_TEXTURE_2D);
	Load::instance().ui.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);

	hpSprite->render(false);
	attackSprite->render(false);
	spinSprite->render(false);
	specialSprite->render(false);
	bgSprite->render(false);
	bossSprite->render(false);
	playerSprite->render(false);
}

void UI::update(int deltaTime, glm::vec2 camPos)
{
	float dt = deltaTime / 1000.f;

	// Follow Cam Static UI
	vector<float> updatedVertices = vertices;
	posDispl = glm::vec2(camPos.x - (winSize.x / 2.f), 0);
	textDispl = glm::vec2(0, 0);

	// Follow Cam Animated UI
	hpSprite->update(deltaTime);
	attackSprite->update(deltaTime);
	spinSprite->update(deltaTime);
	specialSprite->update(deltaTime);
	bgSprite->update(deltaTime);
	bossSprite->update(deltaTime);
	playerSprite->update(deltaTime);

	hpSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	attackSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	spinSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	specialSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f));
	bgSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f) + bossDispl);
	bossSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f) + bossDispl);
	playerSprite->setPosition(glm::vec2(camPos.x - (winSize.x / 2.f), 0.f) + bossDispl);

	// Update cooldowns
	if (attackCooldownTimer > 0) attackCooldownTimer -= dt;
	else if (attackSprite->animation() != WHITE) attackSprite->changeAnimation(WHITE);

	if (spinCooldownTimer > 0) spinCooldownTimer -= dt;
	else if (spinSprite->animation() != WHITE) spinSprite->changeAnimation(WHITE);

	if (specialCooldownTimer > 0) specialCooldownTimer -= dt;
	else if (specialSprite->animation() != WHITE) specialSprite->changeAnimation(WHITE);

	// Boss intro
	if (introDelay > 0) introDelay -= dt;
	if (showingBossIntro) 
	{
		if (introStage == 0 && introDelay < 0)
		{
			if (bgSprite->animation() != SHOW) bgSprite->changeAnimation(SHOW);
			if (bossSprite->animation() != B_NONE) bossSprite->changeAnimation(B_NONE);
			if (playerSprite->animation() != P_NONE) playerSprite->changeAnimation(P_NONE);
			introDelay = 7.5f / 16.f;
			introStage = 1;
		}
		else if (introStage == 1 && introDelay < 0)
		{
			if (bgSprite->animation() != LOOP) bgSprite->changeAnimation(LOOP);

			if (boss == 0 && bossSprite->animation() != ROXANNE_SHOW) bossSprite->changeAnimation(ROXANNE_SHOW);
			else if (boss == 1 && bossSprite->animation() != ROBOT_SHOW) bossSprite->changeAnimation(ROBOT_SHOW);
			else if (boss == 2 && bossSprite->animation() != TODD_SHOW) bossSprite->changeAnimation(TODD_SHOW);

			if (player == 0 && playerSprite->animation() != SCOTT_SHOW) playerSprite->changeAnimation(SCOTT_SHOW);
			else if (player == 1 && playerSprite->animation() != RAMONA_SHOW) playerSprite->changeAnimation(RAMONA_SHOW);
			else if (player == 2 && playerSprite->animation() != KIM_SHOW) playerSprite->changeAnimation(KIM_SHOW);

			introDelay = 7.5f / 16.f;
			introStage = 2;
		}
		else if(introStage == 2 && introDelay < 0)
		{

			if (bgSprite->animation() != LOOP) bgSprite->changeAnimation(LOOP);

			if (boss == 0 && bossSprite->animation() != ROXANNE) bossSprite->changeAnimation(ROXANNE);
			else if (boss == 1 && bossSprite->animation() != ROBOT) bossSprite->changeAnimation(ROBOT);
			else if (boss == 2 && bossSprite->animation() != TODD) bossSprite->changeAnimation(TODD);

			if (player == 0 && playerSprite->animation() != SCOTT) playerSprite->changeAnimation(SCOTT);
			else if (player == 1 && playerSprite->animation() != RAMONA) playerSprite->changeAnimation(RAMONA);
			else if (player == 2 && playerSprite->animation() != KIM) playerSprite->changeAnimation(KIM);

			introDelay = 2.f;
			introStage = 3;
		}
		else if (introStage == 3 && introDelay < 0)
		{
			if (bgSprite->animation() != LOOP) bgSprite->changeAnimation(LOOP);

			if (boss == 0 && bossSprite->animation() != ROXANNE_HIDE) bossSprite->changeAnimation(ROXANNE_HIDE);
			else if (boss == 1 && bossSprite->animation() != ROBOT_HIDE) bossSprite->changeAnimation(ROBOT_HIDE);
			else if (boss == 2 && bossSprite->animation() != TODD_HIDE) bossSprite->changeAnimation(TODD_HIDE);

			if (player == 0 && playerSprite->animation() != SCOTT_HIDE) playerSprite->changeAnimation(SCOTT_HIDE);
			else if (player == 1 && playerSprite->animation() != RAMONA_HIDE) playerSprite->changeAnimation(RAMONA_HIDE);
			else if (player == 2 && playerSprite->animation() != KIM_HIDE) playerSprite->changeAnimation(KIM_HIDE);

			introDelay = 7.5f / 16.f;
			introStage = 4;
		}
		else if (introStage == 4 && introDelay < 0)
		{
			if (bgSprite->animation() != HIDE) bgSprite->changeAnimation(HIDE);
			if (bossSprite->animation() != B_NONE) bossSprite->changeAnimation(B_NONE);
			if (playerSprite->animation() != P_NONE) playerSprite->changeAnimation(P_NONE);

			introDelay = 7.5f / 16.f;
			introStage = 5;
		}
		else if (introStage == 5 && introDelay < 0)
		{
			if (bgSprite->animation() != BG_NONE) bgSprite->changeAnimation(BG_NONE);
			if (bossSprite->animation() != B_NONE) bossSprite->changeAnimation(B_NONE);
			if (playerSprite->animation() != P_NONE) playerSprite->changeAnimation(P_NONE);

			introDelay = -1.f;
			introStage = 0;
			showingBossIntro = false;
		}
	}
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

void UI::showBossIntro() 
{
	if (!showingBossIntro)
	{
		showingBossIntro = true;
		introStage = 0;
		introDelay = -1;
	}
}
