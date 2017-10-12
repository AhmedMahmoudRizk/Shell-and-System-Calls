HEADERS= commands.h command_parser.h environment.h file_processing.h variables.h paths_handle.h
OBJECTS= main.c commands.c command_parser.c environment.c file_processing.c variables.c paths_handle.c
default :shell 

%.o: %.c $(HEADERS)
	gcc -c $< -o $@


shell:$(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f shell

