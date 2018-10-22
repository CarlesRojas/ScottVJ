#ifndef _PHYSICS_INCLUDE
#define _PHYSICS_INCLUDE

#include "Player.h"
#include "Background.h"
#include "Enemy.h"


class Physics
{
public:
	// Singleton
	Physics() {}
	static Physics &instance()
	{
		static Physics P;

		return P;
	}
	Physics(Physics const&) = delete;
	void operator=(Physics const&) = delete;

	void init(ShaderProgram * texProgram);
	void render();

	static bool overlap(Box * box1, Box * box2);
	bool correctPosition(Box * box);
	void attack(Attack * attack);


	ShaderProgram *program;
	Background *background;
	Player *player;
	vector<Enemy*> enemies;

private:
	// Debug
	void loadOutlineTextures();
	void printBoxes(bool printBackground);
	Texture red, blue, green, yellow;
	GLuint vao, vbo;
	vector<float> vertices;
	GLint posLocation, texCoordLocation;
};


#endif //_PHYSICS_INCLUDE