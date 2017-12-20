#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void delta_encode(char * buffer, int length) {
    char last = 0;
    for (int i = 0; i < length; i++) {
        char current = buffer[i];
        buffer[i] = current - last;
        last = current;
    }
}

int main (int argc, char **argv)
{
	if (argc == 1)
    {
        printf("ERROR! No file given.\n");
        return (0);
    }
    else if (argc > 2)
    {
        printf("ERROR! Too many files, try doing them one at a time.\n");
    }
	char * buffer = 0;
	long length = 0;
	FILE * f;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR! Bad file name\n");
        return 0;
    }
    close(fd);
	if ((f = fopen(argv[1], "rb")) != NULL)
	{

		fseek (f, 0, SEEK_END);
        length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length + 1);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
		buffer[length] = '\0';
	}
	int i = buffer[0];
	buffer[0] = buffer[length - 1];
	buffer[length - 1] = i;

	i = buffer[0];
	buffer[0] = buffer[length - 1];
	buffer[length - 1] = i;

	if (buffer)
    {
        delta_encode(buffer, length);
        FILE *fd2 =fopen("WOODY_TEMP_CODE.c", "w");
        fprintf(fd2, "#include <unistd.h>\n"
                "#include <stdio.h>\n"
                "#include <fcntl.h>\n"
                "#include <stdlib.h>\n"
                "#include <string.h>\n"
                "void delta_decode(int * buffer, int length) {int last = 0;for (int i = 0; i < length; i++) {int delta = buffer[i];buffer[i] = delta + last;last = buffer[i];}}\n"
                "int main(int argc, char **argv){write(1, \"....WOODY....\\n\", 6);long int len = %li;int tab[%li] = {%i", length, length, buffer[0]);
        int counter = 1;
        while (counter < length)
        {
            fprintf(fd2, ", %i", buffer[counter]);
            counter++;
        }
        fprintf(fd2, "};\ndelta_decode(tab, len);int fd = open(\"WOODY_TEMP_EXEC\", O_CREAT | O_TRUNC | O_WRONLY);int i = 0; while (i < len){write(fd, &tab[i], 1);i++;};close(fd);system(\"chmod 777 WOODY_TEMP_EXEC\");if(argc == 1 && argv[0]){system(\"./WOODY_TEMP_EXEC;\");}else{char flags[1024];int argcounter = 1;strcpy(flags, \"./WOODY_TEMP_EXEC\");while (argcounter < argc){strcat(flags, \" \");strcat(flags, argv[argcounter]);argcounter++;}system(flags);}system(\"rm WOODY_TEMP_EXEC\");}");
        fclose(fd2);
        system("chmod 777 WOODY_TEMP_CODE.c; gcc -Wall -Werror -Wextra WOODY_TEMP_CODE.c -o woody; rm WOODY_TEMP_CODE.c");
	}
}
