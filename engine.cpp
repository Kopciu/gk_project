#include "engine.h"

#define instance (*Engine::mSingleton)//so instance is just this thing, it helps us deal with references to singleton in static functions (shortens the code)

Engine * Engine::mSingleton = NULL;

Object * Engine::findObject(std::string name)
{
	for(size_t i = 0;i < mRenderQueue.size();i++)
	{
		if(!name.compare(mRenderQueue[i]->getName()))
			return mRenderQueue[i];
	}
	return NULL;
}

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
	//instance.mCamera.move(Engine::getSingleton().mCamDelta);	
	glm::mat4 V=glm::lookAt(
		instance.mCamera.getPos(),
		instance.mCamera.getLookAt(),
		glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	for(size_t i = 0;i < instance.mRenderQueue.size();i++)///RENDERING LOOP !
	{//LOOP.. LOOP.. LOOP.. LOOP.. LOOP.. LOOSE OVERALL ORIENTATION in PROGRAMMING
		Object * current = instance.mRenderQueue[i];
		if(current->getMesh()->getVertices() && current->getMesh()->getVertCount())//dude, do you even render ?
		{		
			glMatrixMode(GL_MODELVIEW);
			glm::mat4 M=glm::mat4(1.0f);
			glm::mat4 R=glm::mat4(1.0f);
			M=glm::translate(M,current->getPos());
			if(current->getRot().x != 0.0f)
				R=glm::rotate(R,current->getRot().x,glm::vec3(1.0f,0.0f,0.0f));
			if(current->getRot().y != 0.0f)
				R=glm::rotate(R,current->getRot().y,glm::vec3(0.0f,1.0f,0.0f));
			if(current->getRot().z != 0.0f)			
				R=glm::rotate(R,current->getRot().z,glm::vec3(0.0f,0.0f,1.0f));
			M=M*R*glm::translate(glm::mat4(1.0f),current->dropDelta());
			current->setPos(glm::vec3(M[3][0],M[3][1],M[3][2]));
			glLoadMatrixf(glm::value_ptr(V*M));
			if(current->getMesh()->isTextured())
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			
				glBindTexture(GL_TEXTURE_2D,current->getMesh()->getTexture());
			}
			else
			{
				
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
	instance.mDelta *= interval*0.02f; 
	instance.findObject("box")->move(instance.mDelta);
	glutPostRedisplay();
}

Engine::Engine()
{
	mCamera = Camera(glm::vec3(0.0f,0.0f,-5.0f),glm::vec3(0.0f,0.0f,0.0f));
	mDelta = glm::vec3(0.0f,0.0f,0.0f);
	mLastTime = 0;
}

Engine::~Engine()
{
	for(size_t i = 0; i < mRenderQueue.size();i++)
	{
		delete mRenderQueue[i];
	}
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
	mRenderQueue.push_back(new Object("box",glm::vec3(0.0f,0.0f,0.0f),glm::vec3(120.0f,0.0f,0.0f),"box.obj","bricks.tga"));//adding objects to render queue. shouldn't be done that way and it's done like that only for test purposes
	mRenderQueue.push_back(new Object("pacmate",glm::vec3(-1.0f,2.0f,0.0f),glm::vec3(0.0f,360.0f-45.0f,0.0f),"pac-man.obj","p_tex.tga"));	
	Object * ptr = findObject("pacmate");
	if(ptr)
	{
		printf("Found object: %s . Messing...\n",ptr->getName().c_str());
		ptr->fixTexCoords();
	}
	return true;
}

void Engine::run()
{
	glutMainLoop();
}

void Engine::keyUp(int c, int x, int y)
{
	switch(c)
	{
		case GLUT_KEY_LEFT: 
		{
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			break;
		}
		case GLUT_KEY_UP:
		{
			instance.mDelta.z = 0;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			instance.mDelta.z = -0;
			break;
		}
	}
}

void Engine::keyDown(int c, int x, int y)//activated when key is pressed
{
	switch (c) 
	{
		case GLUT_KEY_LEFT:
		{
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			break;
		}
		case GLUT_KEY_UP :{ // <---- just look how this guy is stressed out; you don't want to be him ! format your code properly (brought to you by the department of joy) 
			//speed_x=60;
			instance.mDelta.z = 1;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			//speed_x=-60;
			instance.mDelta.z = -1;
			break;
		}
	}
}