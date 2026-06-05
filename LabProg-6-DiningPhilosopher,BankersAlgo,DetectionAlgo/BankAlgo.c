#include <stdio.h>

int main() {
    int n,m,i,j,k,c=0,p,found;
    int a[10][10],max[10][10],need[10][10];
    int avail[10],f[10]={0},safe[10],req[10];

    printf("Processes Resources: ");
    scanf("%d%d",&n,&m);

    printf("Allocation:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&a[i][j]);

    printf("Max:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            scanf("%d",&max[i][j]);
            need[i][j]=max[i][j]-a[i][j];
        }

    printf("Available:\n");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    while(c<n){
        found=0;

        for(i=0;i<n;i++){
            if(!f[i]){

                for(j=0;j<m && need[i][j]<=avail[j];j++);

                if(j==m){
                    for(k=0;k<m;k++)
                        avail[k]+=a[i][k];

                    safe[c++]=i;
                    f[i]=1;
                    found=1;
                }
            }
        }

        if(!found){
            printf("Unsafe State");
            return 0;
        }
    }

    printf("Safe Sequence: ");
    for(i=0;i<n;i++)
        printf("P%d ",safe[i]);

    printf("\n\nProcess Requesting: ");
    scanf("%d",&p);

    printf("Request Vector: ");
    for(i=0;i<m;i++)
        scanf("%d",&req[i]);

    for(i=0;i<m;i++){
        if(req[i]>need[p][i] || req[i]>avail[i]){
            printf("Request Denied");
            return 0;
        }

        avail[i]-=req[i];
        a[p][i]+=req[i];
        need[p][i]-=req[i];
    }

    printf("Request Granted");

    return 0;
}
