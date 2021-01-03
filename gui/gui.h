#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GameController.h>

namespace KooNan
{
	enum class GUIState {Title, Wandering, Creating, Pause};
	int imguiDefaultFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground;

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

		// setWidgets: �������пؼ�����������
		//   ��initEnv�����
		static void drawWidgets(int windowWidth, int windowHeight) {
			ImGui::Begin("Menu", 0, imguiDefaultFlags);
			switch (curState)
			{
			case KooNan::GUIState::Title:
				// todo�������ڷŵ����л��Ʋ˵�

				break;
			case KooNan::GUIState::Wandering:
				ImGui::SetWindowPos(ImVec2(0, 0));
				if (!hideGui && ImGui::Button("Pause")) {
					changeStateTo(GUIState::Pause);
					GameController::gameMode = Pause;
				}
				if (!hideGui && ImGui::Button("Begin Record")) {
					// todo
				}
				if ((!hideGui && ImGui::Button("Hide UI")) || (hideGui && ImGui::Button("Show UI"))) {
					hideGui = !hideGui;
				}
				if (!hideGui && ImGui::Button("Edit Scene")) {
					changeStateTo(GUIState::Creating);
					GameController::mainCamera = Camera();
					GameController::gameMode = Creating;
				}
				break;
			case KooNan::GUIState::Creating:
				ImGui::SetWindowPos(ImVec2(0, 0));
				if (ImGui::Button("Pause")) {
					changeStateTo(GUIState::Pause);
					GameController::gameMode = Pause;
				}
				if (ImGui::Button("Save")) {
					// todo
				}
				if (ImGui::Button("Wander")) {
					// ��鵱ǰ�Ƿ�ѡ���˽�����λ�ò��Ϸ�
					if (1) {
						changeStateTo(GUIState::Wandering);
						GameController::gameMode = Wandering;
					}
				}
				break;
			case KooNan::GUIState::Pause:
				// todo���ı�menuλ�õ�����
				if (ImGui::Button("Continue")) {
					revertState();
					if (curState == GUIState::Creating) GameController::gameMode = Creating;
					else if (curState == GUIState::Wandering) GameController::gameMode = Wandering;
				}
				if (ImGui::Button("Save and Quit to Title")) {
					// todo����鵱ǰ�Ƿ�ѡ���˽�����λ�ò��Ϸ�
					if (1) {
						changeStateTo(GUIState::Title);
						GameController::gameMode = Tile;
					}
				}
				break;
			default:
				break;
			}
			ImGui::End();

			if (curState == GUIState::Creating) {
				// todo������ѡ��������
				ImGui::Begin("Select Page");
				ImGui::End();

				// todo����ѡ�н���ʱ������ѡ�н�����Χ�Ĳ˵�
				if (1) {

				}
			}

			// Render dear imgui into screen
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		// changeStateTo: �ı�״̬����λ��
		static void changeStateTo(GUIState nextState) {
			preState = curState;
			curState = nextState;
		}

		// revertState���˻�ǰһ״̬����������˵ֻ��pause����
		static void revertState() {
			GUIState tmp = curState;
			curState = preState;
			preState = tmp;
		}

	private:
		static GUIState curState, preState;
		static bool hideGui;
	};

	GUIState GUI::preState = GUIState::Title;
	GUIState GUI::curState = GUIState::Wandering;
	bool GUI::hideGui = false;
}