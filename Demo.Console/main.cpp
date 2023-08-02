//#include <iostream>
//#include <vector>
#include <GLFW/glfw3.h>
//
//#include "CopyingAndCopyConstructors.h"

//struct Vertex
//{
//    float x, y, z;
//
//    Vertex(const float x, const float y, const float z)
//	    : x(x), y(y), z(z)
//    {
//	    
//    }
//
//    Vertex(const Vertex& vertex)
//	    : x(vertex.x), y(vertex.y), z(vertex.z)
//    {
//        std::cout << "Copied!" << std::endl;
//    }
//};

int main()
{
    //CopyingAndCopyConstructors();

    //std::vector<Vertex> vertices;
    //vertices.reserve(3);
    //vertices.emplace_back(1, 2, 3);
    //vertices.emplace_back(4, 5, 6);
    //vertices.emplace_back(7, 8, 9);
    //vertices.emplace_back(7, 8, 9);
    //vertices.emplace_back(7, 8, 9);
    //std::cin.get();


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
