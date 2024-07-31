OpenGL is a **specification** that defines what the output should look like, so that users of different machines get the same results. OpenGL is implemented by graphic cards manufactures that write the actual code/libraries.

OpenGL 3.3 and newer versions are called **core-profile mode**. It is efficient because gives developers so much more control over how OpenGL works internally. That's why we have to truly learn OpenGL to use it effectively. Version 3.2 and older were called **immediate mode** which is just an abstraction of the internal functions, and therefore really easy to use.

OpenGL supports extensions. When developers find a better and more optimized way of doing something, they release it via an **extension**. Popular extensions are often integrated into the next version of OpenGL. 

OpenGL is a big **state machine**. We constantly change its **state** (collection of internal variables), also known as **context**

The way we set context is by using **objects**. Related state of OpenGL is grouped in objects.
First, we create an object and give it an id reference. Then, we bind that object to the OpenGL context. Then we set the object's values. Finally, after we're done, we unbind the object.
```c++
// create object
unsigned int objectId = 0;
glGenObject(1, &objectId);
// bind/assign object to context
glBindObject(GL_WINDOW_TARGET, objectId);
// set options of object currently bound to GL_WINDOW_TARGET
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);
```

We need a context and a window to render in. However, these are operating system specific, and we use a library named **GLFW** to take care of it for us.
OpenGL is only a specification and the location of the functions isn't known at compile time. So another thing we need is to retrieve the location of the OpenGL functions. Doing this manually is a lot of work, so we use a library for this named **GLAD**.

First, we initialize GLFW.
```C++
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// callback function headers
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap front and back buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
```

Callback functions are custom called when certain event's are triggered. We can bind callback functions to GLFW functions.

Shaders are small programs that run on the GPU at every step of the graphics pipe line. 
Some of these steps, shown in cyan below, allow us to inject our own shaders.

```tikz 
\begin{document} 
\begin{tikzpicture}[node distance={50mm}, very thick, main/.style={draw, circle}, every node/.style={scale=1}] 

\node[main, fill=cyan] (1) {vertex Shader}; 
\node[main, fill=cyan] [right of=1](2) {geometry shader};
\node[main] [right of=2](3) {shape assembly};
\node[main] [below of=3](4) {rasterization};
\node[main, fill=cyan] [left of=4](5) {fragment shader};
\node[main] [left of=5](6) {testing and blending};

\draw[->] (1) to (2);
\draw[->] (2) to (3);
\draw[->] (3) to (4);
\draw[->] (4) to (5);
\draw[->] (5) to (6);

\end{tikzpicture} 
\end{document}
```

We must define the vertex and fragment shaders at the very least.
GPUs are good at performing similar tasks in parallel.
First, we need to give vertex data as input to the pipeline. Vertices are normalized $xyz$ coordinates (ranging from -1 to 1) and a color value.
It's relatively slow to send data from the CPU to GPU. So we stuff as much vertex data as possible in a vertex buffer object and send it to the built in GPU memory.


### GLM
Open**GL** **M**athematics **L**ibrary
