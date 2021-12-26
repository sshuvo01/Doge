#ifndef _DOGE_ENGINE_H_
#define _DOGE_ENGINE_H_
#include "Core.h"
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"

namespace doge
{
	struct EngineSpec
	{
		uint screenWidth = 640 * 2;
		uint screenHeight = 480 * 2;
		std::string windowTitle = "DOGE";
		Camera* camera = nullptr;
		Renderer* renderer = nullptr;
		Scene* scene = nullptr;
	};
	
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	// singleton class
	class Engine final
	{
	public:
		NOCOPYNOASSIGN(Engine);
		~Engine();

		static Engine& GetInstance();
		void InitEngine(const EngineSpec& es);
		void Run();
		//
		void MouseCallback_(GLFWwindow* window, double xpos, double ypos);
		void ScrollCallback_(GLFWwindow* window, double xoffset, double yoffset);
		//
		inline double GetDeltaTime() const { return m_DeltaTime; }
		inline void SetRenderer(Renderer* renderer) { m_Spec.renderer = renderer; }
		inline void SetCamera(Camera* camera) { m_Spec.camera = camera; }
		inline void SetScene(Scene* scene) { m_Spec.scene = scene; }
		inline void SetSpec(const EngineSpec& es) { m_Spec = es; }
	private:
		Engine();
		EngineSpec       m_Spec;
		double           m_DeltaTime = 0.0, m_LastFrameTime = 0.0, m_CurrentFrameTime, m_LastX, m_LastY;
		bool             m_FirstMouse = true;
		GLFWwindow*      m_Window = nullptr;
		/*private functions*/
		int SetupWindow();
		void ProcessInput(GLFWwindow *window);
		void CalculateDeltaTime();
		void Validate() const;
	};

}

#endif // !_DOGE_ENGINE_H_
