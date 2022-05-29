#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10

typedef struct Vertex {
	int data;
	struct Vertex *link;
} Vertex;

typedef struct Graph{
	Vertex *Head;
} Graph;

#define MAX_QUEUE_SIZE 20
Vertex* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Vertex* deQueue();
void enQueue(Vertex* v); 
int visitInfo[MAX_VERTEX];
int VisitVertex(int visitV);

Graph* Initialize_Graph(Graph* G);
int Insert_Vertex(Graph* G, int v);
void Depth_First_Search(Graph* G, int v);
void Breath_First_Search(Graph* G, int v);
int Insert_Edge(Graph* G, int u, int v);
void Print_Graph(Graph* G);
int freeGraph(Graph* G);
void initVist();
int CheckV(Graph* G, int v);

int main(){

    printf("[-----[Seo han bit]   [2019038043]-----]\n");

    char command;
	int u, v;
	Graph* graph = NULL;

    do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			graph = initialize(graph);
			break;
		case 'q': case 'Q':
			freeGraph(graph); 
			break;
		case 'v': case 'V':
			printf("Your Num = ");
			scanf("%d", &v);
			insertVertex(graph, v); 
			break;
		case 'd': case 'D':
			printf("Your Num = ");
			scanf("%d", &v);
			initVist();
			DepthFS(graph, v);
			break;
		case 'p': case 'P':
			printGraph(graph);			
			break;
		case 'e': case 'E':
			printf("Your Num = ");
			scanf("%d %d", &u, &v);
			insertEdge(graph, u, v);
			insertEdge(graph, v, u); 			
			break;

		case 'b': case 'B':
			printf("Your Num = ");
			scanf("%d", &v);
			BreathFS(graph, v); 
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}
Graph* initialize(Graph* G){
	if(G != NULL) freeGraph(G);

	Graph* temp = (Graph*)malloc(sizeof(Graph)*MAX_VERTEX);

	for(int i = 0; i < MAX_VERTEX; i++){
		temp[i].Head = NULL;
	}

	initVist();

	return temp;
}
int freeGraph(Graph* G)
{
	Vertex *n;
	Vertex *trail;

	for(int i = 0; i < MAX_VERTEX; i++)
	{
		n = G[i].Head;

		if(n != NULL){
			while(n != NULL){
				trail = n;
				n = n->link;
				free(trail);
			}
		}
	}
	free(G);

}
int InsertVertex(Graph* G, int v)
{
	Vertex* new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	if(v > MAX_VERTEX){
		printf("[%d] is out of range \n");

		return 0;
	}

	else if(G[v].Head != NULL){
		printf("The Vertex of [%d] already exists\n", v);

		return 0;
	}
	else{
		G[v].Head = new;

		return 0;
	}
}
int InsertEdge(Graph* G, int u, int v){
	Vertex* new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	Vertex *n, *trail;
	n = G[u].Head;
	trail = n;

	if(CheckV(G, u) != 1 || CheckV(G, u) != 1){
		printf("There is an error");
		return 0;
	}
	
	if(n->link == NULL){

		n->link = new;
		return 0;
	}
	n = n->link;

	while(n != NULL){
		if(n->data > v){
			if(n == G[u].Head->link){
				new->link = G[u].Head->link;
				G[u].Head->link = new;
			}
			else{
				new->link = trail->link;
				trail->link = new;
			}
			return 0;
		}
		else if(n->data == v) return 0;
		trail = n;
		n = n->link;
	}
	trail->link = new;
	return 0;

}
void Depth_First_Search(Graph* G, int v)
{
	Vertex *w;

	if(G == NULL) return 0;
	else if(CheckV(G, v) == 0) return 0;

	VisitVertex(v);
	printf("%d ", v);

	for(w = G[v].Head->link; w; w = w->link){
		if(visitInfo[w->data] == 0){
			Depth_First_Search(G, w->data);
		}

	}
	return 0;
}
void Breath_First_Search(Graph* G, int v)
{
	Vertex *m, *n;
	initVist();

	if(G == NULL) return 0;
	else if(CheckV(G, v) == 0) return 0;

	enQueue(G[v].Head);
	VisitVertex(v);
	printf("%d ", v);

	while(front != rear){
		m = deQueue();
		for(n = G[m->data].Head; n; n = n->link){
			if(visitInfo[n->data] == 0){
				VisitVertex(n->data);
				printf("%d ",n->data);
				enQueue(n);
			}
		}
	}
}

int CheckV(Graph* G, int v){
	if(v < MAX_VERTEX) return 0;

	else if(G[v].Head == NULL) return 0;

	else return 1;
}
int VisitVertex(int visit){
	if(visitInfo[visit] == 0){
		visitInfo[visit] = 1;
		return 0;
	}
	return 1;
}

void initVist()
{
	for(int i = 0; i < MAX_VERTEX; i++) visitInfo[i] = 0;
	for(int j = 0; j < MAX_QUEUE_SIZE; j++) queue[j] = NULL;
	front = rear = -1;
}
void printGraph(Graph* G){
	Vertex *p, *n;

	printf("\n---print\n");

	if(G == NULL){
		printf("Nothing to print \n");
		return;
	}

	for(int i = 0; i < MAX_VERTEX; i++){
		p = G[i].Head;

		if(p != NULL){
			printf("Adjacent list of [%d]", i);
			n = p->link;

			while(n != NULL){
				printf("-> %d", n->data);
				n = n->link;
			}
			printf("\n");
		}
	}
	return;
}

Vertex* deQueue(){
	if(front == rear){
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Vertex* v){
	if(((rear+1)%MAX_QUEUE_SIZE) == front){
		printf(" There is an error (queue is full)");
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = v;
}
