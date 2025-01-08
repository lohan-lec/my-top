/*
** EPITECH PROJECT, 2024
** function related to retrieving infos in the status file
** File description:
** user_infos
*/

#include "../../include/my.h"


char *get_user_name(int uid)
{
    struct passwd *pw;
    char *user = malloc(sizeof(char) * 9);

    if (user == NULL)
        return NULL;
    pw = getpwuid(uid);
    if (strlen(pw->pw_name) > 7){
        for (int i = 0; i < 7; i++)
            user[i] = pw->pw_name[i];
        user[7] = '+';
        user[8] = '\0';
    } else {
        strncpy(user, pw->pw_name, 8);
        user[strlen(pw->pw_name) + 1] = '\0';
    }
    return user;
}

int get_statm_infos(char *filename, int *error, process_t *infos)
{
    char path_statm[512];
    FILE *statm;

    sprintf(path_statm, "/proc/%s/statm", filename);
    statm = fopen(path_statm, "r");
    if (statm == NULL) {
        *error = 1;
        return 0;
    }
    fscanf(statm, "%*u %*u %lu", &infos->shr);
    fclose(statm);
    return 0;
}

int get_status_infos(char *filename, int *error, process_t *infos)
{
    char path_status[512];
    FILE *status;
    char line[256];
    int uid = 0;

    sprintf(path_status, "/proc/%s/status", filename);
    status = fopen(path_status, "r");
    if (status == NULL){
        *error = 1;
        return 0;
    }
    while (fgets(line, sizeof(line), status))
        if (sscanf(line, "Uid:    %d", &uid) == 1)
            continue;
    fclose(status);
    infos->user = get_user_name(uid);
    get_statm_infos(filename, error, infos);
    return 0;
}
