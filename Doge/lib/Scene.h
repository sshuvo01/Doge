#ifndef _DOGE_SCENE_H_
#define _DOGE_SCENE_H_
#include "Core.h"
#include "Renderable.h"
#include "Lights.h"
#include <vector>

namespace doge
{
	class Scene final
	{
	public:
		NOCOPYNOASSIGN(Scene);
		Scene();
		~Scene();

		std::vector<Renderable*>   renderablesList;
		std::vector<Light*>        lightsList;
		inline void lol() {  }
	private:
	};

}

#endif // !_DOGE_SCENE_H_
