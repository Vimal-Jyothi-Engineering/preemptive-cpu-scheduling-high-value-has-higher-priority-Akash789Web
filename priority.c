#include <stdio.h>
#include <string.h>

struct process {
    char pid[10];
    int at, bt, pr;
    int ct, tat, wt;
    int done;
};

int main() {

    struct process p[20];
    int n=0;

    char first[10];
    scanf("%s", first);

    if(first[0]=='P'){  
        strcpy(p[0].pid, first);
        scanf("%d %d %d",&p[0].at,&p[0].bt,&p[0].pr);
        n=1;

        while(scanf("%s",p[n].pid)==1){
            scanf("%d %d %d",&p[n].at,&p[n].bt,&p[n].pr);
            n++;
        }
    }
    else{
        n=atoi(first);
        for(int i=0;i<n;i++)
            scanf("%s %d %d %d",p[i].pid,&p[i].at,&p[i].bt,&p[i].pr);
    }

    for(int i=0;i<n;i++) p[i].done=0;

    int completed=0,time=0;

    while(completed<n){

        int idx=-1;
        int max_pr=-1;

        for(int i=0;i<n;i++){

            if(p[i].at<=time && p[i].done==0){

                if(p[i].pr>max_pr){
                    max_pr=p[i].pr;
                    idx=i;
                }
            }
        }

        if(idx==-1){
            time++;
        }
        else{

            time+=p[idx].bt;
            p[idx].ct=time;

            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;

            p[idx].done=1;
            completed++;
        }
    }

    float avg_wt=0,avg_tat=0;

    printf("Waiting Time:\n");
    for(int i=0;i<n;i++){
        printf("%s %d\n",p[i].pid,p[i].wt);
        avg_wt+=p[i].wt;
    }

    printf("Turnaround Time:\n");
    for(int i=0;i<n;i++){
        printf("%s %d\n",p[i].pid,p[i].tat);
        avg_tat+=p[i].tat;
    }

    printf("Average Waiting Time: %.2f\n",avg_wt/n);
    printf("Average Turnaround Time: %.2f\n",avg_tat/n);

    return 0;
}￼Enter
