/*
** EPITECH PROJECT, 2024
** Cpu usage retrieving
** File description:
** cpu_usage
*/

#include "../../include/my.h"

int cpu_usage_checks(proc_history_t **history, process_t *infos, int index)
{
    if (*history == NULL) {
        *history = calloc(HASH_SIZE, sizeof(proc_history_t));
        if (!*history)
            return 1;
    }
    if ((*history)[index].pid != infos->pid
    || !(*history)[index].initialized) {
        (*history)[index].pid = infos->pid;
        (*history)[index].utime = infos->utime;
        (*history)[index].stime = infos->stime;
        (*history)[index].initialized = 1;
        return 1;
    }
    return 0;
}

double get_cpu_usage(process_t *infos, config_t *config)
{
    static proc_history_t *history = NULL;
    double cpu_usage = 0.0;
    int index = infos->pid % HASH_SIZE;
    unsigned long hertz = sysconf(_SC_CLK_TCK);
    unsigned long long total_time = infos->utime + infos->stime +
                                    infos->cutime + infos->cstime;
    unsigned long long time_delta = 0;

    if (cpu_usage_checks(&history, infos, index))
        return 0.0;
    time_delta = total_time -
        (history[index].utime + history[index].stime +
        history[index].cutime + history[index].cstime);
    cpu_usage = ((double)time_delta / hertz) / config->refresh_rate * 100.0;
    history[index].utime = infos->utime;
    history[index].stime = infos->stime;
    history[index].cutime = infos->cutime;
    history[index].cstime = infos->cstime;
    return cpu_usage;
}
