/*
** EPITECH PROJECT, 2024
** retrieve the infos of the header
** File description:
** retrieve_infos
*/

#include "../../include/my.h"
#include <utmp.h>

char *my_getloadavg(void)
{
    double avg[2];
    FILE *stream = fopen("/proc/loadavg", "r");
    char *avg_str;
    size_t needed_mem;

    fscanf(stream, "%lf %lf %lf", &avg[0], &avg[1], &avg[2]);
    needed_mem = snprintf(NULL, 0, "%.2f, %.2f, %.2f", avg[0], avg[1], avg[2]);
    avg_str = malloc(needed_mem + 1);
    if (avg_str == NULL)
        return NULL;
    snprintf(avg_str, needed_mem + 1, "%.2f, %.2f, %.2f",
    avg[0], avg[1], avg[2]);
    fclose(stream);
    return avg_str;
}

char *logged_in(void)
{
    FILE *utmp = fopen("/var/run/utmp", "rb");
    char *log = malloc(sizeof(char) * 7);
    int logged_users = 0;
    struct utmp infos;

    if (log == NULL)
        return NULL;
    if (utmp == NULL){
        sprintf(log, "%d user", 0);
        return log;
    }
    while (fread(&infos, sizeof(struct utmp), 1, utmp) == 1){
        if (infos.ut_type == USER_PROCESS)
            logged_users++;
    }
    fclose(utmp);
    sprintf(log, "%d user", logged_users);
    return log;
}

header_t header_infos(void)
{
    header_t header;
    int uptime_sec;

    header.total_diff = 0;
    header.time = get_time();
    header.uptime = uptime();
    header.logged_users = logged_in();
    header.loadavg = my_getloadavg();
    header.usage = cpu_load();
    header.mem = mem_usage();
    return header;
}
