/*
** EPITECH PROJECT, 2024
** other important functions
** File description:
** other
*/

#include "../../include/my.h"

int my_nap(double s)
{
    int microseconds = (int)(s * 1000000);

    for (int i = 0; i < microseconds; i += 1000) {
        usleep(1000);
        switch (getch()) {
            case 'q':
                return -1;
            case KEY_DOWN:
                return 1;
            case KEY_UP:
                return 2;
            case 'k':
                return 3;
        }
    }
    return 0;
}

int handle_input(double refresh, int *scroll, header_t *header)
{
    switch (my_nap(refresh)) {
        case -1:
            curs_set(1);
            endwin();
            return -1;
        case 1:
            (*scroll)++;
            break;
        case 2:
            if (*scroll > 0)
                (*scroll)--;
            break;
        case 3:
            send_signal(header);
            break;
    }
    return 0;
}

struct dirent *read_the_dir(struct dirent **file_infos, DIR **folder)
{
    *file_infos = readdir(*folder);
    return *file_infos;
}

int is_folder_digit(char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
        if (!isdigit(name[i]))
            return 0;
    return 1;
}
