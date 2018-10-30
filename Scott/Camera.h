#ifndef _CAMERA_INCLUDE
#define _CAMERA_INCLUDE

#include <glm/glm.hpp>

class Camera
{
public:
	Camera() { }
	static Camera &instance()
	{
		static Camera C;
		return C;
	}
	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;

	void init(glm::vec2 windowSize, glm::vec2 backgroundSize);
	void update(int deltaTime, glm::vec2 playerPos);

	glm::mat4 getProjectionMatrix();
	glm::vec2 getPos();

private:
	glm::vec2 winSize, bgSize, pos;
	float halfWidth, maxX;
	glm::mat4 projection;

};

#endif // _CAMERA_INCLUDE