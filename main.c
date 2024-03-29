#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - Monty code interpreter
 * @argc: number of arguments
 * @argv: Monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *content;
	FILE *file;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;
	unsigned int counter = 0;
	size_t content_len;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	bus.file = file;

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (read_line > 0)
	{
		content = NULL;
		if (fgets(content, size, file) == NULL)
			break;

		bus.content = content;
		counter++;

		content_len = strlen(content);
		if (content_len > 0 && content[content_len - 1] == '\n')
			content[content_len - 1] = '\0';

		execute(content, &stack, counter, file);
		free(content);
	}

	free_stack(stack);
	fclose(file);

	return (0);
}
