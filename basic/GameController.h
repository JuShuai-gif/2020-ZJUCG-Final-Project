#pragma once
#include <Camera.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace KooNan
{
	enum GameMode
	{// ��һ��״̬
		Title, // ����ҳ
		Pause, // ��ͣҳ
		Wandering, // ��������ģʽ
		Creating // ����ģʽ
	};
	enum CreatingMode
	{
		Placing, // ����ģʽ
		Viewing // �۲�ģʽ
	};
	enum class MouseMode {
		GUIMode, CameraMode
	};
	class GameController
	{
		// ȫ�ֳ���
	public:
		const static unsigned int EDGE_WIDTH = 50;
		// ȫ��״̬
	public:
		static unsigned int SCR_WIDTH, SCR_HEIGHT; // ��Ļ��С
		
		static bool firstMouse; // �Ƿ��ǵ�һ�ε������������ƶ��¼���
		static bool altPressedLast; // ��һ��ѭ���Ƿ���alt��
		static MouseMode mouseMode;
		static float deltaTime;
		static float lastFrame;

		static double cursorX, cursorY;

		static Camera mainCamera;
		static Camera oriCreatingCamera;

		// ȫ���źţ���GUIģ����������д�룬������ģ���ȡ
	public:
		static GameMode gameMode; // ��Ϸģʽ
		static CreatingMode creatingMode; // ����ģʽ��ģʽ
		static int sthSelected; // �����������屻ʰȡ
	public:
		static void initGameController(GLFWwindow* window)
		{
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, GameController::framebuffer_size_callback);
			glfwSetCursorPosCallback(window, GameController::cursor_callback);
			glfwSetScrollCallback(window, GameController::scroll_callback);
			glfwSetMouseButtonCallback(window, GameController::mouse_callback);
		}
		static void updateGameController(GLFWwindow* window)
		{
			float currentFrame = glfwGetTime();
			GameController::deltaTime = currentFrame - GameController::lastFrame;
			GameController::lastFrame = currentFrame;

			glfwGetCursorPos(window, &cursorX, &cursorY);

			GameController::processInput(window);

			// ����ģʽ��ʹ���������ƶ����
			if (gameMode == Creating) {
				
				if (cursorX <= EDGE_WIDTH)
					mainCamera.ProcessKeyboard(0.001f, WEST);
				else if (cursorX >= SCR_WIDTH - EDGE_WIDTH)
					mainCamera.ProcessKeyboard(0.001f, EAST);
				if(cursorY <= EDGE_WIDTH)
					mainCamera.ProcessKeyboard(0.001f, NORTH);
				else if(cursorY >= SCR_HEIGHT - EDGE_WIDTH)
					mainCamera.ProcessKeyboard(0.001f, SOUTH);
			}
		}
	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void processInput(GLFWwindow* window);
		static void updateCursorMode(GLFWwindow* window, bool bLAltDown);
	private:
		
	};

	// ״̬���źų�ʼ��
	unsigned int GameController::SCR_WIDTH = 800;
	unsigned int GameController::SCR_HEIGHT = 600;

	bool GameController::firstMouse = true;
	bool GameController::altPressedLast = false;
	MouseMode GameController::mouseMode = MouseMode::GUIMode;
	float GameController::lastFrame = .0f;
	float GameController::deltaTime = .0f;
	double GameController::cursorX = .0;
	double GameController::cursorY = .0;

	Camera GameController::oriCreatingCamera = Camera(0.f, 2.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	Camera GameController::mainCamera = GameController::oriCreatingCamera;

	GameMode GameController::gameMode = Creating;
	CreatingMode GameController::creatingMode = Placing;
	int GameController::sthSelected = 0;

	// ��������
	void GameController::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GameController::cursor_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (mouseMode == MouseMode::GUIMode) return;

		static float lastX = SCR_WIDTH / 2.0f;
		static float lastY = SCR_HEIGHT / 2.0f;
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		// �����겻��ʾʱ�㵽GUI�ϵİ�ť�����ֹ��λ������Ļ����
		lastX = SCR_WIDTH / 2.0f;
		lastY = SCR_HEIGHT / 2.0f;
		glfwSetCursorPos(window, lastX, lastY);

		if(gameMode == Wandering) {
			mainCamera.ProcessMouseMovement(xoffset, yoffset);
		}
	}

	void GameController::mouse_callback(GLFWwindow* window, int button, int action, int mods)
	{

	}

	void GameController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mainCamera.ProcessMouseScroll(gameMode == Wandering ? FOVY_CHANGE : HEIGHT_CHANGE, yoffset);
	}

	void  GameController::processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (gameMode == Creating)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, NORTH);
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, SOUTH);
			else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, WEST);
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, EAST);
		}
		else if (gameMode == Wandering)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, FORWARD);
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, BACKWARD);
			else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, LEFT);
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				mainCamera.ProcessKeyboard(deltaTime, RIGHT);

			bool altPressed = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS;
			if (altPressed != GameController::altPressedLast) GameController::updateCursorMode(window, altPressed);
			GameController::altPressedLast = altPressed;
		}
	}

	void GameController::updateCursorMode(GLFWwindow* window, bool bLAltDown)
	{
		if (bLAltDown || GameController::gameMode != Wandering) {
			mouseMode = MouseMode::GUIMode;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			GameController::firstMouse = true;
		}
		else {
			mouseMode = MouseMode::CameraMode;
			glfwSetCursorPos(window, SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}