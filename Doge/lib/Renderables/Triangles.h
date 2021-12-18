#ifndef _DOGE_TRIANGLES_H_
#define _DOGE_TRIANGLES_H_
#include "Renderable.h"

namespace doge
{
	class Triangles : public Renderable
	{
	public:
		NOCOPYNOASSIGN(Triangles);
		Triangles();
		~Triangles();

		void Init() override;
		void Update() override;
		void CleanUp() override;

	private:

	};

}

#endif // !_DOGE_TRIANGLES_H_
