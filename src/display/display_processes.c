/*
** EPITECH PROJECT, 2024
** Function related to displaying processes
** File description:
** processes
*/

#include "../../include/my.h"

void title_bar(void)
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for (int i = 0; i < COLS; i++){
        mvprintw(6, i, " ");
    }
    mvprintw(6, 0, "  PID USER      PR  NI    VIRT    RES");
    mvprintw(6, 41, "SHR S  %%CPU  %%MEM     TIME+ COMMAND");
    attroff(COLOR_PAIR(1));
}

void running_time(process_t *current, int x)
{
    unsigned long total_time = current->utime + current->stime;
    double seconds = 0.0;
    int minutes = 0;
    double secs = 0.0;

    seconds = (double)total_time / sysconf(_SC_CLK_TCK);
    minutes = (int)seconds / 60;
    secs = seconds - (minutes * 60);
    if (minutes > 99)
        mvprintw(x, 59, "%03d:%05.2f", minutes, secs);
    else
    mvprintw(x, 60, "%02d:%05.2f", minutes, secs);
}

void display_processes_2(process_t *current, int x, header_t *header)
{
    long page_size = sysconf(_SC_PAGESIZE);

    if (current->vsize >= (1024L * 1024L * 1024L))
        mvprintw(x, 23, "%6.1fg",
        (double)current->vsize / (1024L * 1024L * 1024L));
    else
            mvprintw(x, 24, "%6lu", current->vsize / 1024);
    mvprintw(x, 31, "%6lu", current->rss * (page_size / 1024));
    mvprintw(x, 39, "%5lu", (current->shr * page_size) / 1024);
    mvprintw(x, 45, "%c", current->state);
    mvprintw(x, 47, "%5.1f", current->cpu_percent);
    mvprintw(x, 53, "%5.1f", ((double)(current->rss * page_size) /
    (header->mem.total * 1024 * 1024)) * 100.0);
    running_time(current, x);
    mvprintw(x, 69, "%s", current->comm);
}

static void scroll_if_needed(process_t **current, int scroll, config_t config)
{
    for (int i = 0; i < scroll && *current != NULL; i++){
        while ((*current)->next != NULL && config.username != NULL &&
            strcmp(config.username, (*current)->user) != 0)
            *current = (*current)->next;
        *current = (*current)->next;
    }
}

void display_processes(
    process_t *processes, int scroll, header_t *header, config_t config)
{
    process_t *current = processes;

    scroll_if_needed(&current, scroll, config);
    for (int x = 7; x < LINES - 1 && current != NULL; x++){
        if (x == 7)
            header->pid_to_kill = current->pid;
        if (sort_username(&current, config, &x))
            continue;
        mvprintw(x, 0, "%5d", current->pid);
        mvprintw(x, 6, "%s", current->user ? current->user : "unknown");
        if (current->priority == -100)
            mvprintw(x, 14, "  rt");
        else
            mvprintw(x, 14, "%4ld", current->priority);
        mvprintw(x, 19, "%3ld", current->nice);
        display_processes_2(current, x, header);
        current = current->next;
    }
}
