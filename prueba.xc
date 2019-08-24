 #include <unistd.h>
#include <stdio.h>
int main(void)
{
	size_t cnt = 0;
	int i = 0;
	char c;
	char buffer[20];
	while(read(STDIN_FILENO, &c, 1) == 1)
	{
		printf("%d\n", (int)cnt);
		if (c == 4 && cnt == 0)
			break;
		if(c == '\n')
		{
			buffer[cnt] = '\n';
			buffer[cnt + 1] = 0;
			break;
		}

		buffer[cnt++] = c;
	}
	if (cnt)
		printf("%s\n", buffer);
	printf("ejecuta\n");
	return 1;
}
