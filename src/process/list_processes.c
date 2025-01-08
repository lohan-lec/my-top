/*
** EPITECH PROJECT, 2024
** Functions that store process infos
** File description:
** list_processes
*/

#include "../../include/my.h"

static int get_total_state(process_t *infos, config_t *config)
{
    switch (infos->state) {
        case 'R':
            config->running_procs++;
            break;
        case 'S':
        case 'D':
        case 'I':
            config->sleeping_procs++;
            break;
        case 'T':
        case 't':
            config->stopped_procs++;
            break;
        case 'Z':
        case 'X':
            config->zombie_procs++;
            break;
    }
    return 0;
}

void proceed_process_2(FILE *stat, int *error, process_t *infos)
{
    infos->comm = malloc(sizeof(char) * 256);
    if (infos->comm == NULL) {
        *error = 1;
        fclose(stat);
        return;
    }
    if (fscanf(stat,
    "%d (%[^)]) %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",
    &infos->pid, infos->comm, &infos->state,
    &infos->utime, &infos->stime) < 5) {
        *error = 1;
    }
    if (fscanf(stat, "%*d %*d %ld %ld %*d %*d %lu %lu %ld",
    &infos->priority, &infos->nice, &infos->starttime,
    &infos->vsize, &infos->rss) < 5) {
        *error = 1;
    }
}

void proceed_process
(char *filename, int *error, process_t *infos, config_t *config)
{
    char path_stat[512];
    FILE *stat;

    sprintf(path_stat, "/proc/%s/stat", filename);
    stat = fopen(path_stat, "r");
    if (stat == NULL) {
        *error = 1;
        return;
    }
    proceed_process_2(stat, error, infos);
    fclose(stat);
    if (*error == 1)
        return;
    get_total_state(infos, config);
    get_status_infos(filename, error, infos);
    infos->cpu_percent = get_cpu_usage(infos, config);
}

int digit_folder
(process_t **infos, struct dirent *file_infos, DIR *folder, config_t *config)
{
    process_t *new_info;
    int error = 0;

    if (is_folder_digit(file_infos->d_name)) {
        new_info = malloc(sizeof(process_t));
        if (new_info == NULL) {
            closedir(folder);
            return 84;
        }
        memset(new_info, 0, sizeof(process_t));
        proceed_process(file_infos->d_name, &error, new_info, config);
        if (error == 1) {
            free(new_info);
            return 0;
        }
        add_to_chained_list(infos, new_info, error);
    }
    return 0;
}

int proceed_folder(process_t **infos, config_t *config)
{
    DIR *folder;
    struct dirent *file_infos;

    folder = opendir("/proc");
    if (folder == NULL)
        exit(84);
    while (read_the_dir(&file_infos, &folder) != NULL) {
        digit_folder(infos, file_infos, folder, config);
    }
    return closedir(folder);
}
