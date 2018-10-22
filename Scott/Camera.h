#ifndef _CAMERA_INCLUDE
#define _CAMERA_INCLUDE

#include <glm/glm.hpp>

class Camera
{
public:
	static Camera *createCamera(glm::vec2 windowSize, glm::vec2 backgroundSize);
	Camera(glm::vec2 windowSize, glm::vec2 backgroundSize);
	void update(int deltaTime, glm::vec2 playerPos);
	glm::mat4 getProjectionMatrix();
	glm::vec2 getPos();

private:
	glm::vec2 winSize, bgSize, pos;
	int halfWidth, maxX;
	glm::mat4 projection;

};

#endif // _CAMERA_INCLUDE