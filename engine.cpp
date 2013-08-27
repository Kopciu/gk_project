#include "engine.h"

#define instance (*Engine::mSingleton)

Engine * Engine::mSingleton = NULL;

Engine & Engine::getSingleton()
{
	if(Engine::mSingleton)
		return *mSingleton;
	mSingleton = new Engine();
	return *mSingleton;
}

Engine * Engine::getSingletonPtr()
{
	if(Engine::mSingleton)
		return mSingleton;
	mSingleton = new Engine();
	return mSingleton;
}

void Engine::displayFrame()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	instance.mCamera.move(Engine::getSingleton().mCamDelta);	
	glm::mat4 V=glm::lookAt(
		instance.mCamera.getPos(),
		instance.mCamera.getLookAt(),
		glm::vec3(0.0f,1.0f,0.0f));
	//V=glm::translate(V,instance.mCamDelta);
	glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	for(size_t i = 0;i < instance.mRenderQueue.size();i++)///RENDERING LOOP !
	{//LOOP.. LOOP.. LOOP.. LOOP.. LOOP.. LOOSE OVERALL ORIENTATION in PROGRAMMING
		Object * current = instance.mRenderQueue[i];
		if(current->getMesh()->getVertices() && current->getMesh()->getVertCount())
		{		
			glMatrixMode(GL_MODELVIEW);
			glm::mat4 M=glm::mat4(1.0f);
			M=glm::translate(M,current->getPos());
			if(current->getRot().x != 0.0f)
				M=glm::rotate(M,current->getRot().x,glm::vec3(1.0f,0.0f,0.0f));
			if(current->getRot().y != 0.0f)
				M=glm::rotate(M,current->getRot().y,glm::vec3(0.0f,1.0f,0.0f));
			if(current->getRot().z != 0.0f)			
				M=glm::rotate(M,current->getRot().z,glm::vec3(0.0f,0.0f,1.0f));
			glLoadMatrixf(glm::value_ptr(V*M));
			if(current->getMesh()->getTexture())
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			
				glBindTexture(GL_TEXTURE_2D,current->getMesh()->getTexture());
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			if(current->getMesh()->getNormals())
				glEnableClientState(GL_NORMAL_ARRAY);
			if(current->getMesh()->getTexCoords())
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(3,GL_FLOAT,0,current->getMesh()->getVertices());
			glTexCoordPointer(2,GL_FLOAT,0,current->getMesh()->getTexCoords());
			glNormalPointer(GL_FLOAT,0,current->getMesh()->getNormals());
			glDrawArrays(GL_TRIANGLES,0,current->getMesh()->getVertCount());
			glDisableClientState(GL_VERTEX_ARRAY);
			if(current->getMesh()->getNormals())
				glEnableClientState(GL_NORMAL_ARRAY);
			if(current->getMesh()->getTexCoords())
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}
	glutSwapBuffers();
}

void Engine::nextFrame()
{
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-instance.mLastTime;
	instance.mLastTime=actTime;
	instance.mCamDelta *= interval*0.02f; 
	glutPostRedisplay();
}

Engine::Engine()
{
	mCamera = Camera(glm::vec3(0.0f,0.0f,-5.0f),glm::vec3(0.0f,0.0f,0.0f));
	mCamDelta = glm::vec3(0.0f,0.0f,0.0f);
	mLastTime = 0;
}

Engine::~Engine()
{
	Engine::mSingleton = NULL;
}

bool Engine::init(int &arg_count,char * arg_val[])
{
	glutInit(&arg_count, arg_val);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Flight simulator");
	glutDisplayFunc(Engine::displayFrame);
	glutIdleFunc(Engine::nextFrame);
	glutSpecialFunc(Engine::keyDown);
	glutSpecialUpFunc(Engine::keyUp);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	mRenderQueue.push_back(new Object(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),"pac-man.obj","bricks.tga"));
	return true;
}

void Engine::run()
{
	glutMainLoop();
}

void Engine::keyUp(int c, int x, int y)
{
	switch (c) 
	{
		case GLUT_KEY_LEFT: 

		break;
		
		case GLUT_KEY_RIGHT:

		break;
		
		case GLUT_KEY_UP: 
			instance.mCamDelta.z = 0;
		break;
		
		case GLUT_KEY_DOWN:
			instance.mCamDelta.z = -0;
		break;  
	}
}

void Engine::keyDown(int c, int x, int y)
{
	switch (c) 
	{
	case GLUT_KEY_LEFT: 
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP: 
		//speed_x=60;
		instance.mCamDelta.z = 1;
		break;
	case GLUT_KEY_DOWN:
		//speed_x=-60;
		instance.mCamDelta.z = -1;
		break;  
	}
}