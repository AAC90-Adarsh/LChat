/*
 *
 * Arguments for this program are names. Each fifo in the "fifos/"
 * directory is a person who can be messaged.
 *
 * Ex:	(Running without script)
 *
 * gcc -o reader reader.c adarsh
 *
 * With the argument "adarsh", I am asking the reader to read the fifo
 * "adarsh". If I am the user Adarsh, I want to read my own fifo so I
 * can see what others send to me.
 *
 * Multiple people can send messages to your fifo at once.
 *
 * NOT SECURE (people can impersonate others, by using their fifos)
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>

#define BUFFER 2048				// Define the I/O buffer size
#define F_DIR "fifos/"			// Define the directory storing all fifos
#define F_DIR_LEN strlen(F_DIR)	// Define the length of the directory string

char in[BUFFER];        // Input received from FIFO
char *fifo;

void INThandler(int sig) {
	free(fifo);
    exit(0);
}

int main(int argc, char **argv) {
	char *name = argv[1];
	int name_len = strlen(name);
	int num_bytes = 0;

	fifo = (char *) malloc(F_DIR_LEN + name_len + 1);
	memcpy(fifo, F_DIR, F_DIR_LEN);
	memcpy(fifo + F_DIR_LEN, name, name_len + 1);

	// Open the desired fifo
	int fd_r = open(fifo, O_RDONLY);
	if (fd_r == -1) {
		perror("File descriptor error:");
		exit(-1);
	}

	// Infinite loop to read from fifo
	int leave = 0;
	for (;;) {
		if ((num_bytes = read(fd_r, in, BUFFER)) > 0) {
			leave = 0;		// Someone joined the chat
			printf("%s", in);
		}
		else if (num_bytes = read(fd_r, in, BUFFER) == 0 && leave == 0) {
			leave = 1;		// Someone left the chat
			printf("Someone has left the chatroom\nWe will still lookout for more messages\n");
		}
		memset(in, 0, sizeof(in));
	}

	free(fifo);
	return 0;
}