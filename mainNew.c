#include "input_error.h"
#include "adjacentlist.h"

/*
 * @author Matthew Carroll
 */

//start main
int main(int argc, char* argv[]) {

    //error check 1
    if(argc != 3){
        exit(1);
    }

    Array* arr = read(argv[1]);
    //print(arr);
    BFS(arr, argv[2]);

    return (EXIT_SUCCESS);
}

//start read
Array* read(char* ifile){
    int vert, i;
    FILE* fp = fopen(ifile, "r");

    //error check 2
    if(!fp){
        exit(2);
    }

    fscanf(fp, "%d", &vert);

    Array* arr = malloc(sizeof(Array) * vert);
    for(i = 0; i < vert; i++){
        arr[i].vertex = i;
        arr[i].distance = -1;
        arr[i].n = NULL;
        arr[i].n = malloc(sizeof(List));
        arr[i].totalVert = vert;
    }

    char* holder = malloc((sizeof(int) * 2) + (sizeof(char) * 3));
    while(!feof(fp)){
        fscanf(fp, "%s\n", holder);

           if(parseHolder(holder) != 1){
           exit(8);
           }


        addEdge(arr, holder, vert);
    }

    //close fp and error check
    if(fclose(fp) != 0){
        exit(3);
    }

    return arr;
}

//start parseHolder
int parseHolder(char holder[]){
    //int i = 1, j;
    // initialize string so that i can copy it so I dont tokenize the actual string;
    char* string = malloc(sizeof(strlen(holder)));
    //copied over to avoid messing with the other string
    strcpy(string, holder);
    char* token;
    //tokenizing for correct parsing
    // printf("string[0] = %c\n", string[0]);
    if(string[0] == '('){
      token = strtok(++string, ",");
      // printf("1st token = %d\n", atoi(token));
        if(atoi(token) == 0){
            return 0;
        }
        token = strtok(NULL, ")");
        // printf("2nd token = %d\n", atoi(token));
        if(atoi(token) == 0){
            return 0;
        }
        //this is the one valid return
        return 1;
    }
    return 0;
}

//start addEdge
void addEdge(Array* arr, char string[], int vert){

    //basically uses strtok() to parse the input ordered pair, something I should have
    //done for initial parsing. Live and learn I guess but here it is now :)
    char* token;
    //*(string)++;
    token = strtok(++string, ",");
    int source = (atoi(token) - 1);

    //error check to see if source is actually a vertex
    if(source >= vert || source < -1){
        exit(7);
    }
    token = strtok(NULL, ")");
    int destination = (atoi(token) - 1);

    //same as source error check, just for destination
    if(destination >= vert || destination < -1){
        exit(7);
    }


    //adding the edge source to destination to the adjacency list
    List* newList = malloc(sizeof(List));
    newList->vertex = destination;
    // newList->distance = -1;
    newList->n = NULL;
    newList->n = arr[source].n;
    arr[source].n = newList;
    //printf("Source: %d\n", graph->alists[source]->vertex);

    //adding the edge destination to source to the adjacency list (makes it undirected)
    newList = malloc(sizeof(List));
    newList->vertex = source;
    // newList->distance = -1;
    newList->n = NULL;
    newList->n = arr[destination].n;
    arr[destination].n = newList;
    //printf("Destination: %d\n", graph->alists[destination]->vertex);
}

//start print
void print(Array* arr){
    int i;
    //printf("Total number of veritices: %d\n", arr[0].totalVert);
    int vert = arr[0].totalVert;
    for(i = 0; i <= (vert - 1); i++){
        List* temp = arr[i].n;
        //printf("\ntemp->vertex = %d", (temp->vertex + 1));
        printf("\nAdjacency List of vertex %d\n", (arr[i].vertex + 1));
        while(temp->n != NULL){
            printf("%d -> ", (temp->vertex + 1));
            //printf("D: %d ", temp->distance);
            temp = temp->n;
        }
        printf("\n");
    }
}

//start BFS
void BFS(Array* arr, char* ofile){
    FILE* fp = fopen(ofile, "w");
    if(!fp){
        exit(5);
    }

    //This is using the pseudocode from the BFS on the powerpoint in C
    int u;
    arr[0].distance = 0;
    arr[0].found = 1;
    int vert = arr[0].totalVert;
    for(u = 1; u < vert; u++){
        arr[u].distance = -1;
    }
    Queue* queue = NULL;
    //printf("arr[0].n->vertex = %d\n", arr[0].vertex);
    queue = enqueue(queue, arr[0].vertex);
    u = 0;
    //printf("queue->data = %d\n", queue->data);
    while(queue != NULL){
        u = queue->data;
        queue = dequeue(queue);
        // printf("%d\n", u);
        int v = 0;
        while(arr[u].n != NULL){
            //printf("arr[u].n->vertex (v) = %d\n", arr[u].n->vertex);
            v = arr[u].n->vertex;
            if(arr[v].distance == -1){
                arr[v].distance = arr[u].distance + 1;
                queue = enqueue(queue, arr[v].vertex);
            }
            arr[u].n = arr[u].n->n;
        }
    }

    int print = 0;
    for(print = 0; print < vert; print++){
        fprintf(fp, "%d\n", arr[print].distance);
    }

    //fclose(fp);
    if(fclose(fp) != 0){
        exit(6);
    }
}

//start Enqueue
Queue* enqueue(Queue* queue, int num){
    Queue* new = queue;
    if(new == NULL){
        new = malloc(sizeof(Queue));
        new->data = num;
        new->next = NULL;
        return new;
    }
    else{
        while(new->next != NULL){
            new = new->next;
        }
        Queue* add = malloc(sizeof(Queue));
        add->data = num;
        add->next = NULL;
        new->next = add;
    }
    return queue;
}

//start Dequeue
Queue* dequeue(Queue* queue){
    Queue* current = queue;
    if(current == NULL){
        printf("The list is empty\n");
        return current;
    }
    else{
        if(current->next == NULL){
            free(queue);
            queue = NULL;
            return queue;
        }
        else{
            queue = current->next;
            free(current);
            return queue;
        }
    }
}

//function used for error testing on queue
void printQueue(Queue* queue){
    if(queue == NULL){
        printf("Queue is empty\n");
    }
    else{
        //printf("Queue: ");
        Queue* temp = queue;
        while(temp->next != NULL){
            //printf("%d, ", temp->data);
            temp = temp->next;
        }
        //printf("\n");
    }
}
