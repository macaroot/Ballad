COMPLR = gcc

SRCDIR = src
BUILDDIR = build
BINDIR = bin
PROG = $(BINDIR)/ballad

SOURCES = $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))

CFLAGS = -g -Wall -ansi -pedantic
INC = -I/usr/include/SDL2/
HEAD = -Iinclude
LIB_LOOK = -L/usr/lib/
LIB = -lSDL2

$(PROG): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@touch $(PROG)
	@echo "$(COMPLR) $^ -o $(PROG) $(LIB_LOOK) $(LIB)"; $(COMPLR) $^ -o $(PROG) $(LIB_LOOK) $(LIB);
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	@echo "$(COMPLR) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<"; $(COMPLR) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<

tags:
	@echo "ctags -R src/* include/*"; ctags -R src/* include/*

clean:
	@echo "$(RM) -r $(BUILDDIR) $(PROG)"; $(RM) -r $(BUILDDIR) $(PROG)
