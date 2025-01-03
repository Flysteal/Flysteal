#include <iostream> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp" 

#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
{
  -0.5, -0.5, 0.0,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 
  -0.5,  0.5, 0.0,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
   0.5,  0.5, 0.0,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
   0.5, -0.5, 0.0,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
   
};// x, y, z, R, G, B,

GLuint indices[] =
{
    0, 2, 1,
    0, 3, 2,

};// .. the wey to go


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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    // this is for shader float value

    //texture
    Texture popCat("/media/fly/o-o/SKY-t5/SKY_LANDS/Resourcefiles/Textures/meme.png",
    GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);




    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(true); //vsync on 
    glViewport(0, 0, height, height); 

    while (!glfwWindowShouldClose(window))
    {

    glClearColor(0.02f, 0.13f, 0.23f, 1.0f); //color

    glClear(GL_COLOR_BUFFER_BIT); // clears buffer

    shaderProgram.Activate();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 proj  = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    glUniform1f(uniID, 0.0f); // float value foe shaders !
    popCat.Bind();
    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //yup

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();    
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}