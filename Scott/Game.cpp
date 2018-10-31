#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Audio.h"
#include <glm/gtc/matrix_transform.hpp>

Game::Game()
{
	level = NULL;
	screen = NULL;
}

Game::~Game()
{
	if (level != NULL) delete level;
	if (screen != NULL) delete screen;
}

void Game::init()
{
	keepPlaying = true;
	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
	currentTime = 0.0f;
	initShaders();
	theEnd = gameOver = false;
	showOutlines = false;
	
	Load::instance().init();
	Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
	Physics::instance().init(&program);

	state = Game::MAIN;
	Audio::instance().LoadSound("audio/menu.wav",false, true);
	Audio::instance().PlaySounds("audio/menu.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
	
	Game::instance().setKey(' ', false);
	screen = Screen::createScreen(0, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), &program);
	screen->screen->changeAnimation(Screen::S_MAIN);
	screen->message->changeAnimation(Screen::M_START);
	screen->difficulty->changeAnimation(Screen::D_NONE);
}

bool Game::update(int deltaTime)
{
	if (Game::instance().getKey('t'))
	{
		Game::instance().setKey('t', false);
		showOutlines = !showOutlines;
	}

	currentTime += deltaTime;

	if ((state == LVL0 || state == LVL1 || state == LVL2) && level != NULL) 
		level->update(deltaTime);
	
	else if (state != LVL0 && state != LVL1 && state != LVL2 && screen != NULL)
	{
		screen->update(deltaTime);
		Camera::instance().update(deltaTime, glm::vec2(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));
		Game::instance().projection = Camera::instance().getProjectionMatrix();
	}

	switch (state)
	{
	case Game::MAIN:
		if (Game::instance().getKey(' '))
		{
			Audio::instance().PlaySounds("audio/menu_accept.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey(' ', false);
			screen->screen->changeAnimation(Screen::S_TRIA_SCOTT);
			screen->message->changeAnimation(Screen::M_PLAY);
			screen->difficulty->changeAnimation(Screen::D_EASY);
			state = CHOOSE;
		}

		break;
	case Game::CHOOSE:

		// Right
		if (Game::instance().getKey('d'))
		{
			Audio::instance().PlaySounds("audio/menu_change.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey('d', false);
			if (screen->screen->animation() == Screen::S_TRIA_SCOTT)
				screen->screen->changeAnimation(Screen::S_TRIA_RAMONA);
			else if (screen->screen->animation() == Screen::S_TRIA_RAMONA)
				screen->screen->changeAnimation(Screen::S_TRIA_KIM);
			else if (screen->screen->animation() == Screen::S_TRIA_KIM)
				screen->screen->changeAnimation(Screen::S_TRIA_SCOTT);
		}

		// Left
		else if (Game::instance().getKey('a'))
		{
			Audio::instance().PlaySounds("audio/menu_change.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey('a', false);
			if (screen->screen->animation() == Screen::S_TRIA_SCOTT)
				screen->screen->changeAnimation(Screen::S_TRIA_KIM);
			else if (screen->screen->animation() == Screen::S_TRIA_KIM)
				screen->screen->changeAnimation(Screen::S_TRIA_RAMONA);
			else if (screen->screen->animation() == Screen::S_TRIA_RAMONA)
				screen->screen->changeAnimation(Screen::S_TRIA_SCOTT);
		}

		// Up || Down
		else if (Game::instance().getKey('w') || Game::instance().getKey('s'))
		{
			Audio::instance().PlaySounds("audio/menu_change.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey('w', false);
			Game::instance().setKey('s', false);
			if (screen->difficulty->animation() == Screen::D_EASY)
				screen->difficulty->changeAnimation(Screen::D_HARD);
			else if (screen->difficulty->animation() == Screen::D_HARD)
				screen->difficulty->changeAnimation(Screen::D_EASY);
		}

		if (Game::instance().getKey(' '))
		{
			Audio::instance().PlaySounds("audio/menu_accept.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			
			Audio::instance().UnLoadSound("audio/victory.wav");
			Audio::instance().UnLoadSound("audio/menu.wav");
			Audio::instance().LoadSound("audio/lvl0.wav", false, true);
			Audio::instance().PlaySounds("audio/lvl0.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));

			Game::instance().setKey(' ', false);
			if (screen->screen->animation() == Screen::S_TRIA_SCOTT) player = 0;
			else if (screen->screen->animation() == Screen::S_TRIA_RAMONA) player = 1;
			else if (screen->screen->animation() == Screen::S_TRIA_KIM) player = 2;

			if (screen->difficulty->animation() == Screen::D_EASY) hardDifficulty = false;
			else if (screen->difficulty->animation() == Screen::D_HARD) hardDifficulty = true;

			screen->screen->changeAnimation(Screen::S_NONE);
			screen->message->changeAnimation(Screen::M_NONE);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = LVL0;

			Physics::instance().reset();
			level = Level::createLevel(player, hardDifficulty, 0, &program);
		}
		break;
	case Game::LVL0:
		if (theEnd) 
		{
			theEnd = gameOver = false;
			Physics::instance().reset();
			level = Level::createLevel(player, hardDifficulty, 1, &program);
			state = LVL1; 
			Audio::instance().UnLoadSound("audio/lvl0.wav");
			Audio::instance().LoadSound("audio/lvl1.wav", false, true);
			Audio::instance().PlaySounds("audio/lvl1.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		if (gameOver)
		{
			if(player == 0) screen->screen->changeAnimation(Screen::S_GO_SCOTT);
			else if (player == 1) screen->screen->changeAnimation(Screen::S_GO_RAMONA);
			else screen->screen->changeAnimation(Screen::S_GO_KIM);

			Physics::instance().reset();
			Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
			theEnd = gameOver = false;
			screen->message->changeAnimation(Screen::M_MENU);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = GAMEOVER;
			Game::instance().setKey(' ', false);
			Audio::instance().UnLoadSound("audio/lvl0.wav");
			Audio::instance().LoadSound("audio/menu.wav", false, true);
			Audio::instance().PlaySounds("audio/menu.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		break;
	case Game::LVL1:
		if (theEnd) 
		{
			theEnd = gameOver = false;
			Physics::instance().reset();
			level = Level::createLevel(player, hardDifficulty, 2, &program);
			state = LVL2;
			Audio::instance().UnLoadSound("audio/lvl1.wav");
			Audio::instance().LoadSound("audio/lvl2.wav", false, true);
			Audio::instance().PlaySounds("audio/lvl2.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		if (gameOver)
		{
			if (player == 0) screen->screen->changeAnimation(Screen::S_GO_SCOTT);
			else if (player == 1) screen->screen->changeAnimation(Screen::S_GO_RAMONA);
			else screen->screen->changeAnimation(Screen::S_GO_KIM);

			Physics::instance().reset();
			Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
			theEnd = gameOver = false;
			screen->message->changeAnimation(Screen::M_MENU);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = GAMEOVER;
			Game::instance().setKey(' ', false);
			Audio::instance().UnLoadSound("audio/lvl1.wav");
			Audio::instance().LoadSound("audio/menu.wav", false, true);
			Audio::instance().PlaySounds("audio/menu.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		break;
	case Game::LVL2:
		if (theEnd)
		{
			Physics::instance().reset();
			Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
			theEnd = gameOver = false;
			screen->screen->changeAnimation(Screen::S_THEEND);
			screen->message->changeAnimation(Screen::M_MENU);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = THEEND;
			Game::instance().setKey(' ', false);

			Audio::instance().UnLoadSound("audio/lvl2.wav");
			Audio::instance().LoadSound("audio/victory.wav", false, true);
			Audio::instance().PlaySounds("audio/victory.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		if (gameOver)
		{
			if (player == 0) screen->screen->changeAnimation(Screen::S_GO_SCOTT);
			else if (player == 1) screen->screen->changeAnimation(Screen::S_GO_RAMONA);
			else screen->screen->changeAnimation(Screen::S_GO_KIM);

			Physics::instance().reset();
			Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
			theEnd = gameOver = false;
			screen->message->changeAnimation(Screen::M_MENU);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = GAMEOVER;
			Game::instance().setKey(' ', false);
			Audio::instance().UnLoadSound("audio/lvl2.wav");
			Audio::instance().LoadSound("audio/menu.wav", false, true);
			Audio::instance().PlaySounds("audio/menu.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(0.25f));
		}
		break;
	case Game::GAMEOVER:
		if (Game::instance().getKey(' '))
		{
			Audio::instance().PlaySounds("audio/menu_accept.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey(' ', false);
			screen->screen->changeAnimation(Screen::S_MAIN);
			screen->message->changeAnimation(Screen::M_START);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = MAIN;
			Game::instance().setKey(' ', false);
		}
		break;
	case Game::THEEND:
		if (Game::instance().getKey(' '))
		{
			Audio::instance().PlaySounds("audio/menu_accept.wav", Vector3{ 0, 0, 0 }, Audio::instance().VolumeTodB(1.0f));
			Game::instance().setKey(' ', false);
			screen->screen->changeAnimation(Screen::S_MAIN);
			screen->message->changeAnimation(Screen::M_START);
			screen->difficulty->changeAnimation(Screen::D_NONE);
			state = MAIN;
			Game::instance().setKey(' ', false);
		}
		break;
	default: break;
	}
	
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

	if ((state == LVL0 || state == LVL1 || state == LVL2) && level != NULL) level->render();
	else if (state != LVL0 && state != LVL1 && state != LVL2 && screen != NULL) screen->render();
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
	{
		mouseKeys[button] = true;
	}
}

void Game::mouseRelease(int button)
{
	if (button < 7 && button >= 0) 
	{
		mouseKeys[button] = false;
	}
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





