CXX = g++
CXX_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline\
 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default\
 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy\
 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op\
 -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual\
 -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG\
 -D_EJUDGE_CLIENT_SIDE 

LIB_DIR = trees/

LIB_SRC_DIR = $(LIB_DIR)source/
LIB_OBJ_DIR = $(LIB_DIR)object/

SRC_DIR = source/
OBJ_DIR = object/

LIB_OBJECT  =   $(LIB_OBJ_DIR)trees.o            \
				$(LIB_OBJ_DIR)trees_test.o       \
				$(LIB_OBJ_DIR)tree_graphic_dump.o

INCLUDES    =   $(LIB_SRC_DIR)trees.h            \
				$(LIB_SRC_DIR)tree_graphic_dump.h

all: trees_test

trees_test: $(LIB_OBJECT)
	$(CXX) $(LIB_OBJECT) -o $@ $(CXX_FLAGS)

$(LIB_OBJ_DIR)trees.o:             $(LIB_SRC_DIR)trees.cpp             $(INCLUDES)
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

$(LIB_OBJ_DIR)trees_test.o:        $(LIB_SRC_DIR)trees_test.cpp        $(INCLUDES)
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

$(LIB_OBJ_DIR)tree_graphic_dump.o: $(LIB_SRC_DIR)tree_graphic_dump.cpp $(INCLUDES)
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

clean:
	rm $(LIB_OBJECT) *.exe
