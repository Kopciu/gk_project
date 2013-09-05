#pragma once
#include "headers.h"
#include "Camera.h"
#include "Object.h"

class Engine
{
	private:
		std::vector<Object *> mRenderQueue;//self explainatory
		static Engine * mSingleton;//static pointer to the only instance of this class (see more: singletons)
		static void displayFrame();
		static void nextFrame();
		static void keyUp(int c, int x, int y);
		static void keyDown(int c, int x, int y);//these four functions are static because their addresses are passed as arguments in some GLUT functions. Cannot be worked around since C++ doesn't support delegate mechanism
		glm::vec3 mDelta;
		Camera mCamera;//camera object
		int mLastTime;//timestamp of last frame
		Object * findObject(std::string name);//finding object by name in rendering queue
		Engine();//constructor is private so no one can create more than one object
	public:
		~Engine();
		static Engine & getSingleton();//gets singleton as object instance
		static Engine * getSingletonPtr();//gets singleton as object pointer
		bool init(int &arg_count,char * arg_val[]);//init function initiates subsystems; arguemnts are parameters of main function
		void run();//run method... pretty much self-explainatory
};