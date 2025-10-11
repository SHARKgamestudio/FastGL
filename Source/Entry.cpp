#include "OpenGL/Error.h"
#include "OpenGL/types.h"

#include "OpenGL/Window.h"
#include "OpenGL/VAO.h"
#include "OpenGL/VBO.h"
#include "OpenGL/IBO.h"
#include "OpenGL/VBL.h"
#include "OpenGL/Shader.h"
#include "OpenGL/ShaderProgram.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	"OpenGL"

#if defined(_MSC_VER) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
	// DATA
	OpenGL::CombinedShaderSrc src =
		OpenGL::getCombinedShaderSrcFromFile(
			"Shaders/default.shader"
		);

	float vertices[8] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,
	};

	unsigned int indices[6]{
		0, 1, 2,
		2, 3, 0,
	};

	// CREATING THE WINDOW AND CONTEXT
	OpenGL::Window window = OpenGL::Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// CREATING VRAM OBJECTS
	OpenGL::VAO vao;

	OpenGL::VBO vbo(sizeof(vertices), vertices, OpenGL::DrawType::STATIC);

	OpenGL::VBL vbl;
	vbl.addElement<float>(2);

	vao.addBuffer(vbo, vbl);

	OpenGL::IBO ibo(6, indices, OpenGL::DrawType::STATIC);

	// COMPILING SHADERS
	OpenGL::Shader vert(src.vert, OpenGL::ShaderType::VERTEX);
	OpenGL::Shader frag(src.frag, OpenGL::ShaderType::FRAGMENT);

	// CREATING SHADER PROGRAM
	OpenGL::ShaderProgram program;
	program.attachShader(vert);
	program.attachShader(frag);

	program.setUniform<float>("u_R", 1.0f);

	float time = 0;
	int direction = 1;

	while (!window.shouldClose()) {
		window.pollEvents();

		if (time >= 1) direction = -1;
		else if (time <= 0) direction = 1;
		time += direction * 0.05f;

		window.clear();

		program.bind();
		program.setUniform<float>("u_R", time);

		window.draw(vao, ibo, program);

		window.swapBuffers();
	}

	return 0;
}