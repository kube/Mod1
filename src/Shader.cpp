
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#include <OpenGL/gl3.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Shader.hpp"

char*
Shader::filetobuf(const char* path)
{
	int				fd;
	char			*buf;
	int				size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = 0;
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	buf = (char *)malloc(size + 1);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	read(fd, buf, size);
	buf[size] = 0;
	close(fd);
	return (buf);
}

struct s_shader
Shader::load_shaders(const char* vert, const char* frag)
{
	char			*vertSource;
	char			*fragSource;
	struct s_shader	s;

	vertSource = Shader::filetobuf(vert);
	fragSource = Shader::filetobuf(frag);
	s.vertShader = glCreateShader(GL_VERTEX_SHADER);
	s.fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(s.vertShader, 1, (const char**)&vertSource, 0);
	glShaderSource(s.fragShader, 1, (const char**)&fragSource, 0);
	glCompileShader(s.vertShader);
	glCompileShader(s.fragShader);
	s.shader = glCreateProgram();
	glAttachShader(s.shader, s.vertShader);
	glAttachShader(s.shader, s.fragShader);
	glBindAttribLocation(s.shader, 0, "position");
    glBindAttribLocation(s.shader, 1, "color");
	glLinkProgram(s.shader);
	glUseProgram(s.shader);
	free(vertSource);
	free(fragSource);
	return (s);
}