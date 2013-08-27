#pragma once
#include "headers.h"

/*enum camBehaviour 
{
	C_STATIC,//looking at just one fixed point in space... God, must feel lonely
	C_
};*/

class Camera
{
	private:
		glm::vec3 mCamPos;
		glm::vec3 mLookAt;
	public:
		Camera();
		Camera(glm::vec3 pos,glm::vec3 lookAt);
		glm::vec3 getPos();
		glm::vec3 getLookAt();
		void setPos(glm::vec3 vec);
		void setPos(float x,float y,float z);
		void lookAt(glm::vec3 vec);
		void lookAt(float x,float y,float z);
		void move(glm::vec3 vec);
};