#pragma once
#include "headers.h"
#include "external\objLoader.h"
/*
Warning ! Important note... while exporting a mesh it must contain triangles only ! Quads are off limits due to implementation of model loading.
*/
class Mesh
{
	private:
		float * mVertices;
		float * mNormals;
		float * mTexCoords;
		GLuint mTexture;
		size_t mVertCount;
	public:
		Mesh();
		Mesh(Mesh &src);
		~Mesh();
		bool load(std::string name);
		void setTexture(std::string name);
		float * getVertices();
		float * getNormals();
		float * getTexCoords();
		GLuint getTexture();
		size_t getVertCount();
};

class Object
{
	protected:
		Mesh mMesh;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
	public:
		Object();
		Object(glm::vec3 pos, glm::vec3 rot, std::string modelname,std::string texturename);
		Mesh * getMesh();
		glm::vec3 getPos();
		glm::vec3 getRot();
		void setPos(glm::vec3 pos);
		void setRot(glm::vec3 rot);
		void move(glm::vec3 delta);
		void rotate(glm::vec3 delta);
};