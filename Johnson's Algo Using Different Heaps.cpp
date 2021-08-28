./a.out 1=>array
./a.out 2=>binary heap
./a.out 3=>binomial heap
./a.out=>binomial heap
**/


#include <bits/stdc++.h> 
#include<iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct minHeapNode{
    int distance;
    int vertex;
};

struct binomialHeap{
    int dst;
    int vtx;
    int degree;
    struct binomialHeap *child;
    struct binomialHeap *sibling;
    struct binomialHeap *parent;
};

//bellman algo starts
bool bellman(vector<int> adj[],int n,int d[])
{
    int dist[n];
    int i,j,k,v;
    for(i=0;i<n;i++)
    dist[i]=999999;
    dist[n-1]=0;
    vector<int> alist[n];

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j && adj[i][j]!=999999)
            alist[i].push_back(j);
        }
    }


    for(i=1;i<=(n-1);i++)
    {
        for(j=0;j<n;j++)
        {
            if(dist[j]!=999999)
            {
                for(k=0;k<alist[j].size();k++)
                {
                    
                        v=alist[j][k];
                        if(dist[v]>(dist[j]+adj[j][v]))
                        dist[v]=dist[j]+adj[j][v];
                    
                }
            }
        }

    }
    for(j=0;j<n;j++)
        {
            if(dist[j]!=999999)
            {
                for(k=0;k<alist[j].size();k++)
                {
                    
                        v=alist[j][k];
                        if(dist[v]>(dist[j]+adj[j][v]))
                        {
                            cout<<"-1"<<endl;
                            return false;
                        }
                }
            }
        }

            for(i=0;i<(n-1);i++)
            d[i]=dist[i];
        return true;
        
        
}
//bellman algo ends

//binary heap starts
int retValue(int i,int c)
{
    if(c==0)
    return (2*i)+1;
    else if(c==1)
    return (2*i)+2;
    
    return (i-1)/2;
    
}

void swapnode(int position[],struct minHeapNode binaryHeap[],int a,int b)
{
    
    swap(position[binaryHeap[a].vertex],position[binaryHeap[b].vertex]);
    swap(binaryHeap[a],binaryHeap[b]);

}

void decreasekey(int position[],struct minHeapNode binaryHeap[],int n,int a,int b)
{
    int i;
    i=a;
    binaryHeap[i].distance=b;
    while(binaryHeap[retValue(i,2)].distance>binaryHeap[i].distance && i!=0)
    {
        swapnode(position,binaryHeap,i,retValue(i,2));
        i=retValue(i,2);
    }
    
}

void minHeapify(int position[],struct minHeapNode binaryHeap[],int n,int i)
{
    int lt,rt,sml;
    lt=retValue(i,0);
    rt=retValue(i,1); 
    sml=i;
    if(lt<n && binaryHeap[lt].distance<binaryHeap[i].distance)
    sml=lt;
    if(rt<n && binaryHeap[rt].distance<binaryHeap[sml].distance)
    sml=rt;
    if(sml!=i)
    {
        swapnode(position,binaryHeap,i,sml);
        minHeapify(position,binaryHeap,n,sml);
    }

}

struct minHeapNode extractMin(int position[],struct minHeapNode binaryHeap[],int n)
{
    struct minHeapNode sml=binaryHeap[0];
    swapnode(position,binaryHeap,0,n-1);
    minHeapify(position,binaryHeap,n-1,0);
    return sml;

}

void dijkstra_minHeap(vector<int> adj[],vector<int> alist[],int n,int s,int d[])
{
    int i,x,y,siz;
    struct minHeapNode binaryHeap[n];
    for(i=0;i<n;i++)
    {
        binaryHeap[i].distance=999999;
        binaryHeap[i].vertex=i;
        
    }
    int position[n];
    int dist[n];
    for(i=0;i<n;i++)
    {
        dist[i]=999999;
        position[i]=i;
    }
    binaryHeap[s].distance=0;
    dist[s]=0;
    
    for(i=(n-2)/2;i>=0;i--)
    {
        minHeapify(position,binaryHeap,n,i);
    }
    
    siz=n;
    while(siz>0)
    {
        i=0;
        y=(extractMin(position,binaryHeap,siz)).vertex;
        siz--;
        
        while(i<alist[y].size())
        {
            x=alist[y][i];
            if(position[x]<siz)
            {
                dist[x]=min(dist[x],dist[y]+adj[y][x]);
                decreasekey(position,binaryHeap,siz,position[x],dist[x]);
            }
            i++;
        }
    }
    for(i=0;i<n;i++)
    {
        if(dist[i]==999999)
        cout<<dist[i]<<" ";
        else
        {
        int ans=dist[i]+d[i]-d[s];
        cout<<ans<<" ";
        }
    }
    cout<<"\n";
    
}

void call_dijkstra_minHeap(vector<int> adj[],vector<int> alist[],int n,int d[])
{
    for(int i=0;i<n;i++)
    dijkstra_minHeap(adj,alist,n,i,d); 
    
}
//binary heap ends

//binomial heap starts
list<struct binomialHeap*> unionBinomial(list<struct binomialHeap*> listA,list<struct binomialHeap*> listB)
{
    list<struct binomialHeap*> temp;
    list<struct binomialHeap*>::iterator iter1=listA.begin();
    list<struct binomialHeap*>::iterator iter2=listB.begin();
    
    while(iter1!=listA.end())
    {
        if(iter2==listB.end())
        break;
        else
        {
        if((*iter2)->degree<(*iter1)->degree)
        {
            temp.push_back(*iter2);
            iter2++;
        }
        else if((*iter2)->degree>=(*iter1)->degree)
        {
            temp.push_back(*iter1);
            iter1++;
        }
        }
    }
    
    while(iter1!=listA.end())
    {
        temp.push_back(*iter1);
        iter1++;
    }
    while(iter2!=listB.end())
    {
        temp.push_back(*iter2);
        iter2++;
    }
    return temp;
}


list<struct binomialHeap*> decreasekey_binomialHeap(list<struct binomialHeap*> head,int init,int fin,struct binomialHeap *bino[])
{
    struct binomialHeap *node=bino[init];
    struct binomialHeap *temp;
    node->dst=fin;
    while(node->parent!=NULL && node->dst<node->parent->dst)
    {
        temp=node->parent;
        node->parent=node;
        node=temp;
        
    }
    return head;
    
}

list<struct binomialHeap*> modify(list<struct binomialHeap*> head)
{
    
    list<struct binomialHeap*>::iterator iter1,iter2,iter3;
    iter1=head.begin();
    iter2=head.begin();
    iter3=head.begin();
    
    
    if(head.size()<=1)
    return head;
    else if(head.size()==2)
    {
        iter2++;
        iter3=head.end();
    }
    else if(head.size()>2)
    {
        iter2++;
        iter3=iter2;
        iter3++;
    }
    
    
    while(iter1!=head.end())
    {
        if(iter2==head.end())
        iter1++;
        else if((*iter2)->degree > (*iter1)->degree)
        {
            iter1++;
            iter2++;
            if(iter3!=head.end())
            iter3++;
            
        }
        
        else if(iter3!=head.end() && (*iter1)->degree == (*iter2)->degree && (*iter1)->degree == (*iter3)->degree)
        {
            iter1++;
            iter2++;
            iter3++;
        }
        else if((*iter2)->degree==(*iter1)->degree)
        {
            struct binomialHeap *temp;
            
            struct binomialHeap *tree1=*iter1;
            struct binomialHeap *tree2=*iter2;
            
            
            if(tree1->dst>tree2->dst)
            swap(tree1,tree2);
    
            tree2->parent=tree1;
            tree2->sibling=tree1->child;
            tree1->child=tree2;
            tree1->degree++;
            
            *iter1=tree1;
            iter2=head.erase(iter2);
            if(iter3!=head.end())
            iter3++;
            
        }
        
        
    }
    return head;
    
}

list<struct binomialHeap*> insertnode(list<struct binomialHeap*> head,int dist,int vert)
{
    struct binomialHeap *temp=new binomialHeap;
    temp->dst=dist;
    temp->vtx=vert;
    temp->degree=0;
    temp->child=NULL;
    temp->sibling=NULL;
    temp->parent=NULL;
    
    list<struct binomialHeap*> temp1;
    temp1.push_back(temp);
    temp1=unionBinomial(head,temp1);
    return modify(temp1);
    
    
}


struct binomialHeap* Min_get(list<struct binomialHeap*> head)
{
    list<struct binomialHeap*>::iterator iter=head.begin();
    struct binomialHeap *temp=*iter;
    while(iter!=head.end())
    {
        if((*iter)->dst<temp->dst)
        temp=*iter;
        iter++;
    }
    return temp;
}

list<struct binomialHeap*> ExtractMin(list<struct binomialHeap*> head)
{
    list<struct binomialHeap*> temp1;
    list<struct binomialHeap*> temp2;
    struct binomialHeap *temp;
    
    temp=Min_get(head);
    list<struct binomialHeap*>::iterator iter=head.begin();
    
    while(iter!=head.end())
    {
        if(*iter!=temp)
        temp1.push_back(*iter);
        
        iter++;
    }
    
    
    list<struct binomialHeap*> head1;
    temp=temp->child;
    struct binomialHeap *temp3;
    
    while(temp!=NULL)
    {
        temp3=temp;
        temp=temp->sibling;
        temp3->sibling=NULL;
        head1.push_front(temp3);
        
    }
    temp2=head1;
    temp1=unionBinomial(temp1,temp2);
    temp1=modify(temp1);
    return temp1;
    
    
}

void dijkstra_BinomialHeap(vector<int> adj[],vector<int> alist[],int n,int s,int d[])
{
    int distance[n];
    bool visited[n];
    int i,x,y;
    
    for(i=0;i<n;i++)
    {
        visited[i]=false;
        distance[i]=999999;
    }
    distance[s]=0;
    
    list<struct binomialHeap*> Binom_heap;
    Binom_heap=insertnode(Binom_heap,0,s);
    
    
    while(Binom_heap.empty()==false)
    {
        y=(Min_get(Binom_heap))->vtx;
        visited[y]=true;
        Binom_heap=ExtractMin(Binom_heap);
        
        
        for(i=0;i<alist[y].size();i++)
        {
            x=alist[y][i];
            if(visited[x]==false && distance[x]>distance[y]+adj[y][x])
            {
                distance[x]=distance[y]+adj[y][x];
                Binom_heap=insertnode(Binom_heap,distance[x],x);
            }
        }
        
    }
    for(i=0;i<n;i++)
    {
        if(distance[i]==999999)
        cout<<distance[i]<<" ";
        else
        {
        int ans=distance[i]+d[i]-d[s];
        cout<<ans<<" ";
        }
    }
    cout<<"\n";
    
    
}

void call_dijkstra_BinomialHeap(vector<int> adj[],vector<int> alist[],int n,int d[])
{
    for(int i=0;i<n;i++)
    dijkstra_BinomialHeap(adj,alist,n,i,d); 
    
}
//Binomial heap ends

//array part starts
void dijkstra_array(int n,int s,vector<int> a[],int d[])
{
    int i;
    bool visited[n];
    for(i=0;i<n;i++)
    visited[i]=false;
    
    int distance[n];
    for(i=0;i<n;i++)
    distance[i]=999999;
    distance[s]=0;
    int u,c=0;
    while(c<(n-1))
    {
        u=-1;
        for(i=0;i<n;i++)
        {
        if(visited[i]==false && (u==-1 || distance[i]<distance[u]))
        u=i;
        }
        visited[u]=true;
        for(int v=0;v<n;v++)
        {
            if(a[u][v]!=999999 && (visited[v]==false && u!=v))
            distance[v]=min(distance[v],distance[u]+a[u][v]);
        }
        c++;

    }
    for(i=0;i<n;i++)
    {
        if(distance[i]==999999)
        cout<<distance[i]<<" ";
        else
        {
        int ans=distance[i]+d[i]-d[s];
        cout<<ans<<" ";
        }
    }
    cout<<"\n";
}

void call_dijkstra_array(vector<int> a[],int n,int d[])
{
    for(int i=0;i<n;i++)
    dijkstra_array(n,i,a,d);
}
//array part ends


int main(int argc, char** argv)
{
    int t,n,dir,testcase,te=0;
    int chosen=0;
    if(argc>1)
    chosen=atoi(argv[1]);
    
    cin>>t;
    testcase=t;
    double time_taken[testcase];
    clock_t start, end;
    while(t--)
    {
        
        cin>>n>>dir;
        vector<int> adjList[n];
        int wt,i,j;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
                cin>>wt;
				adjList[i].push_back(wt);
			}
		}
		start = clock(); 
        vector<int> NewAdjList[n+1];
        for(i=0;i<=n;i++)
		{
			for(j=0;j<=n;j++)
			{
                if(i!=n && j==n)
                {
                    NewAdjList[i].push_back(999999);

                }
                else if(i==n)
                NewAdjList[i].push_back(0);
                
                else
                {
                    wt=adjList[i][j];
                    NewAdjList[i].push_back(wt);
                }
                
			}
		}
		NewAdjList[n][n]=999999;
        int d[n];
        for(i=0;i<n;i++)
        d[i]=0;
        bool ans;
        ans=bellman(NewAdjList,n+1,d);
        
       if(ans==true)
       {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i!=j && adjList[i][j]!=999999)
                {
                    adjList[i][j]=adjList[i][j]+d[i]-d[j];
                }
            }
        }
         vector<int> alist[n];
        for(i=0;i<n;i++)
        {
          for(j=0;j<n;j++)
           {
             if(i!=j && adjList[i][j]!=999999)
             alist[i].push_back(j);
           }
        }
        if(argc==1 || chosen==3){
        call_dijkstra_BinomialHeap(adjList,alist,n,d);
        }
        else if(chosen==1){
        call_dijkstra_array(adjList,n,d);
        }

        else if(chosen==2)
        {
        call_dijkstra_minHeap(adjList,alist,n,d);

        }

}//end of if else
end = clock();

time_taken[te]=double(end - start) / double(CLOCKS_PER_SEC); 

te++;

    }//end of testcases
    for(te=0;te<testcase;te++){
    cout<<time_taken[te]<<fixed<<setprecision(5);
    cout<<" ";}

    return 0;
}