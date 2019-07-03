/*
 *
 * Arguments for this program are names. Each fifo in the "fifos/"
 * directory is a person who can be messaged.
 *
 * Ex:	(Running without script)
 *
 * gcc -o writer writer.c adarsh eric
 *
 * I am asking the writer, "adarsh", to send a message to the fifo
 * called "eric". If I am another user and I want to message Adarsh,
 * I want to put my fifo as the first argument and the recipient's fifo
 * as the second argument (think of it as "my fifo" to "your fifo").
 *
 * Multiple people can write to a single person's fifo at one time.
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
#define COLON ": "				// Define colon for the name
#define F_DIR_LEN strlen(F_DIR)	// Define the length of the directory string

char in[BUFFER];        // Input received from FIFO
char *fifo;
char *w_str;

void INThandler(int sig) {
	free(fifo);
	free(w_str);
    exit(0);
}

void construct_str(char *r_name, char *in, char* w_str) {
	w_str += sprintf(w_str, "%s", r_name);
	w_str += sprintf(w_str, "%s", ": ");
	w_str += sprintf(w_str, "%s", in);
}

int main(int argc, char **argv) {
	char *w_name = argv[1];		// Name of who is writing message
	char *r_name = argv[2];		// Name of who is receiving message
	int w_name_len = strlen(w_name);
	int r_name_len = strlen(r_name);
	int num_bytes = 0;

	// Fifo directory address construction
	char *fifo = (char *) malloc(F_DIR_LEN + r_name_len + 1);
	memcpy(fifo, F_DIR, F_DIR_LEN);
	memcpy(fifo + F_DIR_LEN, r_name, r_name_len + 1);

	// Open the desired fifo
	int fd_w = open(fifo, O_WRONLY);
	if (fd_w == -1) {
		perror("File descriptor error:");
		exit(-1);
	}

	// Infinite loop to write to fifo
	for (;;) {
		printf("You: ");
		fgets(in, BUFFER, stdin);

		// char w_str[strlen(in) + strlen(name) + strlen(COLON) + 1];
		w_str = (char *) malloc(strlen(w_name) + strlen(COLON) + strlen(in) + 1);
		construct_str(w_name, in, w_str);

		if ((num_bytes = write(fd_w, w_str, strlen(w_str))) > 0) {
			// Send to socket so it can be displayed on reader
		}

		memset(in, 0, sizeof(in));
		memset(w_str, 0, sizeof(w_str));
		free(w_str);
	}

	free(fifo);
	return 0;
}