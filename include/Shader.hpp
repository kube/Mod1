
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#ifndef SHADER_HPP
#define SHADER_HPP

typedef struct	s_shader
{
	int			vertShader;
	int			fragShader;
	int			shader;
}				t_shader;

namespace Shader
{
	char				*filetobuf(const char* path);
	struct s_shader		load_shaders(const char* vert, const char* source);
}

#endif
