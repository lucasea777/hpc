CC=cc
CFLAGS=-Wall -Wextra -std=c99 -g

LDFLAGS=-lm -lgomp -lopenblas

TARGET=real-all

all: $(TARGET)

readme:
	# sudo apt install markdown
	markdown README.md > README.html && xdg-open README.html
	# https://github.com/sindresorhus/github-markdown-css
	# yarn global add generate-github-markdown-css


real-all:
	make docopt
	make matrices


# Para actualizar cambios en matrices.docopt
docopt:
	rm -f docopt.c
	./createdocopt.sh

#https://stackoverflow.com/questions/2131213/can-you-make-valid-makefiles-without-tab-characters
#matrices: matrices.o; $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) # <-- ¿: *** missing separator.  Stop.?
# or using $ make -f <(sed 's/    /\t/g' Makefile)
matrices: matrices.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean: 
	rm -rf *.o matrices docopt.c README.html