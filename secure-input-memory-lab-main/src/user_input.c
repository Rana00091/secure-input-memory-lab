#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_input.h"

char *read_username(void)
{
    char buffer[32];
    char *username = NULL;
    size_t len;
    int c;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[--len] = '\0';
    }
    else
    {
        c = getchar();

        if (c != '\n' && c != EOF)
        {
            while (c != '\n' && c != EOF)
                c = getchar();

            return NULL;
        }
    }

    if (len == 0)
        return NULL;

    username = malloc(len + 1);
    if (username == NULL)
        return NULL;

    strcpy(username, buffer);

    return username;
}
