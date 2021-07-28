#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>


#include <GL/glew.h>
#include <GL/gl.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project Headers
#include "shader.h"
#include "utils.h"
#include "geometry.h"
#include "image.h"
#include "camera.h"

// Camera
Camera *camera;

// Generate a uniformly distributed random number
// float uniform() {
//     return rand()/(float)RAND_MAX;
// }

// Generate poisson-distributed random number (limited)
float poisson(float gamma, float limit) {
    float l = exp(-gamma);
    float k = 0;
    float p = 1;

    do {
        k = k + 1;
        float u = uniform();
        p = p * u;
    } while(p > l && k < limit);

    return (k - 1);
}

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

// Called on Error Event
void onError(int error, const char *description) {
    // Print Error message
    std::cerr << "Error: " << error << " : " << description << std::endl;
}

// Called on Window Close Event
void onWindowClose(GLFWwindow *window) {
    // Nothing to do right now
    // Do not call glfwDestroyWindow from here
}

// Called on Window Size Event
void onFramebufferSize(GLFWwindow *window, int width, int height) {
    // Set-up the window/screen coordinates
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(NULL);
}

// --------------------------------------------------------------------------------
// Keyboard Input
// --------------------------------------------------------------------------------
bool lines = false;
void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Check Input Key - L
    if((key == GLFW_KEY_L) && (action == GLFW_PRESS)) {
        if(lines == true) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        lines = !lines;
    }
}

// --------------------------------------------------------------------------------
// Mouse Input
// --------------------------------------------------------------------------------
void onMouseButton(GLFWwindow *window, int button, int action, int mods) {
    // Update Camera
    camera->onMouseButton(window, button, action, mods);
}

void onCursorPosition(GLFWwindow *window, double x, double y) {
    // Update Camera
    camera->onCursorPosition(window, x, y);
}

void set_river(GLuint pid, GLuint &vao, GLuint &vbo, GLuint &tbo, GLuint &ebo, GLuint &numIndex) {
    glUseProgram(pid);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(glGetAttribLocation(pid, "vert_Position"), 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(glGetAttribLocation(pid, "vert_Normal"),   4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glEnableVertexAttribArray(glGetAttribLocation(pid, "vert_Position"));
    glEnableVertexAttribArray(glGetAttribLocation(pid, "vert_Normal"));

    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec3> indexes;

    // Create River
    createRiver(buffer, indexes);

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    numIndex = indexes.size();

    // uvmap
    std::vector<glm::vec2> uv;
    uv.push_back(glm::vec2( 0.0f, 1.0f));
    uv.push_back(glm::vec2( 1.0f, 1.0f));
    uv.push_back(glm::vec2( 1.0f, 0.0f));
    uv.push_back(glm::vec2( 0.0f, 0.0f));
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(pid, "tex_UV"),   2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(glGetAttribLocation(pid, "tex_UV"));
}

// Tessellation Parameters
float tessLevelInner1 = 1.0f;
float tessLevelInner2 = 1.0f;
float tessLevelOuter1 = 1.0f;
float tessLevelOuter2 = 1.0f;
float tessLevelOuter3 = 1.0f;
float tessLevelOuter4 = 1.0f;

int DSX = pow(2, 10) + 1;
int DSY = pow(2, 10) + 1;
void set_terrain(GLuint pid, GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint &numIndex, GLuint &height_map, GLuint &normal_map) {
    glUseProgram(pid);

    int P = 10;
    // int DSX = pow(2, P) + 1;
    // int DSY = pow(2, P) + 1;

    int X = DSX - 1;
    int Y = DSY - 1;
    float height_scale = 1.5f;

    // float *height = DiamondSquare(DSX, DSY);
    // glm::vec3 *normals = generateNormals(height, height_scale, DSX, DSY);

    unsigned char *normal_data = new unsigned char[X*Y*4];

    float *height_data = new float[X*Y];

    // for(int iy = 0; iy < Y; iy++) {
    //     for(int ix = 0; ix < X; ix++) {
    //         height_data[iy*X  + ix] = height[iy*DSX + ix];
    //         height_data[iy*X  + ix] *= 0.7;
    //         // float tmpy = iy - .5 * Y;
    //         // float tmpx = ix - .5 * X;
    //         // if (tmpy < 0) tmpy = -tmpy;
    //         // if (tmpx < 0) tmpx = -tmpx;
    //         // if (tmpy * 40.0 < Y && tmpx * 5.0 < X)
    //         //     height_data[iy*X  + ix] = 0.2;
    //         // else if (tmpy * 10.0 <  Y && tmpx * 5.0 < X)
    //         //     height_data[iy*X  + ix] *= (tmpy * 10)/Y;// * (tmpy * 10)/Y;// + 0.5;

    //     }
    // }

    // for(int iy = 0; iy < Y; iy++) {
    //     for(int ix = 0; ix < X; ix++) {
    //         normal_data[(iy*X  + ix) * 4 + 0] = (unsigned char)((normals[iy*DSX + ix].x + 1.0f) * 127.5);
    //         normal_data[(iy*X  + ix) * 4 + 1] = (unsigned char)((normals[iy*DSX + ix].y + 1.0f) * 127.5);
    //         normal_data[(iy*X  + ix) * 4 + 2] = (unsigned char)((normals[iy*DSX + ix].z + 1.0f) * 127.5);
    //         normal_data[(iy*X  + ix) * 4 + 3] = 0.0f;
    //     }
    // }



    // std::ofstream fout("height_map.txt");
    // for (int i = 0; i < X*Y; i++) fout << height_data[i] << std::endl;
    // fout.close();

    // std::ofstream fout1("normal_map.txt");
    // for (int i = 0; i < X*Y*4; i++) { fout1 << (unsigned short)normal_data[i] << std::endl; if (i < 5) std::cout << normal_data[i] <<std::endl; }
    // fout1.close();

    // read
    std::ifstream fin("height_map.txt");
    for (int i = 0; i < X*Y; i++) fin >> height_data[i];
    fin.close();

    unsigned short ch;
    std::ifstream fin1("normal_map.txt");
    for (int i = 0; i < X*Y*4; i++) { fin1 >> ch; normal_data[i] = ch; if (i < 5) std::cout << normal_data[i] <<std::endl; }
    fin1.close();


    height_map = createTexture2D(height_data, X, Y, 1, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    normal_map = createTexture2D(normal_data, X, Y, 4, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    // Set Height Scale
    glUniform1f(glGetUniformLocation(pid, "u_Height_Scale"), height_scale);
    // Bind VAO, VBO & EBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Get Position Attribute location (must match name in shader)
    GLuint posLoc = glGetAttribLocation(pid, "vert_Position");

    // Get Texture Attribute location (must match name in shader)
    GLuint texLoc = glGetAttribLocation(pid, "vert_Texture");

    // Set Vertex Attribute Pointers
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));

    // Enable Vertex Attribute Arrays
    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(texLoc);

    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec4> indexes;

    // Create Quadrangle
    //createQuads(buffer, indexes, 15, 15);
    createQuads(buffer, indexes, 55, 55);

    // Load Vertex Data
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

    // Load Element Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec4), indexes.data(), GL_STATIC_DRAW);

    numIndex = indexes.size();
}

void set_blade(GLuint pid, GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint &numIndex,
    std::vector<glm::mat4> &grassModelMatrixes, int &numObjects) {
    glUseProgram(pid);

    // ----------------------------------------
    // Vertex Stream - Ground
    // ----------------------------------------

    // Bind VAO, VBO & EBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Use Program
    glUseProgram(pid);

    // Set Vertex Attribute Pointers
    glVertexAttribPointer(glGetAttribLocation(pid, "vert_Position"), 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(glGetAttribLocation(pid, "vert_Normal"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(glGetAttribLocation(pid, "vert_Colour"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
    glEnableVertexAttribArray(glGetAttribLocation(pid, "vert_Position"));
    glEnableVertexAttribArray(glGetAttribLocation(pid, "vert_Normal"));
    glEnableVertexAttribArray(glGetAttribLocation(pid, "vert_Colour"));

    // Vertex and Index buffers (host)
    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec3> indexes;

    createBlade(buffer, indexes);

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    numIndex = indexes.size();

    int X = DSX - 1;
    int Y = DSY - 1;
    float *height_data = new float[X*Y];
    std::ifstream fin("height_map.txt");
    for (int i = 0; i < X*Y; i++) fin >> height_data[i];
    fin.close();

    //const int N = 10;
    const int N = 1500;
    const int grassX = N;
    const int grassZ = N;
    numObjects = grassX * grassZ;

    int halfX = grassX / 2;
    int halfZ = grassZ / 2;
    // float sX = 2.0 / grassX;
    float sX = 20.0 / grassX;
    float sZ = 20.0 / grassZ;

    glm::vec3 *shift = new glm::vec3[numObjects];
    float *theta = new float[numObjects];
    float *alpha = new float[numObjects];
    float *scale = new float[numObjects];
    float *movement = new float[numObjects];
    glm::vec3 *axis = new glm::vec3[numObjects];

    // Model Matrix

    // Grid
    int k = 0;
    for(int iz = -halfZ; iz < halfZ; iz++) {
        for(int ix = -halfX; ix < halfX; ix++) {
            // map to height map
            int hmx = X * (ix + halfX) / grassX;
            int hmy = Y * (grassZ - iz - halfZ) / grassZ;
            //printf("idx: %d %d %f\n", hmx, hmy, height_data[hmy*X  + hmx]);
            float zzz = height_data[hmy*X  + hmx] * 1.5f * 10.0f;

            if (zzz > 9 || zzz < 7) continue;

            // Random Position
            // shift[k]    = glm::vec3((ix + 0.25 + uniform()*0.5) * sX, 0.0f, (iz + 0.25 + uniform()*0.5) * sZ);
            shift[k]    = glm::vec3((ix + 0.25 + uniform()*0.5) * sX, zzz, (iz + 0.25 + uniform()*0.5) * sZ);

            // Random Angle
            // alpha[k]    = 0.0f;
            alpha[k]    = uniform() * glm::pi<float>() * 2.0f;
            theta[k]    = 0.0f;
            // theta[k]    = uniform() * glm::pi<float>() / 3.0f;
            axis[k]     = glm::normalize(glm::vec3(uniform() * 2.0 - 1.0f, uniform() * 2.0 - 1.0f, uniform() * 2.0 - 1.0f));;

            // Random Scale
            // scale[k] = 0.005;
            // scale[k]    = (uniform() * 0.5 + 0.5) * 0.0075;
            scale[k]    = (poisson(5, 100)) * 0.005 / 5;

            // Movement (wind)
            movement[k] = 0.0f;
            // movement[k] = uniform() * 0.05 + 0.01;

            // Individual Blade Transform
            grassModelMatrixes.push_back(glm::translate(glm::mat4(1.0f), shift[k]) *
                                         glm::rotate(   glm::mat4(1.0f), (float)(sin(glfwGetTime()*4.0f + ix/20.0f)*movement[k]), glm::vec3(0,0,1)) *
                                         glm::rotate   (glm::mat4(1.0f), theta[k], axis[k]) *
                                         glm::rotate   (glm::mat4(1.0f), alpha[k], glm::vec3(0, 1, 0)) *
                                         glm::scale    (glm::mat4(1.0f), glm::vec3(scale[k], scale[k], scale[k])) *// )
                                         glm::scale    (glm::mat4(1.0f), glm::vec3(0.3, 0.3, 0.3)) );
            //glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, zzz, 0.0f)));
            //++k;
        }
    } numObjects = grassModelMatrixes.size();

    GLuint ibo;
    glGenBuffers(1, &ibo);

    // Bind buffer object
    glBindBuffer(GL_ARRAY_BUFFER, ibo);

    // Buffer Model Matrix Data
    glBufferData(GL_ARRAY_BUFFER, numObjects * sizeof(glm::mat4), glm::value_ptr(grassModelMatrixes[0]), GL_STATIC_DRAW);

    // Set Attribute Pointers
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 0*sizeof(float)));
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 4*sizeof(float)));
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 8*sizeof(float)));
    glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(12*sizeof(float)));

    // Enable Attribute Arrays
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);
    glEnableVertexAttribArray(8);
    glEnableVertexAttribArray(9);

    // Set Attribute Divisors (one per instance)
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);
    glVertexAttribDivisor(9, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_grass(GLuint pid, GLuint vao,
                glm::mat4 viewMatrix, int numIndex, glm::mat4 grassGlobalMat,
                int numObjects) {

    glUseProgram(pid);
    glUniformMatrix4fv(glGetUniformLocation(pid, "u_View"),  1, GL_FALSE, glm::value_ptr(viewMatrix));
    // Bind Vertex Array Object
    glBindVertexArray(vao);

    glUniformMatrix4fv(glGetUniformLocation(pid, "g_Matrix"),  1, GL_FALSE, glm::value_ptr(grassGlobalMat));
    // Draw Elements (Triangles)
    glDrawElementsInstanced(GL_TRIANGLES, numIndex * 3, GL_UNSIGNED_INT, NULL, numObjects);
}

void draw_terrain(GLuint pid, GLuint vao, GLuint height_map, GLuint normal_map,
                   glm::mat4 modelMatrix, glm::mat4 viewMatrix, int numIndex) {

    glUseProgram(pid);
    // Copy Model Matrix to Shader
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUniformMatrix4fv(glGetUniformLocation(pid,        "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(pid,        "u_View"),  1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(pid,        "u_IView"), 1, GL_FALSE, glm::value_ptr(glm::inverse(viewMatrix)));
    // ----------------------------------------
    // Update Tessellation Parameters
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelInner1"), tessLevelInner1);
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelInner2"), tessLevelInner2);
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelOuter1"), tessLevelOuter1);
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelOuter2"), tessLevelOuter2);
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelOuter3"), tessLevelOuter3);
    glUniform1f(glGetUniformLocation(pid, "u_TessLevelOuter4"), tessLevelOuter4);

    // Update Time
    glUniform1f(glGetUniformLocation(pid, "u_time"), glfwGetTime());

    // ----------------------------------------
    // Draw Object
    // ----------------------------------------
    // Use Program

    // Bind Vertex Array Object
    glBindVertexArray(vao);

    // Set Texture Units
    glUniform1i(glGetUniformLocation(pid, "u_Height_Map"),  0);

    // Activate Texture Unit 0
    glActiveTexture(GL_TEXTURE0);

    // Bind Texture Map
    glBindTexture(GL_TEXTURE_2D, height_map);

    // Set Texture Units
    glUniform1i(glGetUniformLocation(pid, "u_Normal_Map"),  1);

    // Activate Texture Unit 1
    glActiveTexture(GL_TEXTURE1);

    // Bind Texture Map
    glBindTexture(GL_TEXTURE_2D, normal_map);

    // ----------------------------------------
    // Draw Quadrangles
    // ----------------------------------------
    // Configure Patches
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    // Draw Elements (Patches)
    glDrawElements(GL_PATCHES, numIndex * 4, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


int main() {
    // Set Error Callback
    glfwSetErrorCallback(onError);

    // Initialise GLFW
    if (!glfwInit()) {
        // Return Error
        return 1;
    }


    // Window Size
    int window_width = 600;
    int window_height = 600;

    // Create Window
    GLFWwindow *window = createWindow(600, 600, "River", 3, 3);

    // Check Window
    if (window == NULL) {
        // Print Error Message
        std::cerr << "Error: create window or context failed." << std::endl;

        // Return Error
        return 1;
    }

#if defined(_WIN32) || defined(__linux__)
    // Initialise GLEW
    if (glewInit() != GLEW_OK) {
        // Return Error
        return 1;
    }
#endif
    // Set window callback functions
    glfwSetFramebufferSizeCallback(window, onFramebufferSize);
    glfwSetWindowCloseCallback(window, onWindowClose);

    // Set mouse input callback functions
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCursorPosCallback(window, onCursorPosition);

    // Set keyboard input callback functions
    glfwSetKeyCallback(window, onKey);

    // ----------------------------------------
    // Initialise OpenGL
    // ----------------------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    // Get Maximum Anistropic level
    GLfloat maxAnistropy = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnistropy);

    // Enable Anistropic Filtering
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnistropy);

    int maxVertexUniformComponents;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformComponents);

    std::cout << "Max Vertex Uniform Components: " << maxVertexUniformComponents << std::endl;

    // ----------------------------------------
    // Camera
    // ----------------------------------------
    camera = new GimbalFreeLookCamera(window, glm::vec3(6.0f, 2.0f, -1.4f), glm::quat(1.0, -0.0, 0.0, 0.0));

    // ----------------------------------------
    // Create GLSL Program and VAOs, VBOs
    // ----------------------------------------

    GLuint grassProgram  = loadProgram("./shader/grass.vert.glsl", NULL, NULL, NULL,
                                       "./shader/grass.frag.glsl");
    GLuint riverProgram  = loadProgram("./shader/river.vert.glsl", NULL, NULL, NULL,
                                       "./shader/river.frag.glsl");

    GLuint terrainProgram = loadProgram("./shader/tessellation.vert.glsl",
                                        "./shader/tessellation.ctrl.glsl",
                                        "./shader/tessellation.eval.glsl",
                                        NULL,
                                        "./shader/tessellation.frag.glsl");


    // ----------------------------------------
    // Vertex Array Objects
    // ----------------------------------------
    // Vertex Array Objects (VAO)
    GLuint vao[3];
    GLuint vbo[3];
    GLuint ebo[3];
    GLuint tbo;
    GLuint numIndexes[3];

    // Create VAO, VBO & EBO
    glGenVertexArrays(3, vao);
    glGenBuffers(3, vbo);
    glGenBuffers(1, &tbo);
    glGenBuffers(3, ebo);


    std::vector<glm::mat4> grassModelMatrixes;
    int numObjects;
    set_blade(grassProgram, vao[0], vbo[0], ebo[0], numIndexes[0], grassModelMatrixes, numObjects);
    glUseProgram(grassProgram);

    glm::mat4 grassGlobalMat2 = glm::mat4(1.0f);
    // glm::mat4 grassGlobalMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(2.0f, 2.0f, -1.7f)) * //;
    //                              glm::scale    (glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
    glm::mat4 grassGlobalMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(-0.0f, -8.0f, 0.0f));
    //glm::mat4 grassGlobalMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(-5.0f, 2.0f, 5.0f));


    set_river(riverProgram, vao[1], vbo[1], tbo, ebo[1], numIndexes[1]);
    // glm::mat4 riverModelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 1.9f, 0.0f)) *
    //                             glm::scale    (glm::mat4(1.0f), glm::vec3(10.0, 10.0, 10.0));
    glm::mat4 riverModelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(2.3f, 0.0f, -4.1f)) *
                                glm::scale    (glm::mat4(1.0f), glm::vec3(5.0, 5.0, 5.0));
    // glm::mat4 riverModelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 1.3f, 0.0f)) *
    //                             glm::scale    (glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));

    GLuint height_map, normal_map;
    set_terrain(terrainProgram, vao[2], vbo[2], ebo[2], numIndexes[2], height_map, normal_map);
    float modelThetaX =  0.0f;
    float modelThetaY =  0.0f;
    glm::mat4 terrainModelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 2.10f, 0.0f)) *
                                   glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) *
                                   glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f)) *
                                   glm::scale    (glm::mat4(1.0f), glm::vec3(10.0, 10.0, 10.0));
                                   //glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 27.0f, 0.0f));

    // Unbind VAO, VBO & EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glm::mat4 projectionMatrix;
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 5000000.0f);

    glUseProgram(grassProgram);
    glUniformMatrix4fv(glGetUniformLocation(grassProgram,  "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(grassProgram,  "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUseProgram(riverProgram);
    glUniformMatrix4fv(glGetUniformLocation(riverProgram,  "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(riverProgram,  "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUseProgram(terrainProgram);
    glUniformMatrix4fv(glGetUniformLocation(terrainProgram,  "u_View"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(terrainProgram,  "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));



    // ---------------------------------------
    // Set frame buffer to get river reflection
    // ---------------------------------------
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);


    unsigned int texReflect;
    glGenTextures(1, &texReflect);

    glBindTexture(GL_TEXTURE_2D, texReflect);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texReflect, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum attachments[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, attachments);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);




    // ----------------------------------------
    // Main Render loop
    // ----------------------------------------
    float time = glfwGetTime();
    float total = 0.0f;
    int frame_count = 0;


    glViewport(0, 0, 600, 600);
    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Make the context of the given window current on the calling thread
        glfwMakeContextCurrent(window);

        // Set clear (background) colour to black
        glClearColor(0.4f, 0.4f, 0.8f, 0.0f);

        // Clear Screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update Time
        float current_time = glfwGetTime();
        float dt = current_time - time;
        time = current_time;

        // Frames Per Second Counter
        total += dt;
        frame_count++;
        if(total >= 1.0f) {
            total = 0.0f;
            std::cout << "fps: " << frame_count << std::endl;
            frame_count = 0;
        }
        // ----------------------------------------
        // Update Camera
        // ----------------------------------------
        camera->update(dt);

        glm::vec4 camera_Position = camera->getPosition();

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glEnable(GL_CLIP_DISTANCE0);

        glClearColor(0.2f, 0.4f, 0.6f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float rHeight = .1f;
        glm::vec3 cPos = camera->getPosition();
        glm::vec3 rPos = glm::vec3(cPos.x, rHeight, cPos.z);
        glm::vec3 rNormal = glm::vec3(0, 1, 0);
        glm::mat4 reflectViewMatrix = camera->getReflectedViewMatrix(rPos, rNormal);

        draw_terrain(terrainProgram, vao[2], height_map, normal_map,
                      terrainModelMatrix, reflectViewMatrix, numIndexes[2]);

        // draw_grass(grassProgram, vao[0],
        //            reflectViewMatrix, numIndexes[0], grassGlobalMatrix,
        //            numObjects);

        // draw_grass(grassProgram, vao[0],
        //                 reflectViewMatrix, numIndexes[0], grassGlobalMat1,
        //                 numObjects);
        // draw_grass(grassProgram, vao[0],
        //            reflectViewMatrix, numIndexes[0], grassGlobalMat2,
        //            numObjects);

        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_CLIP_DISTANCE0);


        glClearColor(0.2f, 0.4f, 0.6f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        draw_terrain(terrainProgram, vao[2], height_map, normal_map,
                      terrainModelMatrix, camera->getViewMatrix(), numIndexes[2]);

        // Grass - Instanced - Instance Attributes
        // draw_grass(grassProgram, vao[0],
        //            camera->getViewMatrix(), numIndexes[0], grassGlobalMat1,
        //            numObjects);
        // draw_grass(grassProgram, vao[0],
        //            camera->getViewMatrix(), numIndexes[0], grassGlobalMat2,
        //            numObjects);
        draw_grass(grassProgram, vao[0],
                   camera->getViewMatrix(), numIndexes[0], grassGlobalMatrix,
                   numObjects);

        // Draw River
        glUseProgram(riverProgram);
        glUniform1f(glGetUniformLocation(riverProgram, "time"), time);
        glUniformMatrix4fv(glGetUniformLocation(riverProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(riverModelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(riverProgram,  "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(riverProgram,  "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(glGetUniformLocation(riverProgram, "r_View"),  1, GL_FALSE, glm::value_ptr(reflectViewMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texReflect);
        glUniform1i(glGetUniformLocation(riverProgram, "u_Reflection_Map"), 0);
        glUniform4fv(glGetUniformLocation(riverProgram, "camera_Position"), 1,
                     glm::value_ptr(camera_Position));

        glBindVertexArray(vao[1]);
        glDrawElements(GL_TRIANGLES, numIndexes[1] * 3, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);


        // ----------------------------------------
        // Swap the back and front buffers
        glfwSwapBuffers(window);

        // Poll window events
        glfwPollEvents();
    }

    // Delete VAO, VBO & EBO
    glDeleteVertexArrays(3, vao);
    glDeleteBuffers(3, vbo);
    glDeleteBuffers(3, ebo);

    // Delete Program
    glDeleteProgram(grassProgram);
    glDeleteProgram(riverProgram);
    glDeleteProgram(terrainProgram);

    // Stop receiving events for the window and free resources; this must be
    // called from the main thread and should not be invoked from a callback
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
