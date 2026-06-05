#include <OpenGL.h>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	"OpenGL"

#if defined(_MSC_VER) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

void render(OpenGL::Window& window, OpenGL::VAO& vao, OpenGL::IBO& ibo, OpenGL::ShaderProgram& program) {
	window.clear(OpenGL::Color{ 0.102f, 0.102f, 0.109f, 1.000f });
	window.draw(vao, ibo, program);
	window.swapBuffers();
}

void update_matrices(int width, int height, OpenGL::ShaderProgram program) {
	float ratio = static_cast<float>(width) / static_cast<float>(height);
	glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

	program.bind();
	program.setUniform<glm::mat4>("u_Mvp", projection);
}

int main() {
	// DATA
	OpenGL::CombinedShaderSrc shader_src =
		OpenGL::getCombinedShaderSrcFromFile(
			GL_RES_PATH "Shaders/default.shader"
		);

	OpenGL::TextureSrc icon_src =
		OpenGL::getTextureSrcFromFile(
			GL_RES_PATH "Textures/icon.png",
			false
		);

	OpenGL::TextureSrc texture_src =
		OpenGL::getTextureSrcFromFile(
			GL_RES_PATH "Textures/default.png",
			true
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
	OpenGL::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	window.setIcon(icon_src);

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

	program.setUniform<int>("u_Texture", 0);

	// CREATING TEXTURES
	OpenGL::Texture texture(texture_src);
	texture.bind();

	// CONFIGURING WINDOW RESIZE CALLBACKS
	update_matrices(WINDOW_WIDTH, WINDOW_HEIGHT, program);
	window.OnResize.addListener([&](int width, int height) {
		update_matrices(width, height, program);
		render(window, vao, ibo, program);
	});

	// RENDER LOOP
	while (!window.shouldClose()) {
		window.pollEvents();
		render(window, vao, ibo, program);
	}

	return 0;
}