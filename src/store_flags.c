/*
** EPITECH PROJECT, 2024
** Stores flags
** File description:
** store_flags
*/

#include "../include/my.h"

int store_infos(char *flag, char *argument, config_t *config)
{
    if (strcmp(flag, "-U") == 0)
        config->username = argument;
    if (strcmp(flag, "-d") == 0)
        config->refresh_rate = atof(argument);
    if (strcmp(flag, "-n") == 0)
        config->max_frames = atoi(argument);
    return 0;
}

int get_flags(int ac, char **av, config_t *config)
{
    for (int i = 1; i < ac - 1; i++) {
        if (av[i][0] == '-') {
            store_infos(av[i], av[i + 1], config);
            i++;
        }
    }
    return 0;
}
