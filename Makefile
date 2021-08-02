PREFIX = /usr/local
TARGET = $(DESTDIR)$(PREFIX)

CC = gcc
IDIR = include
CFLAGS = -Wall -lncurses -I$(IDIR)

CDIR = src
ODIR = src

_DEPS = agent.h peragent.h peragent_list.h agent_actions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# _OBJ = agent.o peragent.o main.o
_OBJ = main.o agent_actions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

EXEC = iron-tiger

$(ODIR)/%.o: $(CDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

debug : CFLAGS = -g -Wall -lncurses -I$(IDIR)
debug : $(OBJ)
debug : $(EXEC)

.PHONY: install clean

install: $(EXEC)
	install -Dm 755 $(EXEC) $(TARGET)/bin/$(EXEC)
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXEC)
