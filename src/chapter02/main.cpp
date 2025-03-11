#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../common/utils.h"

int main() {
  
  // TODO - fails with segfault err - figure out porque
  // int nrAttributes;
  // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  // std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
  
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
  
  // float timeValue = glfwGetTime();
  // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  // glUseProgram(shaderProgram);
  // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  
  while (!glfwWindowShouldClose(window))
  {
    
  }
}