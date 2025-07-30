#include "chmod.h"

mode_t parse_input(const char* input)
{
    mode_t mode = 0;

    int is_number = 1;
    int i = 0;

    while (input[i] != '\0')
    {
        if (input[i] < '0' || input[i] > '9')
        {
            is_number = 0;
            break;
        }
        i++;
    }

    if (is_number)
    {
        mode = strtol(input, NULL, 8);
        return mode;
    }

    int is_symbolic = 1;
    i = 0;

    while (input[i] != '\0')
    {
        char c = input[i];
        if (c != 'r' && c != 'w' && c != 'x' && c != '-')
        {
            is_symbolic = 0;
            break;
        }
        i++;
    }

    if ( i != 9)
    {
        is_symbolic = 0;
    }

    if (is_symbolic)
    {
        if (input[0] == 'r') mode |= S_IRUSR;
        if (input[1] == 'w') mode |= S_IWUSR;
        if (input[2] == 'x') mode |= S_IXUSR;
        if (input[3] == 'r') mode |= S_IRGRP;
        if (input[4] == 'w') mode |= S_IWGRP;
        if (input[5] == 'x') mode |= S_IXGRP;
        if (input[6] == 'r') mode |= S_IROTH;
        if (input[7] == 'w') mode |= S_IWOTH;
        if (input[8] == 'x') mode |= S_IXOTH;

        return mode;
    }

    return 0;
}

mode_t modify_mode(mode_t mode, const char* mod)
{
    int who = 0;
    mode_t affected = 0;
    int i = 0;

    while (mod[i] == 'u' || mod[i] == 'g' || mod[i] == 'o' || mod[i] == 'a')
    {
        switch (mod[i])
        {
            case 'u':
                who |= 1;
                break;
            case 'g':
                who |= 2;
                break;
            case 'o':
                who |= 4;
                break;
            case 'a':
                who |= 7;
                break;
        }
        i++;
    }

    if (who == 0)
    {
        who = 7;
    }

    char op = mod[i++];
    if (op != '+' && op != '-' && op != '=')
    {
        return mode;
    }

    while (mod[i])
    {
        mode_t bit = 0;
        switch (mod[i])
        {
            case 'r':
                bit = 4;
                break;
            case 'w':
                bit = 2;
                break;
            case 'x':
                bit = 1;
                break;
            default:
                return mode;
        }

        if (who & 1) 
        {
            affected |= (bit << 6);
        }
        if (who & 2)
        {
            affected |= (bit << 3);
        }
        if (who & 4)
        {
            affected |= (bit);
        }
        i++;
    }

    if (op == '+')
    {
        mode |= affected;
    }
    else if (op == '-')
    {
        mode &= ~affected;
    }
    else if (op == '=')
    {
        if (who & 1)
        {
            mode &= ~0700;
            mode |= (affected & 0700);
        }
        if (who & 2)
        {
            mode &= ~0070;
            mode |= (affected & 0070);
        }
        if (who & 4)
        {
            mode &= ~0007;
            mode |= (affected & 0007);
        }
        
    }
    return mode;
}