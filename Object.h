#pragma once
#include "headers.h"
#include "external\objLoader.h"
/*
Mesh object for loading meshes from *.obj format and containing verticles and texture coordinates positions and normal vectors. It also loads textures (it's tied with Object class)
[Warning !] Important note - while exporting a mesh it must contain triangles only ! Quads are off limits due to implementation of model loading.
*/


class Mesh
{
	private:
		//an array of...
		float * mVertices;//...verticles
		float * mNormals;//...normal vectors
		float * mTexCoords;//... texture coordinates.
		GLuint mTexture;//texture handler
		Material mMaterial;
		size_t mVertCount;//the number of verticles a mesh has
		bool mTextured;//tells us if texture is loaded
	public:
		Mesh();
		Mesh(Mesh &src);
		~Mesh();
		bool load(std::string name);
		void setTexture(std::string name);
		float * getVertices();
		float * getNormals();
		float * getTexCoords();
		Material * getMaterial();
		GLuint getTexture();
		size_t getVertCount();
		void fixTexCoords();
		bool isTextured();
};

class Object
{
	protected:
		Mesh mMesh;
		glm::vec3 mPosition;//position
		glm::vec3 mRotation;//rotation
		glm::vec3 mDelta;//model local axis position change
		std::string mName;//name
	public:
		Object();
		Object(std::string name, glm::vec3 pos, glm::vec3 rot, std::string modelname,std::string texturename);
		Mesh * getMesh();
		glm::vec3 getPos();
		glm::vec3 getRot();
		glm::vec3 dropDelta();
		void setPos(glm::vec3 pos);
		void setRot(glm::vec3 rot);
		void move(glm::vec3 delta);//move uses global axis
		void translate(glm::vec3 delta);//translate uses model-space axis
		void rotate(glm::vec3 delta);
		void fixTexCoords();//blender texture coordinates correction method
		std::string getName();
		void setName(std::string name);
};