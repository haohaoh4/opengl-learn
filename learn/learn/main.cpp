#include <glm/glm.hpp>
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
void Init(){
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "GL_MAX_VERTEX_ATTRIBS:: " << nrAttributes << std::endl;
}