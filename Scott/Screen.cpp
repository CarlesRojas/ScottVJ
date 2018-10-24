#include "Screen.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>


Screen * Screen::createScreen(int id, const glm::vec2 windowSize, ShaderProgram * program)
{
	Screen *s = new Screen(id, windowSize, program);
	return s;
}

Screen::Screen(int id, const glm::vec2 windowSize, ShaderProgram * program)
{
	this->id = id;

	texture.loadFromFile("sprites/screens/screens_1920x1080.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texture.setWrapS(GL_CLAMP_TO_EDGE);
	texture.setWrapT(GL_CLAMP_TO_EDGE);
	texture.setMinFilter(GL_NEAREST);
	texture.setMagFilter(GL_NEAREST);
	scaleFactor = (float)windowSize.y / 1080.f;
	glm::vec2 texSize = glm::vec2(1.f / 8.f, 1.f / 6.f);

	sprite = Sprite::createSprite(true, glm::vec2(1920.f * scaleFactor, 1080.f * scaleFactor), texSize, &texture, program);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(S_MAIN, 8);
	sprite->addKeyframe(S_MAIN, glm::vec2(0 * texSize.x, 0 * texSize.y));

	sprite->setAnimationSpeed(S_TRIA_SCOTT, 8);
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(0 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(1 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(2 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(3 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(4 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(5 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(6 * texSize.x, 1 * texSize.y));
	sprite->addKeyframe(S_TRIA_SCOTT, glm::vec2(7 * texSize.x, 1 * texSize.y));

	sprite->setAnimationSpeed(S_TRIA_RAMONA, 8);
	sprite->addKeyframe(S_TRIA_RAMONA, glm::vec2(0 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_RAMONA, glm::vec2(1 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_RAMONA, glm::vec2(2 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_RAMONA, glm::vec2(3 * texSize.x, 2 * texSize.y));

	sprite->setAnimationSpeed(S_TRIA_KIM, 8);
	sprite->addKeyframe(S_TRIA_KIM, glm::vec2(4 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_KIM, glm::vec2(5 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_KIM, glm::vec2(6 * texSize.x, 2 * texSize.y));
	sprite->addKeyframe(S_TRIA_KIM, glm::vec2(7 * texSize.x, 2 * texSize.y));

	sprite->setAnimationSpeed(S_GO_SCOTT, 8);
	sprite->addKeyframe(S_GO_SCOTT, glm::vec2(0 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_SCOTT, glm::vec2(1 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_SCOTT, glm::vec2(2 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_SCOTT, glm::vec2(3 * texSize.x, 3 * texSize.y));

	sprite->setAnimationSpeed(S_GO_RAMONA, 8);
	sprite->addKeyframe(S_GO_RAMONA, glm::vec2(0 * texSize.x, 4 * texSize.y));
	sprite->addKeyframe(S_GO_RAMONA, glm::vec2(1 * texSize.x, 4 * texSize.y));
	sprite->addKeyframe(S_GO_RAMONA, glm::vec2(2 * texSize.x, 4 * texSize.y));
	sprite->addKeyframe(S_GO_RAMONA, glm::vec2(3 * texSize.x, 4 * texSize.y));

	sprite->setAnimationSpeed(S_GO_KIM, 8);
	sprite->addKeyframe(S_GO_KIM, glm::vec2(4 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_KIM, glm::vec2(5 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_KIM, glm::vec2(6 * texSize.x, 3 * texSize.y));
	sprite->addKeyframe(S_GO_KIM, glm::vec2(7 * texSize.x, 3 * texSize.y));

	sprite->setAnimationSpeed(S_THEEND, 8);
	sprite->addKeyframe(S_THEEND, glm::vec2(0 * texSize.x, 5 * texSize.y));
	sprite->addKeyframe(S_THEEND, glm::vec2(1 * texSize.x, 5 * texSize.y));
	sprite->addKeyframe(S_THEEND, glm::vec2(2 * texSize.x, 5 * texSize.y));
	sprite->addKeyframe(S_THEEND, glm::vec2(3 * texSize.x, 5 * texSize.y));
	sprite->addKeyframe(S_THEEND, glm::vec2(4 * texSize.x, 5 * texSize.y));

	switch (id)
	{
	case 0:
		sprite->changeAnimation(S_MAIN);
		break;
	case 1:
		sprite->changeAnimation(S_TRIA_SCOTT);
		break;
	case 2:
		sprite->changeAnimation(S_THEEND);
		break;
	case 3:
		sprite->changeAnimation(S_GO_SCOTT);
		break;
	default:
		break;
	}

	sprite->changeAnimation(S_MAIN);
	sprite->setPosition(glm::vec2(0.f, 0.f));
	Game::instance().projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void Screen::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (id == 1) {
		if (Game::instance().getKey('d'))
		{
			if (sprite->animation() == S_TRIA_SCOTT)
				sprite->changeAnimation(S_TRIA_RAMONA);
			else if (sprite->animation() == S_TRIA_RAMONA)
				sprite->changeAnimation(S_TRIA_KIM);
			else if (sprite->animation() == S_TRIA_KIM)
				sprite->changeAnimation(S_TRIA_SCOTT);
		}
		if (Game::instance().getKey('a'))
		{
			if (sprite->animation() == S_TRIA_SCOTT)
				sprite->changeAnimation(S_TRIA_KIM);
			else if (sprite->animation() == S_TRIA_KIM)
				sprite->changeAnimation(S_TRIA_RAMONA);
			else if (sprite->animation() == S_TRIA_RAMONA)
				sprite->changeAnimation(S_TRIA_SCOTT);
		}
	}
	Game::instance().projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void Screen::render()
{
	sprite->render(false);
}
