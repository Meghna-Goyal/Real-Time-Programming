/* Program to illustrate file seek. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {

  char *buf;
  int fd, size, l;

  buf = (char *) malloc(100*sizeof(char));
  fd = open("readtext.txt", O_RDONLY);
  if (fd < 0)
	{ 
		perror("readtext.txt"); 
		exit(1); 
	}

	size = read(fd, buf, 10);
	printf("Opened readtext.txt, and called read(%d, buf, 10).\n", fd);
	buf[size]='\0';
	printf("Those bytes are as follows: %s\n\n", buf);

	l= lseek(fd, 0, SEEK_SET); //Reset the read pointer to the begining
	size = read(fd, buf, 10);
	buf[size]='\0';
	printf("Now seek to the beginning of the file and call read(%d, buf, 10) with offset 0\n", fd);
	printf("Those bytes are as follows: %s\n\n", buf);	
	// seek and read, using SEEK_SET, then print to stdout

	l= lseek(fd, 0, SEEK_CUR);
	printf("lseek(%d, 0, SEEK_CUR) sets the position to the current position = %d\n", fd, l);
	size = read(fd, buf, 3);
	buf[size]='\0';
		printf("Those bytes are as follows: %s\n\n", buf);	
	// seek and read, using SEEK_CUR, then print to stdout
	
	l= lseek(fd, 0, SEEK_SET); //Reset the read pointer to the begining
	size = read(fd, buf, 10);
	buf[size]='\0';	
	printf("Now seek from the beginning of the file again and call read(%d, buf, 10)\n", fd);
	printf("Those bytes are as follows: %s\n\n", buf);
	// seek and read, using SEEK_SET 0, then print to stdout
  
	l= lseek(fd, -10, SEEK_END);
	size = read(fd, buf, 10);
	buf[size]='\0';
	printf("Now seek to the end of the file with offset -10 and call read(%d, buf, 10)\n", fd);
	printf("Those bytes are as follows: %s\n\n", buf);
	// seek and read using SEEK_END offset -10, then print to stdout
 close(fd);
 
  return 0;

}
