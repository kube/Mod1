
NAME := mod1
INCLUDEFOLDERS := -I include/ -I$(HOME)/Lib/SDL2/include

SOURCES_FOLDER := src/
OBJECTS_FOLDER := obj/

vpath %.cpp src

CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L$(HOME)/Lib/SDL2/lib -lSDL2 -framework OpenGL

SOURCES := \
			Matrix.cpp		\
			Shader.cpp		\
			Vec3.cpp		\
			Camera.cpp		\
			Particle.cpp	\
			main.cpp		\

OBJECTS := $(SOURCES:.cpp=.o)

OBJECTS := $(addprefix $(OBJECTS_FOLDER), $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_FOLDER), $(SOURCES))


# Colors
NO_COLOR     := \x1b[0m
OK_COLOR     := \x1b[32;01m
ERROR_COLOR  := \x1b[31;01m
WARN_COLOR   := \x1b[33m
SILENT_COLOR := \x1b[30;01m


# Basic Rules
.PHONY: all re clean fclean

all: $(NAME)

obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) $(INCLUDEFOLDERS) -c $(subst __,/,$<) -o $@
	@printf "$(OK_COLOR)✓ $(NO_COLOR)"
	@echo $<

$(NAME): $(OBJECTS)
	@printf "$(SILENT_COLOR)Compiling $(NAME)...$(NO_COLOR)"
	@$(CXX) -o $(NAME) $(LDFLAGS) $(OBJECTS)
	@printf " $(OK_COLOR)Done ✓$(NO_COLOR)\n"

clean:
	@rm -rf $(OBJECTS_FOLDER)
	@printf "$(SILENT_COLOR)$(NAME) : Removed objects$(NO_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(SILENT_COLOR)$(NAME) : Removed $(NAME)$(NO_COLOR)\n"

re: fclean all
