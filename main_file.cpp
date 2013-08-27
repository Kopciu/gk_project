#include "engine.h"

int main(int argc, char* argv[]) 
{
	Engine::getSingleton().init(argc,argv);
	Engine::getSingleton().run();
    return 0;
}