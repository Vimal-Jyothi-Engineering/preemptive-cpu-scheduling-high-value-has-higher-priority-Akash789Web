#include <stdio.h>
#include <string.h>

struct process
{
    char pid[10];
    int at, bt, pr;
    int rt;
    int ct, wt, tat;
};

int main()
{
    int n;
    scanf("%d", &n);

    struct process p[20];

    for(int i = 0; i < n; i++)
    {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
    }

    int completed = 0;
    int time = 0;

    while(completed < n)
    {
        int idx = -1;
        int max_pr = -1;

        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time && p[i].rt > 0)
            {
                if(p[i].pr > max_pr)
                {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if(p[idx].rt == 0)
        {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s %d\n", p[i].pid, p[i].wt);
        total_wt += p[i].wt;
    }

    printf("\nTurnaround Time:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s %d\n", p[i].pid, p[i].tat);
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt/n);
    printf("Average Turnaround Time: %.2f\n", total_tat/n);

    return 0;
}
