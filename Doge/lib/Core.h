#ifndef _DOGE_CORE_H_
#define _DOGE_CORE_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include <string>
typedef unsigned int uint;
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) doge::GLClearError();x;ASSERT(doge::GLLogCall(#x, __FILE__, __LINE__))
#define NOCOPY(x) x(const x&)=delete;x(const x&&)=delete
#define NOASSIGN(x) x& operator=(const x&)=delete;x& operator=(const x&&)=delete
#define NOCOPYNOASSIGN(x) NOCOPY(x);NOASSIGN(x)
#define DELETE(x) if(x)delete x;x=nullptr
#define DELETEARRAY(x) if(x)delete[] x;x=nullptr


namespace doge
{

	inline void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR)
		{

		}
	}

	inline bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{		
			spdlog::critical("OpenGL failed! info: 0x{0:x}, {1}, {2}", error, function, line);
			return false; 
		}
		return true;
	}



}

#endif
