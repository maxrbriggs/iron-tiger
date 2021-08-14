PREFIX = /usr/local
TARGET = $(DESTDIR)$(PREFIX)

CC = gcc
IDIR = include
CFLAGS = -Wall -lncurses -I$(IDIR)

CDIR = src
ODIR = src

_DEPS = agent.h peragent.h peragent_list.h agent_actions.h map.h actions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# _OBJ = agent.o peragent.o main.o
_OBJ = main.o agent_actions.o map.o actions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

EXEC = iron-tiger

DEBUG_FLAG =

$(ODIR)/%.o: $(CDIR)/%.c $(DEPS)
	$(CC) $(DEBUG_FLAG) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) $(DEBUG_FLAG) -o $@ $^ $(CFLAGS)

debug : DEBUG_FLAG = -g
debug : $(OBJ)
debug : $(EXEC)

.PHONY: install clean

install: $(EXEC)
	install -Dm 755 $(EXEC) $(TARGET)/bin/$(EXEC)
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXEC)
