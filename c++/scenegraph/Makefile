
TARGET = t

all: $(TARGET)

INC = -I.
LIB = glad/glad.c

CXX = g++
#CPPFLAGS = -O2 -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 
CPPFLAGS = -g -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 

SRC = \
  arcball.cpp \
  camera2d.cpp \
  camera3d.cpp \
  clipplane.cpp \
  color.cpp \
  cube.cpp \
  disk.cpp \
  error.cpp \
  framebuffer.cpp \
  grid.cpp \
  image.cpp \
  light.cpp \
  material.cpp \
  mesh.cpp \
  node.cpp \
  polyoffset.cpp \
  quad.cpp \
  scene.cpp \
  shader.cpp \
  skybox.cpp \
  sphere.cpp \
  state.cpp \
  texcube.cpp \
  texdepth.cpp \
  texture.cpp \
  transform.cpp \
  triangle.cpp \
  main_3d.cpp

OBJ = $(addsuffix .o, $(basename $(SRC))) 

.cpp.o:
	$(CXX) $(INC) $(CPPFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ) Makefile 
	$(CXX) $(LIB) -o $@ $(OBJ) -lglfw3 -lopengl32 -lgdi32 -lassimp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)


