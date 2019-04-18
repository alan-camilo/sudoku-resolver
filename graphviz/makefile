CC=dot
SRC=$(wildcard *.dot)
TAR=$(SRC:.dot=.png)

.PHONY: all clean

all: $(TAR)

%.png: %.dot
	$(CC) -Tpng $< -o $@

clean:
	rm -rf $(TAR)
