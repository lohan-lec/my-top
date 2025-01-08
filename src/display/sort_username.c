/*
** EPITECH PROJECT, 2024
** sorts by username
** File description:
** sort_username
*/

#include "../../include/my.h"

int sort_username(process_t **current, config_t config, int *x)
{
        if (config.username != NULL && strcmp(
            config.username, (*current)->user) != 0) {
            *current = (*current)->next;
            (*x)--;
            return 1;
        }
        return 0;
}
