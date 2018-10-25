#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"


Level::Level()
{
	program = NULL;
	physics = NULL;
	background = NULL;
	cam = NULL;
	ui = NULL;
	player = NULL;
	enemies.clear();
}

Level::~Level()
{
	if (program != NULL) delete program;
	if (physics != NULL) delete physics;
	if (background != NULL) delete background;
	if (cam != NULL) delete cam;
	if (ui != NULL) delete ui;
	if (player != NULL) delete player;
	for (int i = 0; i < enemies.size(); i++) {
		Enemy* p = enemies[i];
		delete p;
	}
	enemies.clear();
}

Level * Level::createLevel(int character, int difficulty, int lvl, ShaderProgram * program)
{
	Level *l = new Level(character, difficulty, lvl, program);
	return l;
}

Level::Level(int character, int difficulty, int lvl, ShaderProgram * program)
{
	this->program = program;
	this->lvl = lvl;
	this->difficulty = difficulty;
	this->character = character;

	// Physics
	Physics::instance().init(program);

	// Background
	background = Background::createBackground(lvl, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), program);
	Physics::instance().background = background;

	// Cam & UI
	cam = Camera::createCamera(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), background->getSize());
	ui = UI::createUI(character, 0.5f, 5.f, 10.f, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), program);
	Game::instance().projection = cam->getProjectionMatrix();

	// Player
	player = Player::createPlayer(character, glm::vec2(SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), ui, SCREEN_HEIGHT, program);
	Physics::instance().player = player;

	// Enemies
	enemies.push_back(Enemy::createEnemy(0, glm::vec2(3.0f * SCREEN_WIDTH / 4, 3.5f * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, program));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);

	enemies.push_back(Enemy::createEnemy(0, glm::vec2(2.5f * SCREEN_WIDTH / 4, 3.f * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, program));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);

	enemies.push_back(Enemy::createEnemy(1, glm::vec2(7.f * SCREEN_WIDTH / 4, 2.5f * SCREEN_HEIGHT / 4), SCREEN_HEIGHT, program));
	Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
}

void Level::update(int deltaTime)
{
	// Entities
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

	// Camera
	cam->update(deltaTime, player->pos);
	Game::instance().projection = cam->getProjectionMatrix();

	// UI & Background
	ui->update(deltaTime, cam->getPos());
	background->update(deltaTime, cam->getPos());

	// End level if player has no hit poits left
	if (player->hp <= 0) gameOver();

	// Debug
	if (Game::instance().getKey('v')) theEnd();
}

void Level::render()
{
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

void Level::gameOver()
{
	Game::instance().gameOver = true;
}

void Level::theEnd() 
{
	Game::instance().theEnd = true;
}

