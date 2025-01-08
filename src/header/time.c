/*
** EPITECH PROJECT, 2024
** Time retrieving infos for the header of my_top
** File description:
** time
*/

#include "../../include/my.h"

char *get_time(void)
{
    FILE *stream = fopen("/proc/driver/rtc", "r");
    char *time = malloc(sizeof(char) * 9);

    if (stream == NULL || time == NULL)
        return NULL;
    fscanf(stream, "rtc_time        : %8s", time);
    fclose(stream);
    return time;
}

void format_uptime(int m, int h, int d, char **uptime)
{
    if (d >= 1 && h >= 1){
        sprintf(*uptime, "up %d days, %2d:%02d", d, h, m);
        return;
    }
    if (d >= 1 && h < 1){
        sprintf(*uptime, "up %d days, %2d min", d, m);
        return;
    }
    if (d < 1 && h >= 1){
        sprintf(*uptime, "up %2d:%02d", h, m);
        return;
    }
    if (d < 1 && h < 1){
        sprintf(*uptime, "up %d min", m);
        return;
    }
}

char *uptime(void)
{
    FILE *stream = fopen("/proc/uptime", "r");
    char *uptime = malloc(sizeof(char) * 18);
    int s;
    int h;
    int m;
    int d;

    if (stream == NULL || uptime == NULL)
        return NULL;
    fscanf(stream, "%d.", &s);
    m = (s % 3600) / 60;
    h = (s % 86400) / 3600;
    d = s / 86400;
    format_uptime(m, h, d, &uptime);
    fclose(stream);
    return uptime;
}
