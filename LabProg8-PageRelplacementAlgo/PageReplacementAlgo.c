#include <stdio.h>

int find(int p,int f[],int n)
{
    for(int i=0; i<n; i++)if(f[i]==p)return i;
    return -1;
}
void show(int f[],int n)
{
    for(int i=0; i<n; i++)printf(f[i]==-1?" - ":" %d ",f[i]);
}

void FIFO(int p[],int m,int n)
{
    int f[n],i,h=0,t=0;
    for(i=0; i<n; i++)f[i]=-1;
    printf("\nFIFO:\n");
    for(i=0; i<m; i++)
    {
        if(find(p[i],f,n)==-1)
        {
            f[t]=p[i];
            t=(t+1)%n;
            printf("Page %d MISS |",p[i]);
        }
        else
        {
            h++;
            printf("Page %d HIT  |",p[i]);
        }
        show(f,n);
        printf("\n");
    }
    printf("Hits=%d Miss=%d Ratio=%.2f\n",h,m-h,(float)h/(m-h));
}

void Optimal(int p[],int m,int n)
{
    int f[n],i,h=0;
    for(i=0; i<n; i++)f[i]=-1;
    printf("\nOptimal:\n");
    for(i=0; i<m; i++)
    {
        if(find(p[i],f,n)==-1)
        {
            int r=-1,farth=i;
            for(int j=0; j<n; j++)
            {
                int k;
                for(k=i+1; k<m; k++)if(f[j]==p[k])
                    {
                        if(k>farth)
                        {
                            farth=k;
                            r=j;
                        }
                        break;
                    }
                if(k==m)
                {
                    r=j;
                    break;
                }
            }
            if(r==-1)r=0;
            f[r]=p[i];
            printf("Page %d MISS |",p[i]);
        }
        else
        {
            h++;
            printf("Page %d HIT  |",p[i]);
        }
        show(f,n);
        printf("\n");
    }
    printf("Hits=%d Miss=%d Ratio=%.2f\n",h,m-h,(float)h/(m-h));
}

void LRU(int p[],int m,int n)
{
    int f[n],t[n],i,h=0;
    for(i=0; i<n; i++)f[i]=-1,t[i]=-1;
    printf("\nLRU:\n");
    for(i=0; i<m; i++)
    {
        int pos=find(p[i],f,n);
        if(pos==-1)
        {
            int l=0;
            for(int j=1; j<n; j++)if(t[j]<t[l])l=j;
            f[l]=p[i];
            t[l]=i;
            printf("Page %d MISS |",p[i]);
        }
        else
        {
            h++;
            t[pos]=i;
            printf("Page %d HIT  |",p[i]);
        }
        show(f,n);
        printf("\n");
    }
    printf("Hits=%d Miss=%d Ratio=%.2f\n",h,m-h,(float)h/(m-h));
}

int main()
{
    int n,m;
    printf("Frames: ");
    scanf("%d",&n);
    printf("Pages: ");
    scanf("%d",&m);
    int p[m];
    printf("Enter reference string:\n");
    for(int i=0; i<m; i++)scanf("%d",&p[i]);
    FIFO(p,m,n);
    Optimal(p,m,n);
    LRU(p,m,n);
}
