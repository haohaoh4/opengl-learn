#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
int compile();
double random();
typedef _SYSTEMTIME SYSTEMTIME;
void MainDraw(GLFWwindow* window){
	int shader=compile();
	GLuint VBO;
		glGenBuffers(1,&VBO);
		
		//gen VAO
		 GLfloat vertices[] = {
	       0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	  0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部 
    };
    GLuint  VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 位置属性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
// 颜色属性
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    // Game loop
	int now=0;
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
		now>3?now%=3:now++;
		GLdouble R=now==0?1:0,G=now==1?1:0,B=now==2?1:0;
		GLint vertexColorLocation = glGetUniformLocation(shader, "ourColor");
        glUseProgram(shader);
		glUniform4f(vertexColorLocation,R,G,B,1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	return;
}
double random(){
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	long long a;
	srand(a=sys.wMilliseconds);
	double res=rand()/4000.0;
	int n;
	while(res<=0 || res >=1){
		GetLocalTime( &sys );
		srand(sys.wSecond);
		srand(sys.wMilliseconds+rand());
		srand((((rand()+sys.wMilliseconds<<(rand()%6*123)+45341))<<3)/10);
		if(res>1){
			res-=random();
		}else{
			res+=random();
		}
		n=rand()%500;
		while(n--)
		{
			res+=1;
			glfwPollEvents();
		}
		n=rand()%500;
		while(n--)
		{
			res+=1;
			glfwPollEvents();
		}
	}
	return res;
}