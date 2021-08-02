#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Resources/resourceManager.h"

#include "Renderer/renderer.h"

#include "Game/game.h"

glm::ivec2 g_windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> g_game = std::make_unique<Game>(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	g_windowSize.x = width;
	g_windowSize.y = height;

	const float map_aspect_ratio = 13.f / 14.f;
	unsigned viewPortWidth = g_windowSize.x;
	unsigned viewPortHeight = g_windowSize.y;
	unsigned viewPortLeftOffset = 0;
	unsigned viewPortBottomOffset = 0;

	if (g_windowSize.x / g_windowSize.y > map_aspect_ratio)
	{
		viewPortWidth = static_cast<unsigned>(g_windowSize.y * map_aspect_ratio);
		viewPortLeftOffset = (g_windowSize.x - viewPortWidth) / 2;
	}
	else
	{
		viewPortHeight = static_cast<unsigned>(g_windowSize.x / map_aspect_ratio);
		viewPortBottomOffset = (g_windowSize.y - viewPortHeight) / 2;
	}

	RenderEngine::Renderer::setViewPort(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}

	g_game->setKey(key, action);
}

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "glfwInit error!!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//openGL minimum version for start program
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "glfwCreateWindow failed!\n";
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	glfwMakeContextCurrent(pWindow);//all function on this window

	if (!gladLoadGL())
	{
		std::cout << "gladLoadGL failed!\n";
		return -1;
	}
	std::cout << "Renderer: " << RenderEngine::Renderer::getRendererString() << std::endl;
	std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionString() << std::endl;

	RenderEngine::Renderer::setClearColor(0, 0, 0, 1);

	ResourceManager::setExecutablePath(argv[0]);
	g_game->init();
	auto lastTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();
		
		auto currentTime = std::chrono::high_resolution_clock::now();
		uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
		lastTime = currentTime;
		g_game->update(duration);

		RenderEngine::Renderer::clear();

		g_game->render();

		glfwSwapBuffers(pWindow);

	}
	g_game = nullptr;
	ResourceManager::unloadAllResources();
	glfwTerminate();
	return 0;
}
