#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
const char *fragmentShaderSourceGreen = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n\0";
const char *fragmentShaderSourceYellow = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
  "}\n\0";

int main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader green
  unsigned int fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
  glCompileShader(fragmentShaderGreen);
  // check for shader compile errors
  glGetShaderiv(fragmentShaderGreen, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShaderGreen, 512, NULL, infoLog);
    std::cout << "ERROR::GREEN::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader yellow
  unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
  glCompileShader(fragmentShaderYellow);
  // check for shader compile errors
  glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
    std::cout << "ERROR::YELLOW::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders 4 green triangle
  unsigned int shaderProgramGreen = glCreateProgram();
  glAttachShader(shaderProgramGreen, vertexShader);
  glAttachShader(shaderProgramGreen, fragmentShaderGreen);
  glLinkProgram(shaderProgramGreen);
  // check for linking errors
  glGetProgramiv(shaderProgramGreen, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgramGreen, 512, NULL, infoLog);
    std::cout << "ERROR::GREEN::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  // link shaders 4 yellow triangle
  unsigned int shaderProgramYellow = glCreateProgram();
  glAttachShader(shaderProgramYellow, vertexShader);
  glAttachShader(shaderProgramYellow, fragmentShaderYellow);
  glLinkProgram(shaderProgramYellow);
  // check for linking errors
  glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
    std::cout << "ERROR::YELLOW::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderGreen);
  glDeleteShader(fragmentShaderYellow);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
  
  // first triangle
  float firstTriangle[] = {
    -0.9f, -0.5f, 0.0f,  // left
    -0.0f, -0.5f, 0.0f,  // right
    -0.45f, 0.5f, 0.0f,  // top
  };
  // second triangle
  float secondTriangle[] = {
    0.0f, -0.5f, 0.0f,  // left
    0.9f, -0.5f, 0.0f,  // right
    0.45f, 0.5f, 0.0f   // top
  };

  unsigned int VBO1, VAO1;
  unsigned int VBO2, VAO2;
  glGenVertexArrays(1, &VAO1);
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO1);
  glGenBuffers(1, &VBO2);

  glBindVertexArray(VAO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramGreen);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO1);
  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO1);
  glDeleteBuffers(1, &VBO2);
  glDeleteProgram(shaderProgramGreen);
  glDeleteProgram(shaderProgramYellow);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
