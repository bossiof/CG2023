# Thomas Daley
# September 13, 2021

# A generic build template for C/C++ programs

# executable name
EXE = app

# C compiler
CC = gcc
# C++ compiler
CXX = g++
# linker
LD = g++

# C flags
CFLAGS = 
# C++ flags
CXXFLAGS = -std=c++17
# C/C++ flags
CPPFLAGS = -Wall -O2
# dependency-generation flags
DEPFLAGS = -MMD -MP -I./src/lib
# linker flags
LDFLAGS = 
# library flags
LDLIBS = 
# packages used
PKG = vulkan glfw3

CFLAGS+=$(shell pkg-config --cflags $(PKG))
CXXFLAGS+=$(shell pkg-config --cflags $(PKG))
LDFLAGS+=$(shell pkg-config --libs $(PKG))

# build directories
BIN = bin
OBJ = obj
SRC = src

SOURCES := $(wildcard $(SRC)/*.c $(SRC)/**/*.c $(SRC)/*.cc $(SRC)/**/*.cc $(SRC)/*.cpp $(SRC)/**/*.cpp $(SRC)/*.cxx $(SRC)/**/*.cxx)

OBJECTS := \
	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/**/*.c $(SRC)/*.c)) \
	$(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(wildcard $(SRC)/**/*.cc $(SRC)/*.cc)) \
	$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/**/*.cpp $(SRC)/*.cpp)) \
	$(patsubst $(SRC)/%.cxx, $(OBJ)/%.o, $(wildcard $(SRC)/**/*.cxx $(SRC)/*.cxx))

# include compiler-generated dependency rules
DEPENDS := $(OBJECTS:.o=.d)

# compile C source
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c -o $@
# compile C++ source
COMPILE.cxx = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
# link objects
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

ENSURE = @mkdir -p $(dir $@) 2> /dev/null || true

.DEFAULT_GOAL = all

.PHONY: all
all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC) $(OBJ) $(BIN) $(OBJECTS)
	$(LINK.o)

$(SRC):
	mkdir -p $(SRC)

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

$(OBJ)/%.o:	$(SRC)/%.c
	$(ENSURE)
	$(COMPILE.c) $<

$(OBJ)/%.o:	$(SRC)/%.cc
	$(ENSURE)
	$(COMPILE.cc) $<

$(OBJ)/%.o:	$(SRC)/%.cpp
	$(ENSURE)
	$(COMPILE.cxx) $<

$(OBJ)/%.o:	$(SRC)/%.cxx
	$(ENSURE)
	$(COMPILE.cxx) $<

# force rebuild
.PHONY: remake
remake:	clean $(BIN)/$(EXE)

# execute the program
.PHONY: run
run: $(BIN)/$(EXE)
	./$(BIN)/$(EXE)

# remove previous build and objects
.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPENDS)
	$(RM) $(BIN)/$(EXE)

# remove everything except source
.PHONY: reset
reset:
	$(RM) -r $(OBJ)
	$(RM) -r $(BIN)

-include $(DEPENDS)