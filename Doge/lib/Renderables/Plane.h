#ifndef _DOGE_PLANE_H_
#define _DOGE_PLANE_H_
#include "Core.h"
#include "Renderable.h"

namespace doge
{
	class Plane : public Renderable
	{
	public:
		NOCOPYNOASSIGN(Plane);
		Plane();
		~Plane();
		void Init() override;
		void Update() override;
		void CleanUp() override;
	private:

	};
}

#endif // !_DOGE_PLANE_H_
