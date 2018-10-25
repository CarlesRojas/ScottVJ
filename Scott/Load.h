#ifndef _LOAD_INCLUDE
#define _LOAD_INCLUDE

#include "Texture.h"

class Load
{
public:
	Load() { }
	static Load &instance()
	{
		static Load L;
		return L;
	}

	Load(Load const&) = delete;
	void operator=(Load const&) = delete;

	void init();

	Texture screens;

	Texture lvl0;
	Texture lvl1;
	Texture lvl2;

	Texture scott;
	Texture ramona;
	Texture kim;

	Texture malcolm;
	Texture roxilla;
	Texture turret;
};

#endif // _LOAD_INCLUDE
