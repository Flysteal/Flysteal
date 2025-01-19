#include "Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{

    if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;  //check for error
     }
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //the version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     // Tell GLFW we are using the CORE profile
     // So that means we only have the modern functions
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     GLFWwindow* window = glfwCreateWindow(width, height, "Sky Lands", NULL, NULL);

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



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("/media/fly/o-o/GitHub/Flysteal/SKY-t5/SKY_LANDS/Resourcefiles/Shader/default.vert",  "/media/fly/o-o/GitHub/Flysteal/SKY-t5/SKY_LANDS/Resourcefiles/Shader/default.frag");

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);



	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    

    glfwSwapInterval(true); //vsync on 
    glEnable(GL_DEPTH_TEST);// what is closer then others


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));



	
	// Load in a model
	Model model("/media/fly/o-o/GitHub/Flysteal/SKY-t5/SKY_LANDS/Resourcefiles/models/Islands/island1.gltf");

    while (!glfwWindowShouldClose(window))
    {
    
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears buffer

    	camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

	    // Draw a model
		model.Draw(shaderProgram, camera);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
    }
    

    // Delete all the objects we've created
   
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}