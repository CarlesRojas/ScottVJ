#ifndef _BOX_INCLUDE
#define _BOX_INCLUDE

#include <glm/glm.hpp>

class Box
{
public:
	enum BoxOwner { PLAYER, ENEMY, BACKGROUND };
	enum BoxType { HIT, BASE, ATTACK };

	static Box * createBox(BoxOwner owner, BoxType type, const glm::vec2 &bottomMidPoint, const glm::vec2 &size);
	static Box * createBox(BoxOwner owner, BoxType type, float left, float right, float top, float bot);
	Box(BoxOwner owner, BoxType type, const glm::vec2 &bottomMidPoint, const glm::vec2 &size);

	glm::vec2 getPos();
	void increasePos(const glm::vec2 & deltaPos);
	void moveTo(glm::vec2 bottomMidPoint);

	BoxOwner owner;
	BoxType type;
	float left, right, top, bot;
	glm::vec2 size;
	bool active;
};

#endif // _BOX_INCLUDE
