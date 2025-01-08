/*
** EPITECH PROJECT, 2024
** Linked list related funcs
** File description:
** linked_list
*/

#include "../../include/my.h"

void add_to_chained_list
(process_t **infos, process_t *new_info, int error)
{
    process_t *current = *infos;

    if (error == 1) {
        free(new_info);
        return;
    }
    if (*infos == NULL) {
        *infos = new_info;
        new_info->next = NULL;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_info;
    new_info->next = NULL;
}
