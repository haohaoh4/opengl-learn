#pragma once
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>
const GLchar *vertex_shader_s=
	"#version 330 core\n"
	"layout(location=0)in vec4 pos;"
	"layout (location = 1) in vec3 color; "
	"out vec3 ourColor;"
	"void main(){"
	"gl_Position=vec4(pos.x,pos.y,pos.z,1.0);"
	"ourColor=color;"
	"}";
const GLchar *fra_shader_s=
	"#version 330 core\n"
	"in vec3 ourColor;"
	"out vec4 color;"
	"	void main()"
	"{"
	"color = vec4(ourColor, 1.0f);"
	"}";
int compile(){
	GLuint shader;
	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader,1,&vertex_shader_s,NULL);
	glCompileShader(shader);

	//is it ok?
	GLint OK;
	GLchar info[512];
	glGetShaderiv(shader,GL_COMPILE_STATUS,&OK);
	if(!OK){
		glGetShaderInfoLog(shader,512,NULL,info);
		std::cout<<"ERROR::SHADER_VERTEX::COM_FAIL\n"<<info<<std::endl;
		return false;
	}
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fra_shader_s, NULL);
	glCompileShader(fragmentShader);

	//is it ok?
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&OK);
	if(!OK){
		glGetShaderInfoLog(fragmentShader,512,NULL,info);
		std::cout<<"ERROR::SHADER_FRAGMENT::COM_FAIL\n"<<info<<std::endl;
		return 0;
	}
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(shader);
    glDeleteShader(fragmentShader);
	return shaderProgram;
}