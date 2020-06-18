TARGET = runner

CC = gcc
CFLAGS = -Iinclude -c -Wall -Wextra -pedantic -Werror
LDFLAGS = -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR) $(LIBS)

LIB_DIR = lib/

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
LIBS = -lglist

.PHONY: all clean

all: CFLAGS += -O2
all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	@echo "  CC  $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(TARGET)
