#pragma once
#include <string>

class Model;

class GraphicsAPI
{
public:
	GraphicsAPI();
	~GraphicsAPI();

	virtual bool initialize() = 0;
	virtual void showInfo() = 0;
	virtual void createGraphicsPipeline(std::string vertexCode, std::string fragCode) = 0;
	virtual void drawModel(Model model) = 0;
	

private:

};