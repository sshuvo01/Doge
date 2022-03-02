#ifndef _DOGE_MODELS_H_
#define _DOGE_MODELS_H_
#include "Renderable.h"

namespace doge
{
	class Model;
	class Mesh;
	class Models : public Renderable
	{
	public:
		NOCOPYNOASSIGN(Models);
		Models(std::vector<Renderable*>& renderablesList);
		~Models();

		void Init() override;
		void Update() override;
		void CleanUp() override;
	private:
		Model*          m_TheModel = nullptr;
		Renderable*     m_Meshes = nullptr;
		/*private functions*/
		std::shared_ptr<Texture> ExtractTexture(size_t meshIndex, const MaterialMapType& type) const;
	};

}

#endif // !_DOGE_MODELS_H_
