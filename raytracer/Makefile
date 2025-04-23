##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## RayTracer
##

SRC	=	src/main.cpp \
		src/Math/Point3D.cpp \
		src/Math/Vector3D.cpp \
		src/RayTracer/Ray.cpp \
		src/RayTracer/Rectangle3D.cpp \
		src/RayTracer/HitRecord.cpp	\
		src/VisualComp/Color.cpp \
		src/Parsing/ParseArgs.cpp	\
		src/Scene/Scene.cpp \
		src/Scene/SceneBuilder.cpp \
		src/RayTracer/Image.cpp \
		src/RayTracer/Camera.cpp \
		src/Core/Core.cpp \
		src/Factories/LightFactory.cpp \
		src/Factories/PrimitivesFactory.cpp \
		src/Factories/CameraFactory.cpp \
		src/Factories/Exceptions.cpp \
		src/DLLoader/Exceptions.cpp \

OBJ	=	$(SRC:.cpp=.o)

NAME	=	raytracer

CPPFLAGS=	-iquote ./include

CXXFLAGS=-Wall -Wextra -std=c++20 -fno-gnu-unique -fPIC 

PLUGINS_MAKEFILE=PluginsMakefile

RM?	=	rm -f

all: 	$(NAME)

$(NAME): raytracer
$(NAME): plugins

raytracer: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -L/usr/local/lib -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system

plugins:
	[ -d plugins/ ] || mkdir -p plugins/
	[ -d plugins/primitives ] || mkdir -p plugins/primitives
	[ -d plugins/lights ] || mkdir -p plugins/lights
	[ -d plugins/transformations ] || mkdir -p plugins/transformations
	make -f $(PLUGINS_MAKEFILE)

clean:
	make clean -f $(PLUGINS_MAKEFILE)
	$(RM) $(OBJ)

fclean: clean
	make fclean -f $(PLUGINS_MAKEFILE)
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean re all plugins