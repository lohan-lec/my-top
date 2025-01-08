/*
** EPITECH PROJECT, 2024
** Function that helps me display the infos
** File description:
** display_infos
*/

#include "../../include/my.h"

void init_display(void)
{
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE, -1);
}

static void float_bold(int x, int y, double number)
{
    attrset(A_BOLD);
    mvprintw(x, y, "%4.1f", number);
    attroff(A_BOLD);
}

static void mem_bold(int x, int y, double number)
{
    attrset(A_BOLD);
    mvprintw(x, y, "%7.1f", number);
    attroff(A_BOLD);
}

static void first_line(header_t *header)
{
    mvprintw(0, 0, "top - %s ", header->time);
    mvprintw(0, 15, "%s,", header->uptime);
    mvprintw(0, 17 + strlen(header->uptime), "%7s", header->logged_users);
    mvprintw(0, 26 + strlen(header->uptime),
    "load average: %s", header->loadavg);
}

static void second_line(config_t config)
{
    mvprintw(1, 0, "Tasks: %3d total,", config.running_procs +
    config.sleeping_procs + config.stopped_procs +
    config.zombie_procs);
    mvprintw(1, 18, "%3d running,", config.running_procs);
    mvprintw(1, 31, "%3d sleeping,", config.sleeping_procs);
    mvprintw(1, 45, "%3d stopped,", config.stopped_procs);
    mvprintw(1, 58, "%3d zombie", config.zombie_procs);
}

void third_line(header_t *header)
{
    mvprintw(2, 0, "%%Cpu(s):");
    float_bold(2, 9, header->usage.user);
    mvprintw(2, 14, "us,");
    float_bold(2, 18, header->usage.system);
    mvprintw(2, 23, "sy,");
    float_bold(2, 27, header->usage.nice);
    mvprintw(2, 32, "ni,");
    float_bold(2, 36, header->usage.idle);
    mvprintw(2, 41, "id,");
    float_bold(2, 45, header->usage.iowait);
    mvprintw(2, 50, "wa,");
    float_bold(2, 54, header->usage.irq);
    mvprintw(2, 59, "hi,");
    float_bold(2, 63, header->usage.softirq);
    mvprintw(2, 68, "si,");
    float_bold(2, 72, header->usage.steal);
    mvprintw(2, 77, "st");
}

void fourth_line(header_t *header)
{
    mvprintw(3, 0, "MiB Mem : ");
    mem_bold(3, 10, header->mem.total);
    mvprintw(3, 18, "total,");
    mem_bold(3, 25, header->mem.free);
    mvprintw(3, 33, "free,");
    mem_bold(3, 40, header->mem.used);
    mvprintw(3, 48, "used,");
    mem_bold(3, 55, header->mem.buff);
    mvprintw(3, 63, "buff/cache");
}

void fifth_line(header_t *header)
{
    mvprintw(4, 0, "MiB Swap: ");
    mem_bold(4, 10, header->mem.swap_total);
    mvprintw(4, 18, "total,");
    mem_bold(4, 25, header->mem.swap_free);
    mvprintw(4, 33, "free,");
    mem_bold(4, 40, header->mem.swap_used);
    mvprintw(4, 48, "used.");
    mem_bold(4, 55, header->mem.avail);
    mvprintw(4, 63, "avail Mem");
}

void display_header
(header_t *header, process_t *processes, config_t config, int scroll)
{
    first_line(header);
    second_line(config);
    third_line(header);
    fourth_line(header);
    fifth_line(header);
    title_bar();
    display_processes(processes, scroll, header, config);
}
