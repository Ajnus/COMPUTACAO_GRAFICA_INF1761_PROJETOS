
TARGET = t

all: $(TARGET)

INC = -I. -I/Users/celes/Work/include -I/opt/homebrew/include 
LIB = -L.  -L/opt/homebrew/lib

CPP = CC
#CPPFLAGS = -O2 -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 
CPPFLAGS = -g -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 

SRC = \
  camera2d.cpp \
  color.cpp \
  disk.cpp \
  error.cpp \
  image.cpp \
  node.cpp \
  scene.cpp \
  shader.cpp \
  state.cpp \
  texture.cpp \
  transform.cpp \
  triangle.cpp \
  main_crono_tex.cpp \

OBJ = $(addsuffix .o, $(basename $(SRC))) 

.cpp.o:
	$(CPP) $(INC) $(CPPFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ) Makefile 
	$(CPP) $(LIB) -o $@ $(OBJ) -lstdc++ -framework OpenGL -lglfw -lassimp


clean:
	rm -f $(TARGET) $(OBJ)


