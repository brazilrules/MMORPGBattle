#define SDL_MAIN_HANDLED
#include "constants.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "Model.h"
#include "Player.h"
#include "Monster.h"
#include "HUDElement.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_GLContext context = NULL;

TTF_Font* font;

SDL_Event e;

GLuint glVertexArrayObject = 0;
GLuint glVertexBufferObject = 0;
GLuint glShader = 0;

Character* player;
Character* monster;

HUDElement* hudHP;
HUDElement* deathMessage;
HUDElement* winMessage;

int frame = 0;
SDL_Point target;
bool quit;
bool clicked;
bool holding;

GLuint createShaderProgram(const std::string& vertexCode, const std::string& fragmentCode) {
    GLuint program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* code = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &code , NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    code = fragmentCode.c_str();
    glShaderSource(fragShader, 1, &code, NULL);
    glCompileShader(fragShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glValidateProgram(program);

    return program;
}

void createGraphicsPipeline() {
    std::string vertexShader = "#version 410\n"
                               "layout(location=0) in vec3 position;\n"
                               "layout(location=1) in vec3 color;\n "

                                "out vec3 v_color;\n"
                               "void main()\n"
                               "{\n"
                                    "v_color = color;\n"
                               "    gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
                               "}";

    std::string fragmentShader = "#version 410\n"
                                 "in vec3 v_color;"
                                 "out vec4 color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    color = vec4(v_color.r, v_color.g, v_color.b, 1.0f);\n"
                                 "}";

    glShader = createShaderProgram(vertexShader, fragmentShader);
}

void vertexSpecification() {
    const std::vector<GLfloat> vertexData{
        -.5f, -.5f, .0f, //coords BL
        1.f, .0f, .0f, //color BL
        .5f, -.5f, .0f, //coords BR
        .0f, 1.f, .0f, //color BR
        -.5f, .5f, .0f, //coords TL
        .0f, .0f, 1.0f, //color TL
        .5f, .5f, .0f, //coords TR
        1.f, 1.f, .0f, //color TR
    };

    glGenVertexArrays(1, &glVertexArrayObject);
    glBindVertexArray(glVertexArrayObject);

    glGenBuffers(1, &glVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, glVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, (void*)(sizeof(GL_FLOAT)*3));
    
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void mainLoop() {
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                player->getModel().move(FORWARDS);
                break;
            case SDLK_RIGHT:
                player->getModel().move(RIGHT);
                break;
            case SDLK_DOWN:
                player->getModel().move(BACKWARDS);
                break;
            case SDLK_LEFT:
                player->getModel().move(LEFT);
                break;
            case SDLK_r:
                player->takeDamage(-100);
                player->getModel().setX(0);
                player->getModel().setY(0);
                player->getModel().setZ(0);
                monster->takeDamage(-20);
                monster->getModel().setX(0);
                monster->getModel().setY(0);
                monster->getModel().setZ(50);

            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                player->getModel().stop(FORWARDS);
                break;
            case SDLK_RIGHT:
                player->getModel().stop(RIGHT);
                break;
            case SDLK_DOWN:
                player->getModel().stop(BACKWARDS);
                break;
            case SDLK_LEFT:
                player->getModel().stop(LEFT);
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                target = { e.button.x, e.button.y };
                clicked = true;
                holding = true;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                holding = false;
                break;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }

    /*if ((holding || player->isAttacking()) && monster->getSprite().isInBounds(target)) {
        player->attackEnemy(*monster);
        clicked = false;
    }

    if (clicked && (target.x != player->getSprite().getCenter().x || target.y != player->getSprite().getCenter().y)) {
        player->getSprite().moveTowards(target);
    }
    else if (clicked) {
        player->getSprite().stop();
        clicked = false;
    }*/

    ((Monster*)monster)->checkPlayerProximity(*player);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(1.f, .72f, .72f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(glShader);
    
    glBindVertexArray(glVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, glVertexBufferObject);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    player->update(frame, screenSurface);
    monster->update(frame, screenSurface);

    SDL_Rect textPos{ 200, 200, 400, 100 };

    hudHP->update(frame, std::to_string(player->getHP()), screenSurface);

    if (!player->getHP()) deathMessage->update(frame, "", screenSurface);

    if (!monster->getHP()) winMessage->update(frame, "", screenSurface);

    SDL_GL_SwapWindow(window);

    frame++;
}

int main()
{

    std::cout << "Initializing SDL!" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cout << "SDL couldn't initialize! SDL Error: " << SDL_GetError() << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "Initializing SDL_TTF!" << std::endl;
    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize SDL_TTF: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    std::cout << "Initializing SDL_IMG!" << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Failed to initialize SDL_Image for PNG: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    std::cout << "Creating Window!" << std::endl;
    window = SDL_CreateWindow("MMO Battle!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Window couldn't be created! SDL Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    context = SDL_GL_CreateContext(window);

    if (context == NULL) {
        std::cout << "OpenGL context not available" << std::endl;
        return EXIT_FAILURE;
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Glad was not initialized" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "GLVersion: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Creating Font!" << std::endl;
    // Load a font
    font = TTF_OpenFont("assets/fonts/Ldfcomicsans-jj7l.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    std::cout << "Creating Screen Surface!" << std::endl;

    screenSurface = SDL_GetWindowSurface(window);

    std::cout << "Creating Units!" << std::endl;
    player = new Player(100, 50, 10, 10, 10, 5, 5, 5, "assets/gfx/Player.png", font, std::vector<Skill>());
    monster = new Monster(20, 0, 30, 10, 5, "assets/gfx/Monster.png", font, 10, 45, 0, 0, 50);

    std::cout << "Creating HUD Elements!" << std::endl;
    hudHP = new HUDElement(font, "HP", std::to_string(player->getHP()), SDL_Rect{ 10, 10 });
    deathMessage = new HUDElement(font, "You Died, Press R to try again.", "", SDL_Rect{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0,0 }, SDL_Color{ 255,0,0,255 });
    winMessage = new HUDElement(font, "You Won!, Press R to play again.", "", SDL_Rect{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0,0 }, SDL_Color{ 0,255,0,255 });

    /*if (player->getSprite().getImage() == NULL) {
        std::cout << "SDL could not load image: " << IMG_GetError() << std::endl;

        return EXIT_FAILURE;
    }

    if (monster->getSprite().getImage() == NULL) {
        std::cout << "SDL could not load image: " << IMG_GetError() << std::endl;

        return EXIT_FAILURE;
    }*/

    vertexSpecification();
    createGraphicsPipeline();

    Uint64 start;
    target = player->getModel().getScreenSpacePos();
    quit = false;
    clicked = false;
    holding = false;
    std::cout << "Main Loop!" << std::endl;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    while (!quit)
    {
        start = SDL_GetTicks64();

        mainLoop();

        if (1000 / FPS > SDL_GetTicks64() - start) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks64() - start));
        }

    }
#endif

    delete player;
    delete monster;
    delete hudHP;
    delete deathMessage;
    delete winMessage;

    SDL_FreeSurface(screenSurface);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}