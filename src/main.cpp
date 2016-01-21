
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <array>

#include "Matrix.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Particle.hpp"

void
initCube(float cube[24][7])
{
	// X Lines
	cube[0][0] = -5.0;
	cube[0][1] = -5.0;
	cube[0][2] = -5.0;
	cube[1][0] = 5.0;
	cube[1][1] = -5.0;
	cube[1][2] = -5.0;
	cube[2][0] = -5.0;
	cube[2][1] = 5.0;
	cube[2][2] = -5.0;
	cube[3][0] = 5.0;
	cube[3][1] = 5.0;
	cube[3][2] = -5.0;
	cube[4][0] = -5.0;
	cube[4][1] = -5.0;
	cube[4][2] = 5.0;
	cube[5][0] = 5.0;
	cube[5][1] = -5.0;
	cube[5][2] = 5.0;
	cube[6][0] = -5.0;
	cube[6][1] = 5.0;
	cube[6][2] = 5.0;
	cube[7][0] = 5.0;
	cube[7][1] = 5.0;
	cube[7][2] = 5.0;
	// Y Lines
	cube[8][0] = -5.0;
	cube[8][1] = -5.0;
	cube[8][2] = -5.0;
	cube[9][0] = -5.0;
	cube[9][1] = 5.0;
	cube[9][2] = -5.0;
	cube[10][0] = 5.0;
	cube[10][1] = -5.0;
	cube[10][2] = -5.0;
	cube[11][0] = 5.0;
	cube[11][1] = 5.0;
	cube[11][2] = -5.0;
	cube[12][0] = -5;
	cube[12][1] = -5.0;
	cube[12][2] = 5.0;
	cube[13][0] = -5.0;
	cube[13][1] = 5.0;
	cube[13][2] = 5.0;
	cube[14][0] = 5.0;
	cube[14][1] = -5.0;
	cube[14][2] = 5.0;
	cube[15][0] = 5.0;
	cube[15][1] = 5.0;
	cube[15][2] = 5.0;
	// Z Lines
	cube[16][0] = -5.0;
	cube[16][1] = -5.0;
	cube[16][2] = -5.0;
	cube[17][0] = -5.0;
	cube[17][1] = -5.0;
	cube[17][2] = 5.0;
	cube[18][0] = 5.0;
	cube[18][1] = -5.0;
	cube[18][2] = -5.0;
	cube[19][0] = 5.0;
	cube[19][1] = -5.0;
	cube[19][2] = 5.0;
	cube[20][0] = -5.0;
	cube[20][1] = 5.0;
	cube[20][2] = -5.0;
	cube[21][0] = -5.0;
	cube[21][1] = 5.0;
	cube[21][2] = 5.0;
	cube[22][0] = 5.0;
	cube[22][1] = 5.0;
	cube[22][2] = -5.0;
	cube[23][0] = 5.0;
	cube[23][1] = 5.0;
	cube[23][2] = 5.0;

	// Color
	for (int i = 0; i < 24; i++)
	{
		cube[i][3] = 0.2;
		cube[i][4] = 0.2;
		cube[i][5] = 0.2;
		cube[i][6] = 0.8;
	}
}

void
handleEvents(Camera &camera, bool* over, SDL_Event* events)
{
	SDL_PollEvent(events);
	if (events->type == SDL_QUIT)
		*over = 1;
	else if (events->type == SDL_KEYDOWN)
	{
		switch (events->key.keysym.sym)
		{
			case SDLK_ESCAPE:
				*over = 1;
				break;
			case SDLK_w:
				camera.keys.mFront = true;
				break;
			case SDLK_a:
				camera.keys.mLeft = true;
				break;
			case SDLK_s:
				camera.keys.mBack = true;
				break;
			case SDLK_d:
				camera.keys.mRight = true;
				break;
			case SDLK_r:
				camera.keys.mUp = true;
				break;
			case SDLK_f:
				camera.keys.mDown = true;
				break;
			case SDLK_LEFT:
				camera.keys.rLeft = true;
				break;
			case SDLK_RIGHT:
				camera.keys.rRight = true;
				break;
			case SDLK_UP:
				camera.keys.rUp = true;
				break;
			case SDLK_DOWN:
				camera.keys.rDown = true;
				break;
		}
	}
	else if (events->type == SDL_KEYUP)
	{
		switch (events->key.keysym.sym)
		{
			case SDLK_w:
				camera.keys.mFront = false;
				break;
			case SDLK_a:
				camera.keys.mLeft = false;
				break;
			case SDLK_s:
				camera.keys.mBack = false;
				break;
			case SDLK_d:
				camera.keys.mRight = false;
				break;
			case SDLK_r:
				camera.keys.mUp = false;
				break;
			case SDLK_f:
				camera.keys.mDown = false;
				break;
			case SDLK_LEFT:
				camera.keys.rLeft = false;
				break;
			case SDLK_RIGHT:
				camera.keys.rRight = false;
				break;
			case SDLK_UP:
				camera.keys.rUp = false;
				break;
			case SDLK_DOWN:
				camera.keys.rDown = false;
				break;
		}
	}
}

int
main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	SDL_Window		*win(0);
	SDL_GLContext	glContext;
	SDL_Event		events;

	//// INITIALIZING
	// SDL initializing
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to init SDL, aborting." << std::endl;
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	win = SDL_CreateWindow("Mod1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	if (!win)
	{
		std::cout << "Failed to create window, aborting." << std::endl;
		SDL_Quit();
		return (-1);
	}

	// GL initializing
	glContext = SDL_GL_CreateContext(win);
	if (!glContext)
	{
		std::cout << "Failed to create OpenGL context, aborting." << std::endl;
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (-1);
	}
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	////

	// Particles Initializing
	//
	Vec3 particles[1331];
	int i = 0;
	for (float x = -5.0; x <= 5.0; x += 1.0)
	{
		for (float y = -5.0; y <= 5.0; y += 1.0)
		{
			for (float z = -5.0; z <= 5.0; z += 1.0)
			{
				particles[i].x = x;
				particles[i].y = y;
				particles[i].z = z;
				i++;
			}
		}
	}

	// VAOs/VBOS
	GLuint vao, particlesVbo, cubeVbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Cube VBO
	float cube[44][7];
	initCube(cube);
	glGenBuffers(1, &cubeVbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * 7 * sizeof(float), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  7 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Particles VBO
	//
	glGenBuffers(1, &particlesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, particlesVbo);
	glBufferData(GL_ARRAY_BUFFER, 1331 * 7 * sizeof(float), reinterpret_cast<float*>(particles), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  7 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Shaders
	t_shader s = Shader::load_shaders(static_cast<const char *>("shaders/basic.vert.glsl"), static_cast<const char *>("shaders/basic.frag.glsl"));

	// Camera/Matrix Setup
	Camera camera(0.0, 0.0, 40.0);
	float projection[16], model[16], view[16];
	Matrix::perspective(projection, 45.0, 1.0, 0.01, 1000000000000.0);


	//// Main Loop
	bool over(false);
	while (!over)
	{
		handleEvents(camera, &over, &events);
		camera.update();

		// Matrix Setup
		Matrix::setIdentity(model);
		Matrix::setIdentity(view);
		std::memcpy(view, camera.view(), 16 * sizeof(float));
		Matrix::multiply(view, projection);
		Matrix::multiply(model, view);
		glUniformMatrix4fv(glGetUniformLocation(s.shader, "mvp"), 1, GL_FALSE, model);

		//
		// Computing
		//

		//
		// Update
		//

		// Drawing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Cube
		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  7 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_LINES, 0, 24);
		// Particles
		glBindBuffer(GL_ARRAY_BUFFER, particlesVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  7 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_POINTS, 0, 1331);

		// Refresh
		SDL_GL_SwapWindow(win);
	}

	// Freeing resources
	glUseProgram(0);
	// glDisableVertexAttribArray(0);
	// glDisableVertexAttribArray(1);
	glDetachShader(s.shader, s.vertShader);
	glDetachShader(s.shader, s.fragShader);
	glDeleteProgram(s.shader);
	glDeleteShader(s.vertShader);
	glDeleteShader(s.fragShader);
	glDeleteBuffers(1, &particlesVbo);
	glDeleteBuffers(1, &cubeVbo);
	glDeleteVertexArrays(1, &vao);
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}