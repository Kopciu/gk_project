#include "engine.h"

int main(int argc, char* argv[]) 
{
	Engine::getSingleton().init(argc,argv);//passing arguments to init function
	Engine::getSingleton().run();//running the engine
    return 0;
}