#include "OpenGLAPI.h"
#include "Model.h"

OpenGLAPI::OpenGLAPI()
{
}

OpenGLAPI::~OpenGLAPI()
{
}

bool OpenGLAPI::initialize()
{
	return false;
}

void OpenGLAPI::showInfo()
{
}

void OpenGLAPI::createGraphicsPipeline(std::string vertexCode, std::string fragCode)
{
    currentProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* code = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &code, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    code = fragCode.c_str();
    glShaderSource(fragShader, 1, &code, NULL);
    glCompileShader(fragShader);

    glAttachShader(currentProgram, vertexShader);
    glAttachShader(currentProgram, fragShader);
    glLinkProgram(currentProgram);

    glValidateProgram(currentProgram);

    //return program;
}

void OpenGLAPI::drawModel(Model model)
{
}