#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++
SRC_DIR := src
COMPILER := g++
INC_DIR := include
INC_FLAGS := -I $(INC_DIR)
OTHER_FLAGS := -std=c++17 -Wextra -O2 -g


ADD_LIB:=


OBJS_FILES := build/geometricalobjects.o build/objectimages.o build/main.o build/coords.o build/construction.o build/objet3d.o 

all: build/runnable

build:
	mkdir build

build/construction.o : $(SRC_DIR)/construction.cpp $(INC_DIR)/construction.h build
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/objet3d.o : $(SRC_DIR)/Object3D.cpp $(INC_DIR)/Object3D.h $(INC_DIR)/ObjectImages.h build
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/coords.o : $(SRC_DIR)/coords.cpp $(INC_DIR)/coords.h build
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/geometricalobjects.o : $(SRC_DIR)/GeometricalObjects.cpp $(INC_DIR)/GeometricalObjects.h build
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/objectimages.o : $(SRC_DIR)/ObjectImages.cpp $(INC_DIR)/ObjectImages.h $(INC_DIR)/GeometricalObjects.h build
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/main.o : $(SRC_DIR)/Main.cpp $(INC_DIR)/*.h build
	$(COMPILER) $< -c -o $@ -g -I PNG -Wno-deprecated $(INC_FLAGS) $(OTHER_FLAGS) $(ADD_LIB)

build/runnable : $(ADD_LIB) $(OBJS_FILES)
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) $(OTHER_FLAGS) 

run :
	build/runnable

check-run :
	valgrind -s --leak-check=full --track-origins=yes build/runnable

test-other : build/legobrick.o build/coords.o build/legobricks.o build/geometricalobjects.o
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) $(OTHER_FLAGS)
	build/runnable

clean:
	rm build/*
