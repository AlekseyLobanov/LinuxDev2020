CFLAGS = -Wall -Wextra -std=c99 -g
CPPFLAGS = -I.
LDFLAGS =

EXEC = main

all: $(EXEC) po/ru/$(EXEC).mo

$(EXEC): $(EXEC).c 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

po/ru/$(EXEC).mo: po/ru/$(EXEC).po
	msgfmt --output-file=$@ $<

po/ru/$(EXEC).po: po/$(EXEC).pot
	msgmerge --update $@ $<

po/$(EXEC).pot: $(EXEC).c
	xgettext -k_ -j -lC -c -s -o po/main.pot main.c

clean:
	@rm -f $(EXEC) po/ru/*.mo *~

.PHONY: clean