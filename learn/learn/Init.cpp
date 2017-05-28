#include<head.hpp>
#include <iostream>
void MainDraw(GLFWwindow*);
void Init();
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
	  std::cout << "Failed to create GLFW window" << std::endl;
	  glfwTerminate();
	  return -1;
	}
	glfwMakeContextCurrent(window);
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	   std::cout << "Failed to initialize GLEW" << std::endl;
	   return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	Init();
	MainDraw(window);
    return 0;
}