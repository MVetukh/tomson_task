//
// Created by Max on 12.09.2024.
//

#ifndef TOMSON_TASK_RENDERER_H
#define TOMSON_TASK_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"



// Класс для работы с OpenGL и отрисовкой
class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(int width, int height, const char* title);
    void render(const std::vector<std::array<double, 3>>& points);
    void cleanup();

private:
    void init_shaders();
    void init_points(const std::vector<std::array<double, 3>>& points);
    void process_input();
    void update_view_matrix();

    // OpenGL ресурсы
    GLFWwindow* window;
    GLuint VBO, VAO, shaderProgram;

    // Управление камерой
    float pitch, yaw;
    float lastX, lastY;
    bool firstMouse;
    float radius;  // радиус для вращения вокруг сферы
    glm::vec3 cameraPos, cameraUp;

    // Математические данные для проекции и вида
    glm::mat4 view;
    glm::mat4 projection;
};

#endif // TOMSON_TASK_RENDERER_H


