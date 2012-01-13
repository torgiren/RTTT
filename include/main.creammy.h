#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>

#ifdef WIN32
	#define WINDOWS
#else
	#ifdef WIN64
		#define WINDOWS
	#else
		#define LINUX
	#endif
#endif

extern "C"
	{
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <SDL/SDL_thread.h>
	}
using namespace std;

#include "consts.h"

#include "windowengine.h"
#include "utils/log.h"

#define printf Log::info
