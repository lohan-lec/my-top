/*
** EPITECH PROJECT, 2024
** header file for my_top
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #define _DEFAULT_SOURCE
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ncurses.h>
    #include <string.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <pwd.h>
    #include <unistd.h>
    #include <sys/sysinfo.h>
    #include <sys/types.h>

    #if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
        #define HASH_SIZE 65536
    #elif defined(__powerpc64__) || defined(__ppc64__) || defined(__ia64__)
        #define HASH_SIZE 65536
    #else
        #define HASH_SIZE 32768
    #endif

typedef struct cpu_values {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
} cpu_values_t;

typedef struct cpu_percents {
    double user;
    double nice;
    double system;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
} cpu_percents_t;

typedef struct cpu {
    cpu_values_t prev_stats;
    cpu_values_t curr_stats;
    cpu_percents_t usage;
    unsigned long total_diff;
} cpu_t;

typedef struct mem {
    double total;
    double free;
    double used;
    double buff;
    double cached;
    double sreclaimable;
    double swap_total;
    double swap_free;
    double swap_used;
    double avail;
}mem_t;

typedef struct header {
    unsigned long total_diff;
    char *time;
    char *uptime;
    char *logged_users;
    char *loadavg;
    cpu_percents_t usage;
    mem_t mem;
    pid_t pid_to_kill;
}header_t;

typedef struct process {
    int pid;
    char *user;
    long priority;
    long nice;
    long unsigned vsize;
    long rss;
    long unsigned shr;
    char state;
    double cpu_percent;
    double mem_percent;
    unsigned long utime;
    unsigned long prev_utime;
    unsigned long stime;
    unsigned long prev_stime;
    unsigned long cutime;
    unsigned long cstime;
    unsigned long starttime;
    int ppid;
    char *comm;
    struct process *next;
} process_t;

typedef struct proc_history {
    pid_t pid;
    unsigned long long utime;
    unsigned long long stime;
    unsigned long long cutime;
    unsigned long long cstime;
    int initialized;
} proc_history_t;

typedef struct config {
    int uptime_sec;
    int count_frames;
    int running_procs;
    int sleeping_procs;
    int stopped_procs;
    int zombie_procs;
    char *username;
    double refresh_rate;
    int max_frames;
} config_t;

char *get_time(void);
char *uptime(void);
cpu_percents_t cpu_load(void);
header_t header_infos(void);
void init_display(void);
mem_t mem_usage(void);
void display_header
(header_t *header, process_t *processes, config_t config, int scroll);
void title_bar(void);
int proceed_folder(process_t **infos, config_t *config);
void display_processes(
    process_t *processes, int scroll, header_t *header, config_t config);
int get_status_infos(char *filename, int *error, process_t *infos);
int handle_input(double refresh, int *scroll, header_t *header);
int digit_folder
(process_t **infos, struct dirent *file_infos, DIR *folder, config_t *config);
void free_all(header_t *header, process_t *processes, config_t *config);
struct dirent *read_the_dir(struct dirent **file_infos, DIR **folder);
int is_folder_digit(char *name);
void add_to_chained_list(process_t **infos, process_t *new_info, int error);
int cpu_usage_checks(proc_history_t **history, process_t *infos, int index);
double get_cpu_usage(process_t *infos, config_t *config);
int get_flags(int ac, char **av, config_t *config);
void send_signal(header_t *header);
int sort_username(process_t **current, config_t config, int *x);

#endif /* !MY_H_ */
