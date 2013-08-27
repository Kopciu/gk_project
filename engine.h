#pragma once 
#include "headers.h"
#include "Camera.h"
#include "Object.h"

class Engine
{
	private:
		std::vector<Object *> mRenderQueue;
		static Engine * mSingleton;
		static void displayFrame();
		static void nextFrame();
		static void keyUp(int c, int x, int y);
		static void keyDown(int c, int x, int y);
		glm::vec3 mCamDelta;
		Camera mCamera;
		int mLastTime;
		Engine();
	public:
		~Engine();
		static Engine & getSingleton();
		static Engine * getSingletonPtr();
		bool init(int &arg_count,char * arg_val[]);
		void run();
};