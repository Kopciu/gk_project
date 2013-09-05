#include "Object.h"

Mesh::Mesh()
{
	mVertices = NULL;
	mNormals = NULL;
	mTexCoords = NULL;
	mVertCount = 0;
	mTexture = 0;
	mTextured = false;
}

Mesh::Mesh(Mesh &src)
{
	mVertices = new float [src.mVertCount*3];
	mNormals = new float [src.mVertCount*3];
	mTexCoords = new float [src.mVertCount*2];
	mVertCount = src.mVertCount;
	mTexture = src.mTexture;
	mTextured = src.mTextured;
	for(size_t i = 0;i < src.mVertCount*3;i++)
	{
		mVertices[i] = src.mVertices[i];
		mNormals[i] = src.mNormals[i];
	}
	for(size_t i = 0;i < src.mVertCount*2;i++)
	{
		mTexCoords[i] = src.mTexCoords[i];
	}
}

Mesh::~Mesh()
{
	if(mVertices)
		delete [] mVertices;
	if(mNormals)
		delete [] mNormals;
	if(mTexCoords)
		delete [] mTexCoords;
}

bool Mesh::load(std::string name)//function that parses *.obj files (uses external library to do so)
{
	objLoader * temp = new objLoader();
	if(!temp->load((char *) (name.c_str())))
	{
		delete temp;
		return false;
	}
	mVertCount = temp->faceCount*3;///all tris
	mVertices = new float[mVertCount*3];
	mNormals = new float[mVertCount*3];
	mTexCoords = new float[mVertCount*2];
	for(size_t i = 0;i < temp->faceCount;i++)
	{
		for(size_t j = 0;j < 3;j++)
		{
			for(size_t k = 0;k < 3;k++)
			{
				mVertices[(i*9)+(j*3)+k] = temp->vertexList[temp->faceList[i]->vertex_index[j]]->e[k];
				mNormals[(i*9)+(j*3)+k] = temp->normalList[temp->faceList[i]->normal_index[j]]->e[k];
			}
		}
	}
	for(size_t i = 0;i < temp->faceCount;i++)
	{
		for(size_t j = 0;j < 3;j++)
		{
			for(size_t k = 0;k < 2;k++)
			{
				mTexCoords[(i*6)+(j*2)+k] = temp->textureList[temp->faceList[i]->texture_index[j]]->e[k];
			}
		}
	}
	delete temp;
	return true;
}

float * Mesh::getVertices()
{
	return mVertices;
}

float * Mesh::getNormals()
{
	return mNormals;
}

float * Mesh::getTexCoords()
{
	return mTexCoords;
}

GLuint Mesh::getTexture()
{
	return mTexture;
}

size_t Mesh::getVertCount()
{
	return mVertCount;
}

void Mesh::setTexture(std::string name)///COPYPASTA ! %-D
{
	TGAImg img; 
	if(img.Load((char *) name.c_str())==IMG_OK) 
	{
		mTextured = true;
		glGenTextures(1,&mTexture);
		glBindTexture(GL_TEXTURE_2D,mTexture);
		if(img.GetBPP()==24)
			glTexImage2D(GL_TEXTURE_2D,0,3,img.GetWidth(),img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,img.GetImg());
		else if(img.GetBPP()==32)
			glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,img.GetImg());
		else
		{
			mTextured = false;
			printf("[Warning]Texture (\"%s\") is in unsupported format.\n",name.c_str());
		}
	}
	else
	{
		printf("[Warning]Texture (\"%s\") cannot be loaded (file loading error).\n",name.c_str());
	}
}

void Mesh::fixTexCoords()
{
	for(size_t i = 1;i < mVertCount*2;i+=2)
	{
		mTexCoords[i] = 1.0f-mTexCoords[i];
	}
}

bool Mesh::isTextured()
{
	return mTextured;
}

Object::Object() : mMesh()
{
	mName = "";
}

Object::Object(std::string name, glm::vec3 pos, glm::vec3 rot, std::string modelname,std::string texturename)
{
	mPosition = pos;
	mRotation = rot;
	mMesh.load(modelname);
	if(!texturename.empty())
		mMesh.setTexture(texturename);
	mName = name;
}

Mesh * Object::getMesh()
{
	return &mMesh;
}

glm::vec3 Object::getPos()
{
	return mPosition;
}

glm::vec3 Object::getRot()
{
	return mRotation;
}

glm::vec3 Object::dropDelta()
{
	glm::vec3 temp = mDelta;
	mDelta = glm::vec3(0.0f,0.0f,0.0f);
	return temp;
}

void Object::setPos(glm::vec3 pos)
{
	mPosition = pos;
}

void Object::setRot(glm::vec3 rot)
{
	mRotation = rot;
}

void Object::move(glm::vec3 delta)
{
	mPosition += delta;
}

void Object::translate(glm::vec3 delta)
{
	mDelta += delta;
}

void Object::rotate(glm::vec3 delta)
{
	mRotation += delta;
}

void Object::fixTexCoords()
{
	mMesh.fixTexCoords();
}

std::string Object::getName()
{
	return mName;
}

void Object::setName(std::string name)
{
	mName = name;
}