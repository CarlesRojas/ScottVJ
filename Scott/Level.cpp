#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"


Level::Level()
{
	background = NULL;
	player = NULL;
	cam = NULL;
	ui = NULL;
	enemies.clear();
}

Level::~Level()
{
	if (background != NULL) delete background;
	if (player != NULL) delete player;
	if (cam != NULL) delete cam;
	if (ui != NULL) delete ui;
	for (auto e : enemies) delete e;
}

void Level::init()
{
	// Render
	initShaders();

	// LevelInfo
	lvl = 1;
	character = 2;

	// Physics
	Physics::instance().init(&texProgram);

	// Background
	background = Background::createBackground(lvl, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), &texProgram);
	Physics::instance().background = background;

	// Cam & UI
	cam = Camera::createCamera(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), background->getSize());
	ui = UI::createUI(character, 0.5f, 5.f, 10.f, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), &texProgram);
	projection = cam->getProjectionMatrix();
	currentTime = 0.0f;

	// Player
	player = Player::createPlayer(character, glm::vec2(SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), ui, SCREEN_HEIGHT, &texProgram);
	Physics::instance().player = player;

	// Enemies
	enemies.push_back(Enemy::createEnemy(0, glm::vec2(2.0f * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, &texProgram));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
	enemies.push_back(Enemy::createEnemy(0, glm::vec2(2.5f * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, &texProgram));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
	enemies.push_back(Enemy::createEnemy(2, glm::vec2(3.0f * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, &texProgram));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
	enemies.push_back(Enemy::createEnemy(2, glm::vec2(3.5f * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, &texProgram));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
	enemies.push_back(Enemy::createEnemy(2, glm::vec2(4.0f * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, &texProgram));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);

}

void Level::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->update(deltaTime);
		if (enemies[i]->dead)
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			Physics::instance().enemies.erase(Physics::instance().enemies.begin() + i);
		}
	}

	/*
	// Player attacks
	for (auto a : player->getAttacks())
		if (a->box->active)
			attack(a);

	// Enemy attacks
	for (auto e : enemies)
		for (auto a : e->getAttacks())
			if (a->box->active)
				attack(a);
	*/

	// Camera
	cam->update(deltaTime, player->pos);
	projection = cam->getProjectionMatrix();

	// UI & Background
	ui->update(deltaTime, cam->getPos());
	background->update(deltaTime, cam->getPos());
}

void Level::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	// Background && UI
	background->render();
	ui->render();

	// Enemies & Player in order
	vector< pair<int, int> > entities;
	entities.push_back(make_pair(player->pos.y, 0));
	int i = 1;
	for (auto e : enemies) { entities.push_back(make_pair(e->pos.y, i)); ++i; }
	sort(entities.begin(), entities.end());
	for (auto e : entities)
	{
		if (e.second == 0) player->render();
		else enemies[e.second - 1]->render();
	}

	// Render attacks always on top
	for (auto a : player->getAttacks())
		a->render();

	for (auto e : enemies)
		for (auto a : e->getAttacks())
			a->render();

	// Debug
	Physics::instance().render();

}

void Level::initShaders()
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
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}