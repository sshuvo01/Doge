#ifndef _DOGE_WINDOW_H_
#define _DOGE_WINDOW_H_
#include "Core.h"

namespace doge
{
	class Window
	{
	public:
		Window() = delete;
		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;
		
		Window(uint width, uint height, const std::string& title);
		~Window();

		void Run() const;
	private:
		GLFWwindow* m_Window = nullptr;
		uint m_Width, m_Height;
		std::string m_Title;
		/*private functions*/
		int SetupWindow();
	};
}


#endif