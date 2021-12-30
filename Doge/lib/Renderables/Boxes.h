#ifndef _DOGE_BOXES_H_
#define _DOGE_BOXES_H_
#include "Renderable.h"

namespace doge
{
	class Boxes : public Renderable
	{
	public:
		NOCOPYNOASSIGN(Boxes);
		Boxes();
		~Boxes();

		void Init() override;
		void Update() override;
		void CleanUp() override;
	private:

	};
}

#endif // !_DOGE_BOXES_H_
