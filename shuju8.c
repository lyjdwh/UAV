#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_VERTEX_NUM  20
typedef int VertexType;       //矩阵元素定义

typedef struct {
  VertexType adjvex;
  int lowcost;
}Edge[MAX_VERTEX_NUM];        // 记录从顶点集U到V－U的代价最小的边的辅助数组定义

typedef struct
{
  int vexnum;                 ////矩阵数目
  int connum;                    //连接数目      
  int  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //用二维数组表示网的临接矩阵
  int vexs[MAX_VERTEX_NUM];                   //矩阵元素
} MGraph;

void CreateDG(MGraph *G) ;                    //生成图
int minimum(Edge closedge,int n);             //寻找closedge 中最小的边
void MiniSpanTree(MGraph * G, int u);

void main()
{
  MGraph G;
  CreateDG(&G);
  MiniSpanTree(&G,0);                          //从第0个节点出发

}
void CreateDG(MGraph *G)
{ int i,j,k;
  printf("please input the number of vertex\n");
  scanf("%d",&(G->vexnum));
  printf("please input the number of connection \n");
  scanf("%d",&(G->connum));

  printf("please input the value of vertex\n");
  for(k=0;k<G->vexnum;k++)
  {
    scanf("%d",&(G->vexs[k]));
  }
  for(i=0;i<G->vexnum;i++)
    for(j=0;j<G->vexnum;j++)
      G->arcs[i][j]=100;                      //初始化临接矩阵，不临接的边为100
  printf("please input the node info you want to connect \n");
  for(k=0;k<G->connum;k++)
  {
    scanf("%d%d",&i,&j);
    scanf("%d",&(G->arcs[i][j]));
    G->arcs[j][i]=G->arcs[i][j];
  }
}

int minimum(Edge closedge,int n)
{
  int k=100;
  int i,j;
  j=closedge[0].lowcost;
  j=0;
  for(i=0;i<n;i++)
  {
    if((closedge[i].lowcost<k)&&(closedge[i].lowcost!=0))
    {
      j=i;
      k=closedge[i].lowcost;
    }
  }
  return j;
}
void MiniSpanTree(MGraph * G, int u) {
  int i,j,k;
  Edge closedge;
  k = u;
  for ( j=0; j<G->vexnum; ++j ) {             // 辅助数组初始化
	if (j!=k)
	{
	  closedge[j].adjvex=j;
	  closedge[j].lowcost=G->arcs[k][j];
	}
  }
  closedge[k].lowcost = 0;                  // 初始，U＝{u}
  for (i=1; i<G->vexnum; ++i) {              // 选择其余G.vexnum-1个顶点
	k = minimum(closedge,G->vexnum);        // 求出T的下一个结点：第k顶点
	  // 此时closedge[k].lowcost =
	  // MIN{ closedge[vi].lowcost | closedge[vi].lowcost>0, vi∈V-U }
	printf("the node is %d,the cost is %d\n",closedge[k].adjvex,closedge[k].lowcost);   // 输出生成树的边
	closedge[k].lowcost = 0;              // 第k顶点并入U集
	// for (j=0; j<G->vexnum; ++j)
	//   for(i=0;i<G->vexnum;++i)
	//   {
	// 	if (G->arcs[k][j] < closedge[i].lowcost) {
	// 	   // 新顶点并入U后重新选择最小边
	// 	   // closedge[j] = { G.vexs[k], G.arcs[k][j].adj };
	// 	  closedge[i].adjvex=j;
	// 	  closedge[i].lowcost=G->arcs[k][j];
	// 	  break;
	// 	}
	//   }
    for(j=0;j<G->vexnum;++j)
      if(G->arcs[k][j]<closedge[j].lowcost)
      {

        closedge[j].adjvex=j;
        closedge[j].lowcost=G->arcs[k][j];
      }
  }
}


