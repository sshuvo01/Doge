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
		void GetTangentBitengent(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& pos3,
			const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3, glm::vec3& tangent, glm::vec3& bitangent) const;

	};
}

#endif // !_DOGE_PLANE_H_
