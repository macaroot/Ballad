# the compiler: gcc for C, g++ for C++
# CC = g++
CC = gcc

SRCDIR = src
BUILDDIR = build
TARGET = bin/ballad

SRCEXT = c
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# compiler flags
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall
# includes and libs
INC = -I/usr/include/SDL2/
HEAD = -Iinclude
LIB_LOOK = -L/usr/lib/ -L/usr/lib/mesa/
LIB = -lSDL2 -lSDL2_image

# all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "$(CC) $^ -o $(TARGET) $(LIB_LOOK) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB_LOOK) $(LIB);
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<

clean:
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)


# This is the original working version
# gcc -I/usr/include/SDL2 ballad.c -o ballad -L/usr/lib -lSDL2
