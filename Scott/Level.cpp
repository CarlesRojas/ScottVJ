#include "Level.h"
#include "Game.h"
#include <fstream>

Level::Level()
{
	background = NULL;
	ui = NULL;
	player = NULL;
	enemies.clear();
}

Level::~Level()
{
	
	if (background != NULL) delete background;
	if (ui != NULL) delete ui;
	if (player != NULL) delete player;
	
	for (int i = 0; i < enemies.size(); i++) {
		Enemy* p = enemies[i];
		delete p;
	}
	
	enemies.clear();
}

Level * Level::createLevel(int character, bool hardDifficulty, int lvl, ShaderProgram * program)
{
	Level *l = new Level(character, hardDifficulty, lvl, program);
	return l;
}

Level::Level(int character, bool hardDifficulty, int lvl, ShaderProgram * program)
{
	this->program = program;
	this->lvl = lvl;
	this->hardDifficulty = hardDifficulty;
	this->character = character;
	float scaleFactor = SCREEN_HEIGHT / 256.f;
	
	layout = loadLevel("levels/lvl" + to_string(lvl) + ".txt", hardDifficulty);

	// Physics
	Physics::instance().init(program);

	// Background
	background = Background::createBackground(lvl, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), program);
	Physics::instance().background = background;

	// Cam & UI
	Camera::instance().init(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), background->getSize());
	ui = UI::createUI(character, lvl, 0.5f, 10.f, 10.f, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), program);
	Game::instance().projection = Camera::instance().getProjectionMatrix();

	// Player
	player = Player::createPlayer(character, glm::vec2(SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4), ui, SCREEN_HEIGHT, program);
	Physics::instance().player = player;

	// Enemies
	for(int i = 0; i < layout.size(); ++i)
		for (int j = 0; j < layout[i].size(); ++j)
		{
			int enemy = -1;
			if (layout[i][j] == 'm') enemy = 0;
			else if (layout[i][j] == 't') enemy = 1;
			else if (layout[i][j] == 'r') enemy = 2;

			if (enemy != -1) 
			{
				enemies.push_back(Enemy::createEnemy(enemy, glm::vec2((32 * j + 282) * scaleFactor, (27 * i + 148) * scaleFactor), SCREEN_HEIGHT, program));
				Physics::instance().enemies.push_back(enemies[enemies.size() - 1]);
			}
		}
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
	Camera::instance().update(deltaTime, player->pos);
	Game::instance().projection = Camera::instance().getProjectionMatrix();

	// UI & Background
	ui->update(deltaTime, Camera::instance().getPos());
	background->update(deltaTime, Camera::instance().getPos());

	// End level if player has no hit poits left
	if (player->hp <= 0) gameOver();

	// Debug
	if(Game::instance().getKey('b')) ui->showBossIntro();
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

vector< vector<char> > Level::loadLevel(const string &levelFile, bool hard)
{
	vector< vector<char> > l;
	ifstream fin;
	string line;

	fin.open(levelFile.c_str());

	getline(fin, line);
	for (int i = 0; i < 5; ++i)
	{
		getline(fin, line);
		if (!hard)
		{
			vector<char> data(line.begin() + 1, line.end() - 1);
			l.push_back(data);
		}
	}

	getline(fin, line);
	getline(fin, line);
	for (int i = 0; i < 5; ++i)
	{
		getline(fin, line);
		if (hard)
		{
			vector<char> data(line.begin() + 1, line.end() - 1);
			l.push_back(data);
		}
	}
	
	fin.close();
	return l;
}

void Level::gameOver()
{
	Game::instance().gameOver = true;
}

void Level::theEnd() 
{
	Game::instance().theEnd = true;
}

