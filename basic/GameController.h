#pragma once
#include <Camera.h>
#include <glm/glm.hpp>
#include <Render.h>

namespace KooNan
{
	enum GameMode
	{
		Tile,
		Pause,
		Wandering,
		Creating
	};
	class GameController
	{
		// ȫ��״̬
	public:
		
		
		static bool firstMouse; // �Ƿ��ǵ�һ�ε������������ƶ��¼���
		static bool altPressedLast; // ��һ��ѭ���Ƿ���alt��
		static float deltaTime;
		static float lastFrame;

		static Camera mainCamera;
		static unsigned int mouseX;
		static unsigned int mouseY;
		// ȫ���źţ���GUIģ����������д�룬������ģ���ȡ
	public:
		static GameMode gameMode; // ��Ϸģʽ����ͣ�����Ρ�����
		static int sthSelected; // �����������屻ʰȡ
		// �������봦��ʰȡ
	public:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void processInput(GLFWwindow* window);
		static void updateCursorMode(GLFWwindow* window);
	};

	// ״̬���źų�ʼ��

	bool GameController::firstMouse = true;
	float GameController::lastFrame = .0f;
	float GameController::deltaTime = .0f;
	unsigned int GameController::mouseX = Render::SCR_WIDTH / 2;
	unsigned int GameController::mouseY = Render::SCR_HEIGHT / 2;
	Camera GameController::mainCamera = Camera(glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	GameMode GameController::gameMode = Wandering;
	int GameController::sthSelected = 0;
	//MousePicker GameController::mpicker = MousePicker(GameController::mainCamera,
		//glm::perspective(glm::radians(GameController::mainCamera.Zoom), (float)Render::SCR_WIDTH / (float)Render::SCR_HEIGHT, 0.1f, 1000.0f));
	// ��������
	void GameController::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GameController::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		static float lastX = Render::SCR_WIDTH / 2.0f;
		static float lastY = Render::SCR_HEIGHT / 2.0f;

		if (gameMode == Creating) {
			
		}
		else if(gameMode == Wandering) {
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}
			GameController::mouseX = xpos;
			GameController::mouseY = ypos;
			//mpicker.update(xpos, ypos);
			//std::cout << mpicker.getCurrentRay().x << " " << mpicker.getCurrentRay().y << " " << mpicker.getCurrentRay().z << std::endl;
			
			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			mainCamera.ProcessMouseMovement(xoffset, yoffset);
			
		}
	}

	void GameController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mainCamera.ProcessMouseScroll(gameMode == Wandering ? FOVY_CHANGE : HEIGHT_CHANGE, yoffset);
	}

	void GameController::processInput(GLFWwindow* window)
	{
		

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (gameMode == Creating)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(NORTH, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(SOUTH, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(WEST, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(EAST, deltaTime);
		}
		else if (gameMode == Wandering)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(FORWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(BACKWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(LEFT, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(RIGHT, deltaTime);
		}
	}

	void GameController::updateCursorMode(GLFWwindow* window)
	{
		
	}
}