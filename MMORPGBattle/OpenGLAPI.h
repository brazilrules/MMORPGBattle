#pragma once
#include "GraphicsAPI.h"
#include "glad/glad.h"

class OpenGLAPI: public GraphicsAPI
{
public:
	OpenGLAPI();
	~OpenGLAPI();

	// Inherited via GraphicsAPI
	bool initialize() override;

	void showInfo() override;

	void createGraphicsPipeline(std::string vertexCode, std::string fragCode) override;

	void drawModel(Model model) override;

private:
	GLuint currentProgram;

};
