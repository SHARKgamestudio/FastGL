#include <OpenGL.h>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	"OpenGL"

#if defined(_MSC_VER) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

int main() {
	// DATA
	OpenGL::CombinedShaderSrc shader_src =
		OpenGL::getCombinedShaderSrcFromFile(
			"../../Shaders/default.shader"
		);

	OpenGL::TextureSrc texture_src =
		OpenGL::getTextureSrcFromFile(
			"../../Textures/default.png"
		);

	float vertices[] = {
	   //Position   //TexCoords
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f,
	};

	unsigned int indices[]{
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
	vbl.addElement<float>(2);

	vao.addBuffer(vbo, vbl);

	OpenGL::IBO ibo(6, indices, OpenGL::DrawType::STATIC);

	// COMPILING SHADERS
	OpenGL::Shader vert(shader_src.vert, OpenGL::ShaderType::VERTEX);
	OpenGL::Shader frag(shader_src.frag, OpenGL::ShaderType::FRAGMENT);

	// CREATING SHADER PROGRAM
	OpenGL::ShaderProgram program;
	program.attachShader(vert);
	program.attachShader(frag);

	float ratio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
	glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

	program.setUniform<glm::mat4>("u_Mvp", projection);

	program.setUniform<int>("u_Texture", 0);

	// CREATING TEXTURES
	OpenGL::Texture texture(texture_src);
	texture.bind();

	while (!window.shouldClose()) {
		window.pollEvents();

		window.clear();

		window.draw(vao, ibo, program);

		window.swapBuffers();
	}

	return 0;
}