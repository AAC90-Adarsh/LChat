cc = gcc -g

reader: reader.c
	$(cc) -o reader reader.c
	$(cc) -o writer writer.c
clean:
	rm -rf reader writer

