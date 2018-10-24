#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Level.h"
#include "Screen.h"

#define SCREEN_WIDTH 960  // 960 1280 1920
#define SCREEN_HEIGHT 540 // 540 720 1080

class Game
{
public:
	enum GameState { MAIN, CHOOSE, LVL1, LVL2, LVL3, GAMEOVER, THEEND };
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

	glm::mat4 projection;

private:
	void initShaders();

	GameState state;
	bool keepPlaying;
	Level level;
	bool keys[256], specialKeys[256], mouseKeys[6];
	glm::vec2 mousePos;

	Screen *screen;

	float currentTime;
	ShaderProgram program;
};

#endif // _GAME_INCLUDE


