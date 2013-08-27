#include "Camera.h"

Camera::Camera()
{
	mCamPos = glm::vec3(0.0f,0.0f,0.0f);
}

Camera::Camera(glm::vec3 pos,glm::vec3 lookAt)
{
	mCamPos = pos;
	mLookAt = lookAt;
}

glm::vec3 Camera::getPos()
{
	return mCamPos;
}

glm::vec3 Camera::getLookAt()
{
	return mLookAt;
}

void Camera::setPos(glm::vec3 vec)
{
	mCamPos = vec;
}

void Camera::setPos(float x,float y,float z)
{
	mCamPos = glm::vec3(x,y,z);
}

void Camera::lookAt(glm::vec3 vec)
{
	mLookAt = vec;
}

void Camera::lookAt(float x,float y,float z)
{
	mLookAt = glm::vec3(x,y,z);
}

void Camera::move(glm::vec3 vec)
{
	mCamPos += vec;
}