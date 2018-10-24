#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>


void Game::init()
{
	keepPlaying = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	currentTime = 0.0f;
	initShaders();
	//level.init(&program);
	//state = Game::MAIN;
	screen = Screen::createScreen(0, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), &program);
}

bool Game::update(int deltaTime)
{
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime += deltaTime;
	/*
	switch (state)
	{
	case Game::MAIN:
		if (Game::instance().getKey(' ')) state = CHOOSE;

		break;
	case Game::CHOOSE:
		if (Game::instance().getKey(' ')) state = LVL1;

		break;
	case Game::LVL1:
		true;
		break;
	case Game::LVL2:
		true;
		break;
	case Game::LVL3:
		true;
		break;
	case Game::GAMEOVER:
		if (Game::instance().getKey(' ')) state = MAIN;
		break;
	case Game::THEEND:
		if (Game::instance().getKey(' ')) state = MAIN;
		break;
	default:

		true;
		break;
	}
	*/
	//level.update(deltaTime);
	screen->update(deltaTime);

	return keepPlaying;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 modelview;
	program.use();
	program.setUniformMatrix4f("projection", projection);
	program.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	program.setUniformMatrix4f("modelview", modelview);
	program.setUniform2f("texCoordDispl", 0.f, 0.f);

	//level.render();
	screen->render();
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

void Game::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if (!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}





