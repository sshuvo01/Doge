#ifndef _DOGE_LIGHTS_H_
#define _DOGE_LIGHTS_H_
#include "Core.h"
#include <glm/matrix.hpp>

namespace doge
{
	enum class LightType
	{
		POINT, 
		DIRECTIONAL
	};

	class Light
	{
	public:
		Light();
		~Light();

	private:

	protected:
		LightType    m_Type;
		glm::vec3    m_Color;
	};

	
	// point light
	class PointLight : public Light
	{
	public:
	private:
		
	};
}

#endif // !_DOGE_LIGHTS_H_

