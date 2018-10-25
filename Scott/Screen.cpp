#include "Screen.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>



Screen::Screen()
{
	difficulty = NULL;
	message = NULL;
	screen = NULL;
	program = NULL;
}

Screen::~Screen()
{
	if (difficulty != NULL) delete difficulty;
	if (message != NULL) delete message;
	if (screen != NULL) delete screen;
	if (program != NULL) delete program;
}

Screen *Screen::createScreen(int id, const glm::vec2 windowSize, ShaderProgram * program)
{
	Screen *s = new Screen(id, windowSize, program);
	return s;
}

Screen::Screen(int id, const glm::vec2 windowSize, ShaderProgram * program)
{
	this->id = id; 
	this->program = program;
	scaleFactor = (float)windowSize.y / 540.f;

	glm::vec2 texSize = glm::vec2(1.f / 7.f, 1.f / 7.f);

	screen = Sprite::createSprite(false, glm::vec2(960.f * scaleFactor, 540.f * scaleFactor), texSize, &Load::instance().screens, program);
	screen->setNumberAnimations(9);

	screen->setAnimationSpeed(S_MAIN, 8);
	screen->addKeyframe(S_MAIN, glm::vec2(0 * texSize.x, 0 * texSize.y));

	screen->setAnimationSpeed(S_TRIA_SCOTT, 8);
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(1 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(2 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(3 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(4 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(5 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(6 * texSize.x, 0 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(0 * texSize.x, 1 * texSize.y));
	screen->addKeyframe(S_TRIA_SCOTT, glm::vec2(1 * texSize.x, 1 * texSize.y));

	screen->setAnimationSpeed(S_TRIA_RAMONA, 8);
	screen->addKeyframe(S_TRIA_RAMONA, glm::vec2(2 * texSize.x, 1 * texSize.y));
	screen->addKeyframe(S_TRIA_RAMONA, glm::vec2(3 * texSize.x, 1 * texSize.y));
	screen->addKeyframe(S_TRIA_RAMONA, glm::vec2(4 * texSize.x, 1 * texSize.y));
	screen->addKeyframe(S_TRIA_RAMONA, glm::vec2(5 * texSize.x, 1 * texSize.y));

	screen->setAnimationSpeed(S_TRIA_KIM, 8);
	screen->addKeyframe(S_TRIA_KIM, glm::vec2(6 * texSize.x, 1 * texSize.y));
	screen->addKeyframe(S_TRIA_KIM, glm::vec2(0 * texSize.x, 2 * texSize.y));
	screen->addKeyframe(S_TRIA_KIM, glm::vec2(1 * texSize.x, 2 * texSize.y));
	screen->addKeyframe(S_TRIA_KIM, glm::vec2(2 * texSize.x, 2 * texSize.y));

	screen->setAnimationSpeed(S_GO_SCOTT, 8);
	screen->addKeyframe(S_GO_SCOTT, glm::vec2(3 * texSize.x, 2 * texSize.y));
	screen->addKeyframe(S_GO_SCOTT, glm::vec2(4 * texSize.x, 2 * texSize.y));
	screen->addKeyframe(S_GO_SCOTT, glm::vec2(5 * texSize.x, 2 * texSize.y));
	screen->addKeyframe(S_GO_SCOTT, glm::vec2(6 * texSize.x, 2 * texSize.y));

	screen->setAnimationSpeed(S_GO_KIM, 8);
	screen->addKeyframe(S_GO_KIM, glm::vec2(0 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_KIM, glm::vec2(1 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_KIM, glm::vec2(2 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_KIM, glm::vec2(3 * texSize.x, 3 * texSize.y));

	screen->setAnimationSpeed(S_GO_RAMONA, 8);
	screen->addKeyframe(S_GO_RAMONA, glm::vec2(4 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_RAMONA, glm::vec2(5 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_RAMONA, glm::vec2(6 * texSize.x, 3 * texSize.y));
	screen->addKeyframe(S_GO_RAMONA, glm::vec2(0 * texSize.x, 4 * texSize.y));

	screen->setAnimationSpeed(S_THEEND, 8);
	screen->addKeyframe(S_THEEND, glm::vec2(1 * texSize.x, 4 * texSize.y));
	screen->addKeyframe(S_THEEND, glm::vec2(2 * texSize.x, 4 * texSize.y));
	screen->addKeyframe(S_THEEND, glm::vec2(3 * texSize.x, 4 * texSize.y));
	screen->addKeyframe(S_THEEND, glm::vec2(4 * texSize.x, 4 * texSize.y));
	screen->addKeyframe(S_THEEND, glm::vec2(5 * texSize.x, 4 * texSize.y));

	screen->setAnimationSpeed(S_NONE, 8);
	screen->addKeyframe(S_NONE, glm::vec2(6 * texSize.x, 6 * texSize.y));
	
	screen->changeAnimation(S_NONE);
	screen->setPosition(glm::vec2(0.f));
	
	// Message
	message = Sprite::createSprite(false, glm::vec2(960.f * scaleFactor, 540.f * scaleFactor), texSize, &Load::instance().screens, program);
	message->setNumberAnimations(4);

	message->setAnimationSpeed(M_START, 2);
	message->addKeyframe(M_START, glm::vec2(6 * texSize.x, 4 * texSize.y));
	message->addKeyframe(M_START, glm::vec2(6 * texSize.x, 5 * texSize.y));

	message->setAnimationSpeed(M_PLAY, 2);
	message->addKeyframe(M_PLAY, glm::vec2(0 * texSize.x, 5 * texSize.y));
	message->addKeyframe(M_PLAY, glm::vec2(0 * texSize.x, 6 * texSize.y));
	
	message->setAnimationSpeed(M_MENU, 2);
	message->addKeyframe(M_MENU, glm::vec2(1 * texSize.x, 5 * texSize.y));
	message->addKeyframe(M_MENU, glm::vec2(1 * texSize.x, 6 * texSize.y));
	
	message->setAnimationSpeed(M_NONE, 2);
	message->addKeyframe(M_NONE, glm::vec2(6 * texSize.x, 6 * texSize.y));

	message->changeAnimation(M_NONE);
	message->setPosition(glm::vec2(0.f));

	// Difficulty
	difficulty = Sprite::createSprite(false, glm::vec2(960.f * scaleFactor, 540.f * scaleFactor), texSize, &Load::instance().screens, program);
	difficulty->setNumberAnimations(4);

	difficulty->setAnimationSpeed(D_EASY, 8);
	difficulty->addKeyframe(D_EASY, glm::vec2(2 * texSize.x, 5 * texSize.y));

	difficulty->setAnimationSpeed(D_MEDIUM, 8);
	difficulty->addKeyframe(D_MEDIUM, glm::vec2(3 * texSize.x, 5 * texSize.y));

	difficulty->setAnimationSpeed(D_HARD, 8);
	difficulty->addKeyframe(D_HARD, glm::vec2(4 * texSize.x, 5 * texSize.y));
	
	difficulty->setAnimationSpeed(D_NONE, 8);
	difficulty->addKeyframe(D_NONE, glm::vec2(6 * texSize.x, 6 * texSize.y));

	difficulty->changeAnimation(D_NONE);
	difficulty->setPosition(glm::vec2(0.f));
}

void Screen::update(int deltaTime)
{
	float dt = deltaTime / 1000.f;

	screen->update(deltaTime);
	screen->setPosition(glm::vec2(0.f));

	message->update(deltaTime);
	message->setPosition(glm::vec2(0.f));

	difficulty->update(deltaTime);
	difficulty->setPosition(glm::vec2(0.f));
}

void Screen::render()
{
	screen->render(false);
	difficulty->render(false);
	message->render(false);
}