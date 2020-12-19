#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace KooNan
{
	enum class GUIState {Default, EditScene, EditBuilding};

	class GUI
	{
	public:
		// init: ��ʼ��GUI����
		//   ��GLFW��ʼ���ʹ��ڴ��������
		//   �ڻ���GUIǰ����
		static void initEnv(GLFWwindow* window) {
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init();

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();


		}

		// newFrame: ����ǰ��׼��
		//   ÿ�λ���ѭ������Ҫ����
		static void newFrame() {
			// feed inputs to dear imgui, start new frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		// setWidgets: �������пؼ�
		//   ��initEnv�����
		static void drawWidgets() {
			// Set all widgets
			switch (curState)
			{
			case KooNan::GUIState::Default:

				break;
			case KooNan::GUIState::EditScene:
				break;
			case KooNan::GUIState::EditBuilding:
				break;
			default:
				break;
			}
			/*
			ImGui::Begin("Demo window");
			ImGui::Button("Hello!");
			ImGui::End();*/

			// Render dear imgui into screen
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		static void ProcessMouseMovement(double xpos, double ypos) {};
		static GUIState getCurState() noexcept { return curState; }
	private:
		static GUIState curState;
	};

	GUIState GUI::curState = GUIState::Default;
}