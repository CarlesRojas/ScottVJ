#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	keepPlaying = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	return keepPlaying;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		keepPlaying = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mousePos = glm::vec2(x, y);
}

void Game::mousePress(int button)
{
	if (button < 7 && button >= 0)
		mouseKeys[button] = true;
}

void Game::mouseRelease(int button)
{
	if (button < 7 && button >= 0)
		mouseKeys[button] = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getMouseKey(int key) const
{
	if (key >= 0 && key < 7)
		return mouseKeys[key];
	else return false;
}

glm::vec2 Game::getMousePos() const
{
	return mousePos;
}

void Game::setKey(int key, bool set)
{
	keys[key] = set;
}

void Game::setSpecialKey(int key, bool set)
{
	specialKeys[key] = set;
}

void Game::setMouseKey(int key, bool set)
{
	if (key >= 0 && key < 7)
		mouseKeys[key] = set;
}





