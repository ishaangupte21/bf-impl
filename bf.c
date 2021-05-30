#include "bf.h"

char mem[30000] = {'\0'}, *ptr = mem;

char *getSource(const char *path)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("Could not open file from path specified\n");
        exit(EXIT_FAILURE);
    }
    char *source = NULL, c;
    size_t pos = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (source == NULL)
        {
            source = malloc(sizeof(char));
            if (source == NULL)
            {
                printf("Could not allocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            source = realloc(source, sizeof(source) + sizeof(char));
        }
        source[pos++] = c;
    }
    fclose(file);
    source = realloc(source, sizeof(source) + sizeof(char));
    source[pos] = '\0';
    return source;
}

void interpret(const char *source)
{
    size_t i = 0;
    while (i < strlen(source))
    {
        char c = source[i];
        // printf("%c\n", c);
        if (c == '>')
        {
            ++ptr;
        }
        else if (c == '<')
        {
            --ptr;
        }
        else if (c == '+')
        {
            ++(*ptr);
        }
        else if (c == '-')
        {
            --(*ptr);
        }
        else if (c == '.')
        {
            printf("%c", *ptr);
        }
        else if (c == ',')
        {
            *ptr = getchar();
        }
        else if (c == '[')
        {
            char *nestedSource = NULL, d;
            size_t bracketCount = 1, j = i + 1, nsPos = 0;
            while (bracketCount > 0)
            {
                d = source[j];
                // printf("%c\n", d);
                if (d == ']')
                {
                    bracketCount--;
                }
                else
                {
                    if (d == '[')
                    {
                        bracketCount++;
                    }
                    if (nestedSource == NULL)
                    {
                        nestedSource = malloc(sizeof(char));
                        if (nestedSource == NULL)
                        {
                            printf("Could not allocate memory\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        nestedSource = realloc(nestedSource, sizeof(nestedSource) + sizeof(char));
                    }
                    nestedSource[nsPos++] = d;
                }
                j++;
            }
            nestedSource = realloc(nestedSource, sizeof(nestedSource) + sizeof(char));
            nestedSource[nsPos] = '\0';
            while (*ptr)
            {
                interpret(nestedSource);
            }
            i = j - 1;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Too few arguements\n");
        return 1;
    }
    const char *source = getSource(argv[2]);
    if (strcmp("run", argv[1]) == 0)
    {
        // interpret the code
        interpret(source);
    }
    else
    {
        printf("Compiler not yet implemented\n");
        exit(EXIT_FAILURE);
    }
}