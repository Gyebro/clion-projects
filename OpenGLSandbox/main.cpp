#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace std;

/*** Classes ***/

const size_t NUM_BUFFERS = 1;
const size_t POSITION_VB = 0;

class Vertex {
private:
    glm::vec3 mCoords;
public:
    Vertex(glm::vec3 coords) : mCoords(coords) {};
};

class Mesh {
private:
    GLuint m_vertexArrayObject;
    char m_flag;
    unsigned int m_drawCount;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
public:
    Mesh(Vertex* vertices, unsigned int numVertices, const char& flag) : m_flag(flag), m_drawCount(numVertices) {
        glGenVertexArrays(1, &m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);
    }
    void draw() {
        switch (m_flag) {
            case 'P':
                glBindVertexArray(m_vertexArrayObject);
                glDrawArrays(GL_POINTS, 0, m_drawCount);
                glBindVertexArray(0);
                break;
            case 'L':
                glBindVertexArray(m_vertexArrayObject);
                glDrawArrays(GL_LINES, 0, m_drawCount);
                glBindVertexArray(0);
                break;
            case 'T':
                glBindVertexArray(m_vertexArrayObject);
                glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
                glBindVertexArray(0);
                break;
        }
    }
};

/*** End of classes ***/

int mWidth = 1024;
int mHeight = 768;

vector<Mesh> meshes;

static void error_callback(int error, const char* description) {
    cout << "Error: " << description << endl;
}

void drawScene(void) {
    for (int i(0); i < meshes.size(); ++i )
        meshes[i].draw();
}

void setupScene(void) {
    Vertex vertices1[] = {
        Vertex(glm::vec3(-.5, -.5, 0)),
        Vertex(glm::vec3(  0,  .5, 0))
    };
    Vertex vertices2[] = {
        Vertex(glm::vec3(  .5, -.5, 0)),
        Vertex(glm::vec3( -.5,  .5, 0))
    };
    Mesh mesh1(vertices1, sizeof(vertices1)/sizeof(vertices1[0]), 'L');
    Mesh mesh2(vertices2, sizeof(vertices2)/sizeof(vertices2[0]), 'L');
    meshes.push_back(mesh1);
    meshes.push_back(mesh2);
}

int display(void) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(mWidth, mHeight, "OpenGL Sandbox", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    // Set up scene and shaders
    setupScene();
    glfwGetFramebufferSize(window, &mWidth, &mHeight);
    glViewport(0, 0, mWidth, mHeight);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw here
        drawScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int main() {
    cout << "Starting OpenGL Sandbox..." << endl;
    display();
    return 0;
}