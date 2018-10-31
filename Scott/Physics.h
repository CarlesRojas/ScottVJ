#ifndef _PHYSICS_INCLUDE
#define _PHYSICS_INCLUDE

#include "Player.h"
#include "Background.h"
#include "Enemy.h"


class Physics
{
public:
	// Singleton
	Physics();
	~Physics();
	static Physics &instance()
	{
		static Physics P;

		return P;
	}
	Physics(Physics const&) = delete;
	void operator=(Physics const&) = delete;

	void init(ShaderProgram * texProgram);
	void render();
	void reset();

	static bool overlap(Box * box1, Box * box2);
	bool correctPosition(Box * box);
	void attack(Attack * attack);
	bool isCloseThan(Enemy * e, int dist);
	bool isInAttackRange(Enemy * e, glm::vec2 min, glm::vec2 max);
	glm::vec2 distToPlayer(Enemy * e);
	glm::vec2 getPlayerPos();


	ShaderProgram *program;
	Background *background;
	Player *player;
	vector<Enemy*> enemies;

private:
	void loadOutlineTextures();
	void printBoxes(bool printBackground);
	GLuint vao, vbo;
	vector<float> vertices;
	GLint posLocation, texCoordLocation;
};


#endif //_PHYSICS_INCLUDE
