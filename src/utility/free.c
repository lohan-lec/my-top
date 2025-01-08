/*
** EPITECH PROJECT, 2024
** Free functions
** File description:
** free
*/

#include "../../include/my.h"

void free_header(header_t *header)
{
    if (header->time != NULL)
        free(header->time);
    if (header->uptime != NULL)
        free(header->uptime);
    if (header->logged_users != NULL)
        free(header->logged_users);
    if (header->loadavg != NULL)
        free(header->loadavg);
}

void free_all(header_t *header, process_t *processes, config_t *config)
{
    process_t *current = processes;
    process_t *next;

    config->running_procs = 0;
    config->sleeping_procs = 0;
    config->stopped_procs = 0;
    config->zombie_procs = 0;
    free_header(header);
    while (current != NULL) {
        next = current->next;
        free(current->user);
        free(current->comm);
        free(current);
        current = next;
    }
}
