TARGET = runner

CC = gcc
CFLAGS = -Iinclude -c -Wall -Wextra -pedantic -Werror
LDFLAGS =

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

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
