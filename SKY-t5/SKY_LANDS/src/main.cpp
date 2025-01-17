#include<iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
      0, 1, 2,
      0, 2, 3,
      0, 4, 7,
      0, 7, 3,
      3, 7, 6,
      3, 6, 2,
      2, 6, 5,
      2, 5, 1,
      1, 5, 4,
      1, 4, 0,
      4, 5, 6,
      4, 6, 7
}; 



int main()
{
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //the version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     // Tell GLFW we are using the CORE profile
     // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;  //check for error
     }
     GLFWwindow* window = glfwCreateWindow(width, height, "Sky Lands", nullptr, nullptr);
     if (!window) { std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //here too
        return -2;
     }
     glfwMakeContextCurrent(window);
     // Initialize GLAD
     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -3; // special one:)
    }
    gladLoadGL();
    glViewport(0, 0, width, height);

    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("../SKY_LANDS/Resourcefiles/Shader/default.vert", "../SKY_LANDS/Resourcefiles/Shader/default.frag");
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    //the other cube
    Shader lightShader("../SKY_LANDS/Resourcefiles/Shader/light.vert", "../SKY_LANDS/Resourcefiles/Shader/light.frag");

    VAO lightVAO;
    lightVAO.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();



    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    //texture
    Texture plank("/media/fly/o-o/GitHub/Flysteal/SKY-t5/SKY_LANDS/Resourcefiles/Textures/planks.png",
    GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    plank.texUnit(shaderProgram, "tex0", 0);

    Texture planksSpec("/media/fly/o-o/GitHub/Flysteal/SKY-t5/SKY_LANDS/Resourcefiles/Textures/planksSpec.png",
    GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.texUnit(shaderProgram, "tex1", 1);

    glfwSwapInterval(true); //vsync on 
    glEnable(GL_DEPTH_TEST);// what is closer then others


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    while (!glfwWindowShouldClose(window))
    {
    
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears buffer

    

    camera.Inputs(window);
	camera.updateMatrix(45.0f, 0.1f, 100.0f);

    shaderProgram.Activate();
    // Exports the camera Position to the Fragment Shader for specular lighting
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    // Export the camMatrix to the Vertex Shader of the pyramid
    camera.Matrix(shaderProgram, "camMatrix");

    plank.Bind();
    planksSpec.Bind();
    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(int), GL_UNSIGNED_INT, 0); //yup


    lightShader.Activate();
    camera.Matrix(lightShader,  "camMatrix");
    lightVAO.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/ sizeof(int), GL_UNSIGNED_INT, 0); //yup



    glfwSwapBuffers(window);
    glfwPollEvents();
    }
    

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    plank.Delete(); 
    planksSpec.Delete();    
    shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}