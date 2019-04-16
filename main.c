#include <stdio.h>
#include <memory.h>

int main(int argc, char** argv)
{
    if( argc == 2)
    {
        FILE* fp = NULL;
        fp = fopen(argv[1], "rt");

        if( fp != NULL )
        {
            char memory[1024];
            memset(memory, 0, 1024);
            char* pointer = memory;
            char c;
            while((c = fgetc(fp)) != EOF)
            {
                switch (c)
                {
                case '>':
                    pointer++;
                    break;
                case '<':
                    pointer--;
                    break;
                case '+':
                    (*pointer)++;
                    break;
                case '-':
                    (*pointer)--;
                    break;
                case '.':
                    putchar(*pointer);
                    break;
                case ',':
                    *pointer = getchar();
                    break;
                case '[':
                    if(*pointer == 0)
                    {
                        int scope = 0;
                        char h;
                        while((h = fgetc(fp)) != EOF)
                        {
                            if(h == '[')
                            {
                                scope++;
                            }
                            else if(h == ']' && scope == 0)
                            {
                                break;
                            }
                            else if(h == ']' && scope != 0)
                            {
                                scope--;
                            }
                        }
                    }
                    break;
                case ']':
                    if(*pointer != 0)
                    {
                        int scope = 0;
                        char h;
                        fseek(fp, -2, SEEK_CUR);
                        while(ftell(fp) != 0)
                        {
                            h = fgetc(fp);
                            if(h == ']')
                            {
                                scope++;
                            }
                            else if(h == '[' && scope == 0)
                            {
                                break;
                            }
                            else if(h == '[' && scope != 0)
                            {
                                scope--;
                            }
                            fseek(fp, -2, SEEK_CUR);
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            fprintf(stderr, "Cannot open file %s", argv[1]);
        }
    }
    else
    {
        fprintf(stderr, "You must specify brainfuck file for example ./simple-brainfuck-c example.bf");
    }
    
    return 0;
}