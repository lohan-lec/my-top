/*
** EPITECH PROJECT, 2024
** CPU Load information related funcs (hard asf)
** File description:
** cpu_load
*/

#include "../../include/my.h"


void calculate_percentages(cpu_t *val)
{
    unsigned long user_diff = val->curr_stats.user - val->prev_stats.user;
    unsigned long nice_diff = val->curr_stats.nice - val->prev_stats.nice;
    unsigned long system_diff = val->curr_stats.system -
    val->prev_stats.system;
    unsigned long idle_diff = val->curr_stats.idle - val->prev_stats.idle;
    unsigned long iowait_diff = val->curr_stats.iowait -
    val->prev_stats.iowait;
    unsigned long irq_diff = val->curr_stats.irq - val->prev_stats.irq;
    unsigned long softirq_diff = val->curr_stats.softirq -
    val->prev_stats.softirq;
    unsigned long steal_diff = val->curr_stats.steal - val->prev_stats.steal;

    val->usage.user = (double)user_diff / val->total_diff * 100;
    val->usage.nice = (double)nice_diff / val->total_diff * 100.0;
    val->usage.system = (double)system_diff / val->total_diff * 100;
    val->usage.idle = (double)idle_diff / val->total_diff * 100;
    val->usage.iowait = (double)iowait_diff / val->total_diff * 100;
    val->usage.irq = (double)irq_diff / val->total_diff * 100;
    val->usage.softirq = (double)softirq_diff / val->total_diff * 100;
    val->usage.steal = (double)steal_diff / val->total_diff * 100;
}

unsigned long total_diff(cpu_t val)
{
    unsigned long prev_total = val.prev_stats.user + val.prev_stats.nice +
    val.prev_stats.system + val.prev_stats.idle + val.prev_stats.iowait +
    val.prev_stats.irq + val.prev_stats.softirq + val.prev_stats.steal;
    unsigned long curr_total = val.curr_stats.user + val.curr_stats.nice +
    val.curr_stats.system + val.curr_stats.idle + val.curr_stats.iowait +
    val.curr_stats.irq + val.curr_stats.softirq + val.curr_stats.steal;

    return curr_total - prev_total;
}

void init_previous(cpu_values_t *prev_stats)
{
    prev_stats->idle = 0;
    prev_stats->iowait = 0;
    prev_stats->irq = 0;
    prev_stats->nice = 0;
    prev_stats->softirq = 0;
    prev_stats->steal = 0;
    prev_stats->system = 0;
    prev_stats->user = 0;
}

void store_values(cpu_values_t *prev_stats, cpu_values_t curr_stats)
{
    *prev_stats = curr_stats;
}

cpu_percents_t cpu_load(void)
{
    FILE *stream = fopen("/proc/stat", "r");
    static cpu_t val;
    static int first_time = 0;

    if (first_time == 0)
        init_previous(&val.prev_stats);
    fscanf(stream, "cpu  %lu %lu %lu %lu %lu %lu %lu %lu",
    &val.curr_stats.user, &val.curr_stats.nice, &val.curr_stats.system,
    &val.curr_stats.idle, &val.curr_stats.iowait, &val.curr_stats.irq,
    &val.curr_stats.softirq, &val.curr_stats.steal);
    val.total_diff = total_diff(val);
    calculate_percentages(&val);
    fclose(stream);
    store_values(&val.prev_stats, val.curr_stats);
    first_time++;
    return val.usage;
}
