/*
** EPITECH PROJECT, 2024
** Main file of the project
** File description:
** main
*/

#include "../include/my.h"

static int loop_iteration
(header_t *header, process_t **processes, config_t *config, int *scroll)
{
    FILE *stream = fopen("/proc/uptime", "r");

    if (stream == NULL)
        return 1;
    erase();
    fscanf(stream, "%d.", &config->uptime_sec);
    fclose(stream);
    proceed_folder(processes, config);
    display_header(header, *processes, *config, *scroll);
    free_all(header, *processes, config);
    *processes = NULL;
    if (handle_input(config->refresh_rate, scroll, header) == -1) {
        return 1;
    }
    refresh();
    return 0;
}

void close_top(header_t *header, process_t *processes, config_t *config)
{
    free_all(header, processes, config);
    curs_set(1);
    endwin();
    exit(0);
}

int main(int ac, char **av)
{
    config_t config = {0, 0, 0, 0, 0, 0, NULL, 3.0, 0};
    header_t header;
    process_t *processes = NULL;
    int scroll = 0;

    init_display();
    keypad(stdscr, TRUE);
    get_flags(ac, av, &config);
    timeout(0);
    while (getch() != 'q') {
        header = header_infos();
        config.count_frames++;
        if (config.max_frames > 0 && config.count_frames > config.max_frames)
            break;
        if (loop_iteration(&header, &processes, &config, &scroll))
            return 0;
    }
    close_top(&header, processes, &config);
}
