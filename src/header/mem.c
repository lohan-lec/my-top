/*
** EPITECH PROJECT, 2024
** mem gathering infos functions
** File description:
** mem
*/

#include "../../include/my.h"

mem_t calculate_mems(mem_t *temp, mem_t *mem)
{
    mem->buff = (temp->buff + temp->cached + temp->sreclaimable) / 1024.0;
    mem->used = (temp->total - temp->avail) / 1024.0;
    mem->swap_used = (temp->swap_total - temp->swap_free) / 1024.0;
    mem->free = temp->free / 1024.0;
    mem->swap_free = temp->swap_free / 1024.0;
    mem->total = temp->total / 1024.0;
    mem->swap_total = temp->swap_total / 1024.0;
    mem->avail = temp->avail / 1024.0;
    return *mem;
}

void search_mems(mem_t *temp)
{
    FILE *stream = fopen("/proc/meminfo", "r");
    char line[256];

    while (fgets(line, sizeof(line), stream)) {
        if (sscanf(line, "MemTotal: %lf kB", &temp->total) == 1)
            continue;
        if (sscanf(line, "MemFree: %lf kB", &temp->free) == 1)
            continue;
        if (sscanf(line, "MemAvailable: %lf kB", &temp->avail) == 1)
            continue;
        if (sscanf(line, "Buffers: %lf kB", &temp->buff) == 1)
            continue;
        if (sscanf(line, "Cached: %lf kB", &temp->cached) == 1)
            continue;
        if (sscanf(line, "SReclaimable: %lf kB", &temp->sreclaimable) == 1)
            continue;
    }
    fclose(stream);
}

void search_swap(mem_t *temp)
{
    FILE *stream = fopen("/proc/meminfo", "r");
    char line[256];

    while (fgets(line, sizeof(line), stream)) {
        if (sscanf(line, "SwapTotal: %lf kB", &temp->swap_total) == 1)
            continue;
        if (sscanf(line, "SwapFree: %lf kB", &temp->swap_free) == 1)
            continue;
    }
    fclose(stream);
}

mem_t mem_usage(void)
{
    mem_t mem;
    mem_t temp;

    search_mems(&temp);
    search_swap(&temp);
    return calculate_mems(&temp, &mem);
}
