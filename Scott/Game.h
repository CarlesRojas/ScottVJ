#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Level.h"

#define SCREEN_WIDTH 1920  // 960 1280
#define SCREEN_HEIGHT 1080 // 540 720

class Game
{
public:
	Game() {}

	static Game &instance()
	{
		static Game G;

		return G;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	void init();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool getMouseKey(int key) const;
	glm::vec2 getMousePos() const;

	void setKey(int key, bool set);
	void setSpecialKey(int key, bool set);
	void setMouseKey(int key, bool set);


private:
	bool keepPlaying;
	Level scene;
	bool keys[256], specialKeys[256], mouseKeys[6];
	glm::vec2 mousePos;

};

#endif // _GAME_INCLUDE


