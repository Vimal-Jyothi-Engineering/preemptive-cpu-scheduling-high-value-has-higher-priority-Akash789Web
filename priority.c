#include <stdio.h>
#include <string.h>

struct process {
    char pid[10];
    int at, bt, pr;
    int rt;
    int ct, wt, tat;
};

int main() {
    int n;
    scanf("%d", &n);

    struct process p[20];
    int i;

    for (i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].ct = 0;  /* Initialize completion time */
    }

    int completed = 0, time = 0;
    int idx, max_pr;

    /* Find the minimum arrival time to avoid unnecessary idle increments */
    int min_at = p[0].at;
    for (i = 1; i < n; i++) {
        if (p[i].at < min_at)
            min_at = p[i].at;
    }
    if (time < min_at)
        time = min_at;

    while (completed < n) {
        idx = -1;
        max_pr = -1;

        for (i = 0; i < n; i++) {
            /* Consider only arrived and not-yet-completed processes */
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr > max_pr ||
                   (p[i].pr == max_pr && idx != -1 && p[i].at < p[idx].at)) {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            time++;
            if (p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        } else {
            /* CPU is idle — jump to the next process arrival */
            int next_at = -1;
            for (i = 0; i < n; i++) {
                if (p[i].rt > 0) {
                    if (next_at == -1 || p[i].at < next_at)
                        next_at = p[i].at;
                }
            }
            if (next_at != -1)
                time = next_at;
            else
                time++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        avg_wt  += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("Waiting Time:\n");
    for (i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].wt);

    printf("\nTurnaround Time:\n");
    for (i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].tat);

    printf("\nAverage Waiting Time: %.2f\n",      avg_wt  / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
