#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


GLfloat vertices[] =
{
	0.5f, -0.25f, 0.0f, //0
		0.0f, -0.25f, 0.0f, //1
	-0.5f, -0.25f, 0.0f, //2
		-0.25f, 0.25f, 0.0f, //3
	0.0f, 0.75f, 0.0f, //4
		0.25f, 0.25f, 0.0f, //5
}; // the cords x^ Y^ x^

GLuint indices[] =
{
	0, 1, 5,
	1, 2, 3,
	3, 4, 5
};

// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    width = 400;
    height= 400;
    glViewport(0, 0, width*2.25, height*2.25); //custom rezize
}

int main()
{
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 // Tell GLFW we are using the CORE profile
	 // So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
     }
     GLFWwindow* window = glfwCreateWindow(800, 600, "Sky Lands", nullptr, nullptr);
     if (!window) { std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -2;
     }
     glfwMakeContextCurrent(window);
     // Initialize GLAD
     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -3;
    }
	gladLoadGL();
	
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("/home/fly/Downloads/SKY-t5/SKY_LANDS/Shader/default.vert", "/home/fly/Downloads/SKY-t5/SKY_LANDS/Shader/default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(true); //vsync on  

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.02f, 0.13f, 0.23f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();


		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}