
#include "glad.h"
#include <GLFW/glfw3.h>

#include "scene.h"
#include "state.h"
#include "camera.h"
#include "camera2d.h"
#include "color.h"
#include "transform.h"
#include "error.h"
#include "shader.h"
#include "disk.h"
#include "engine.h"
#include "triangle.h"
#include "texture.h"
#include "rectangle.h"

#include <iostream>

static CameraPtr camera;
static ScenePtr scene;

static void initialize(void)
{
    // background color: almost black
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // create objects
    camera = Camera::Make(0, 10, 0, 10);

    // background
    AppearancePtr backgroundTexture = Texture::Make("sampler", "galaxy.png");
    Error::Check("Texture::Make(sampler, galaxy.jpg)");
    auto trfBackground = Transform::Make();
    trfBackground->Scale(10, 10, 0.9f);
    trfBackground->Translate(0.5f, 0.5f, 0);

    auto background = Node::Make(trfBackground, {Color::Make(1, 1, 1), backgroundTexture}, {Rectangle::Make()});

    // sun
    auto trfSun = Transform::Make();
    trfSun->Translate(5, 5, 0);
    trfSun->Scale(0.8f, 0.8f, 1);

    AppearancePtr sunTexture = Texture::Make("sampler", "sun.png");
    auto sun = Node::Make(trfSun, {Color::Make(1.0f, 1.0f, 0.0f), sunTexture}, {Disk::Make(128)});

    // venus
    auto trfVenusPos = Transform::Make();
    trfVenusPos->Translate(7, 5, 0);

    auto venusPos = Node::Make(trfVenusPos);

    auto trfVenusScale = Transform::Make();
    trfVenusScale->Scale(0.3f, 0.3f, 1);
    auto venusTexture = Texture::Make("sampler", "venus.png");
    auto venusScale = Node::Make(trfVenusScale, {Color::Make(1.0f, 1.0f, 1.0f), venusTexture}, {Disk::Make(128)});

    venusPos->AddNode(venusScale);

    // earth
    auto trfEarthPos = Transform::Make();
    trfEarthPos->Translate(9.5f, 5, 0);

    auto earthPos = Node::Make(trfEarthPos);

    auto trfEarthScale = Transform::Make();
    trfEarthScale->Scale(0.5f, 0.5f, 0);

    auto earthTexture = Texture::Make("sampler", "earth.png");
    auto earthScale = Node::Make(trfEarthScale, {Color::Make(1.0f, 0.5f, 0.0f), earthTexture}, {Disk::Make(128)});

    earthPos->AddNode(earthScale);

    // moon
    auto trfMoonPos = Transform::Make();
    trfMoonPos->Translate(1.25f, 0, 0);

    auto moonPos = Node::Make(trfMoonPos);

    auto trfMoonScale = Transform::Make();
    trfMoonScale->Scale(0.2f, 0.2f, 0);

    auto moonTexture = Texture::Make("sampler", "moon.png");
    auto moonScale = Node::Make(trfMoonScale, {Color::Make(0.5f, 0.5f, 0.5f), moonTexture}, {Disk::Make(128)});

    moonPos->AddNode(moonScale);
    earthPos->AddNode(moonPos);

    auto shader = Shader::Make();
    shader->AttachVertexShader("vertex.glsl");
    shader->AttachFragmentShader("fragment.glsl");
    shader->Link();

    // scene
    auto root = Node::Make(shader, {sun, earthPos, venusPos});
    scene = Scene::Make(root);

    scene->AddEngine(VenusOrbit::Make(trfVenusPos));
    scene->AddEngine(EarthOrbit::Make(trfEarthPos));
    scene->AddEngine(RotateEarthAxis::Make(trfEarthScale));
    scene->AddEngine(MoonOrbit::Make(trfMoonPos));
}

static void display(GLFWwindow *win)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
    Error::Check("after glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)");
    scene->Render(camera);
    Error::Check("after scene->Render(camera)");
}

static void error(int code, const char *msg)
{
    printf("GLFW error %d: %s\n", code, msg);
    glfwTerminate();
    exit(0);
}

static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize(GLFWwindow *win, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void update(float dt)
{
    scene->Update(dt);
}

int main()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error);

    GLFWwindow *win = glfwCreateWindow(600, 400, "Window title", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(win, resize); // resize callback
    glfwSetKeyCallback(win, keyboard);           // keyboard callback

    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD OpenGL context\n");
        exit(1);
    }

    initialize();

    float t0 = glfwGetTime();
    while (!glfwWindowShouldClose(win))
    {
        float t = glfwGetTime();
        update(t - t0);
        t0 = t;
        display(win);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
