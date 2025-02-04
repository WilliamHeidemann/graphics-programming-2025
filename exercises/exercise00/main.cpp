#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ituGL/core/DeviceGL.h>
#include <ituGL/application/Window.h>
#include <ituGL/geometry/VertexBufferObject.h>
#include <ituGL/geometry/VertexArrayObject.h>
#include <ituGL/geometry/VertexAttribute.h>
#include <ituGL/geometry/ElementBufferObject.h>

#include <iostream>
#include <valarray>

unsigned int BuildShaderProgram();

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 512;

int main() {
    DeviceGL device;

    // glfw window creation
    // --------------------

    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");

    if (!window.IsValid()) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    device.SetCurrentWindow(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!device.IsReady()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int shaderProgram = BuildShaderProgram();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.0f, // bottom-right
        0.5f, 0.5f, 0.0f, // top-right
        -0.5f, 0.5f, 0.0f // top-left
    };

    constexpr float radius = std::sqrt(2.0f) / 2;
    constexpr float degreesToRadians = 3.141592653589793f / 180.0f;

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VBO, VAO;
    VertexBufferObject vbo;
    VertexArrayObject vao;
    ElementBufferObject ebo;

    constexpr int indicesCount = sizeof(indices) / sizeof(unsigned int);
    constexpr int verticesCount = sizeof(vertices) / sizeof(float);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    vao.Bind();

    vbo.Bind();
    vbo.AllocateData<float>(std::span(vertices, verticesCount));

    ebo.Bind();
    ebo.AllocateData(std::span(indices, indicesCount));


    VertexAttribute position(Data::Type::Float, 3);
    vao.SetAttribute(0, position, 0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // VertexBufferObject::Unbind();

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // VertexArrayObject::Unbind();

    // ElementBufferObject::Unbind();


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    float startAngle = 0.0f;
    while (!window.ShouldClose()) {
        processInput(window.GetInternalWindow());

        // render
        // ------
        device.Clear(0.2f, 0.1f, 0.8f, 1.0f);

        float angle = startAngle * degreesToRadians;
        startAngle += 0.01;

        for (int i = 0; i < verticesCount; i += 3) {
            float x = std::sin(angle) * radius;
            float y = std::cos(angle) * radius;

            vertices[i + 0] = x;
            vertices[i + 1] = y;
            vertices[i + 2] = 0.0f;

            angle += 90.0f * degreesToRadians;
        }

        // angle += 0.001f;
        vbo.UpdateData(std::span(vertices, verticesCount));

        // draw our first triangle
        glUseProgram(shaderProgram);
        vao.Bind();
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.SwapBuffers();
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteProgram(shaderProgram);

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

unsigned int BuildShaderProgram() {
    const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(0.8f, 0.1f, 0.4f, 1.0f);\n"
            "}\n\0";

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
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
