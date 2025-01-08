/*
** EPITECH PROJECT, 2024
** sends a signal
** File description:
** send_signal
*/

#include "../../include/my.h"
#include <signal.h>

int get_pid_to_signal(header_t *header)
{
    char input[10] = {0};
    int pid = 0;

    curs_set(1);
    mvprintw(
        5, 0, "PID to signal/kill [default pid = %d]", header->pid_to_kill);
    clrtoeol();
    refresh();
    echo();
    timeout(-1);
    getnstr(input, sizeof(input) - 1);
    noecho();
    if (input[0] != '\0')
        pid = atoi(input);
    else
        pid = header->pid_to_kill;
    return pid;
}

int get_signal_type(int pid)
{
    char sig_input[10] = {0};
    int signal = SIGKILL;

    mvprintw(5, 0, "Send pid %d signal [15/sigterm]", pid);
    clrtoeol();
    refresh();
    echo();
    getnstr(sig_input, sizeof(sig_input) - 1);
    noecho();
    if (sig_input[0] != '\0')
        signal = atoi(sig_input);
    return signal;
}

void handle_signal_send_error(int pid, int signal)
{
    mvprintw(5, 0, "Failed signal pid '%d' with '%d': No such process ",
    pid, signal);
    clrtoeol();
    refresh();
    napms(2000);
    clrtoeol();
    refresh();
}

void send_signal(header_t *header)
{
    int pid = 0;
    int signal = 0;

    while (1) {
        pid = get_pid_to_signal(header);
        signal = get_signal_type(pid);
        if (kill(pid, signal) == -1) {
            handle_signal_send_error(pid, signal);
            continue;
        }
        break;
    }
    move(5, 0);
    clrtoeol();
    refresh();
    curs_set(0);
    timeout(0);
}
