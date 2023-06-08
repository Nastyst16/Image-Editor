# Copyright Nastase Cristian - Gabriel
# 315 CA

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) 0.function.c  1.load.c  2.select.c  3.histogram.c  4.equalize.c  5.rotate.c  6.crop.c  7.apply.c  8.save.c  -lm  image_editor.c  -o  image_editor

clean:
	rm -f $(TARGETS)
