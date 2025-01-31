#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// usage: g++ src/main.cpp src/glad.c -o opengl_app -Iinclude -lglfw -lGL

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  
  // render loop
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
    
    // omg - rendering greenish color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // state-setting func
    glClear(GL_COLOR_BUFFER_BIT);           // state-using func
    
    // ----------------------------------
    // 'Vertex input'
    
    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
    };
    
    unsigned int VBO;
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ----------------------------------
    // 'Vertex shader'
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // setup to check if vertex compilation was successfull
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // ----------------------------------
    // stoppet at chapter 'Fragment shader'
    
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }
  
  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame will react accordingly
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
