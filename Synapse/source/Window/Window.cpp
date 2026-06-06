#include "Window.h"

Window::Window()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //Width = mode->width;
    //Height = mode->height;


    // Window Creation
    window = glfwCreateWindow(Width, Height, "Synapse", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetWindowPos(window, 1400, 400);

    glfwMakeContextCurrent(window);

    // GLAD Initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // Viewport Size 
    glViewport(0, 0, Width, Height);

    // Resize Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetWindowUserPointer(window, this);
    

}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    instance->Width = width;
    instance->Height = height;
    glViewport(0, 0, width, height);
}