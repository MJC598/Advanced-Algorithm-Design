/*
  *   @author Matthew Carroll
  *   CS3050 Homework 4 Programming Assignment Main File
  *   Dijkstra's Algorithm
*/

//NOTES FOR THE LAST adjacency
/*
    Figure out why the last and first nodes of the heap are not flipping correctly
    it acts like its just the first and last flipping instead of bubbling down correctly
*/

#include "adjacentlist.h"
// #include "input_error.h"
// #include "heaps.h"


int main(int argc, char* argv[]){
  //error check 1
  if(argc != 3){
      exit(1);
  }
  Array* arr = read(argv[1]);

  //REMEMBER TO COMMENT OR UNCOMMENT THESE LINES BASED ON WHAT YOU ARE DOING

  // print(arr);
  dijkstras(arr, argv[2]);

  //PLEASE

  return (EXIT_SUCCESS);
}

//Start read function
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
  char* holder = malloc((sizeof(int) * 3) + (sizeof(char) * 4));
  while(!feof(fp)){
    fscanf(fp, "%s\n", holder);
    //THIS NEEDS TO CHANGE TO ACCOMIDATE THE WEIGHTED GRAPH
    //CHECK FOR ERRORS HERE
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

//NEEDS REVISION
//start parseHolder
int parseHolder(char holder[]){
  // initialize string so that i can copy it so I dont tokenize the actual string;
  char* string = malloc(sizeof(strlen(holder)));
  //copied over to avoid messing with the other string
  strcpy(string, holder);
  char* token;
  //tokenizing for correct parsing
  if(string[0] == '('){
    //source vertex
    token = strtok(++string, ",");
    if(atoi(token) == 0){
      return 0;
    }
    //destination vertex
    token = strtok(NULL, ",");
    if(atoi(token) == 0){
      return 0;
    }
    //weight
    token = strtok(NULL, ")");
    if(atoi(token) == 0){
      return 0;
    }
    //this is the one valid return
    return 1;
  }
  return 0;
}

//start addEdge (NEED TO REVISE FOR DIJKSTRA)
void addEdge(Array* arr, char string[], int vert){
  char* token;
  token = strtok(++string, ",");
  int source = (atoi(token) - 1);
  //error check to see if source is actually a vertex
  if(source >= vert || source < -1){
    exit(7);
  }
  //Probably need to change the ")" to "," to find the second vertex
  token = strtok(NULL, ",");
  int destination = (atoi(token) - 1);
  //same as source error check, just for destination
  if(destination >= vert || destination < -1){
    exit(7);
  }
  //PROBABLY NEEDS THE SAME THING AS ABOVE TO RECONGIZE THE WEIGHT
  token = strtok(NULL, ")");
  int weight = (atoi(token) - 1);
  //adding the edge source to destination to the adjacency list
  List* newList = malloc(sizeof(List));
  newList->vertex = destination;
  //adding weight to the list to control for edges, stored on destination vertex list
  newList->weight = weight;
  newList->n = NULL;
  newList->n = arr[source].n;
  arr[source].n = newList;


  //THIS SECTION IS UNEEDED BECAUSE WE WANT A DIRECTED GRAPH
  //adding the edge destination to source to the adjacency list (makes it undirected)
  // newList = malloc(sizeof(List));
  // newList->vertex = source;
  // newList->n = NULL;
  // newList->n = arr[destination].n;
  // arr[destination].n = newList;


}


//start print (Used to show the adjacency list is working correctly)
void print(Array* arr){
  int i;
  int vert = arr[0].totalVert;
  for(i = 0; i <= (vert - 1); i++){
  List* temp = arr[i].n;
  printf("\nAdjacency List of vertex %d\n", (arr[i].vertex + 1));
  while(temp->n != NULL){
    printf("%d W: %d-> ", (temp->vertex + 1), (temp->weight + 1));
    temp = temp->n;
  }
    printf("\n");
  }
}

//Dijkstra's Algorithm Start
void dijkstras(Array* arr, char* ofile){
  FILE* fp = fopen(ofile, "w");
  if(!fp){
    exit(5);
  }
  vertex* holder = malloc(sizeof(vertex) * arr[0].totalVert);
  vertex u;
  int heapSize = arr[0].totalVert;
  holder = initSingleSource(arr, holder);
  arr[0].distance = 0;

  // This is backup plan

  int i, j = 0, currentDistance = -1;
  int* distance = malloc(sizeof(int) * heapSize);
  int* queue = malloc(sizeof(int) * heapSize);
  for(i = 0; i < heapSize; i++){
    distance[i] = currentDistance;
    queue[i] = i;
  }

  distance[0] = 0;
  queue[0] = 0;

  while(j < heapSize){
    // printf("Entered while(j < heapSize): j = %d\n", j);
    currentDistance = queue[j];
    // printf("1.) currentDistance = %d\n", currentDistance);
    j++;
    // printf("2.) currentDistance = %d\n", currentDistance);
    // printf("distance[currentDistance] = %d\n", distance[currentDistance]);
    if(distance[currentDistance] == -1){
      continue;
    }
    u.vertex = arr[currentDistance].vertex;
    // printf("u.vertex = %d\n", u.vertex);
    u.distance = arr[currentDistance].distance;
    // printf("u.distance = %d\n", u.distance);
    u.n = arr[currentDistance].n;
    while(u.n != NULL){
      // printf("u.n->vertex = %d\n", u.n->vertex);
      // printf("distance[u.vertex] = %d\n", distance[u.n->vertex]);
      if(distance[u.n->vertex] == -1 || distance[u.n->vertex] > (distance[currentDistance] + u.n->weight)){
        // printf("u.n->weight = %d, distance[currentDistance] = %d\n", u.n->weight, distance[currentDistance]);
        distance[u.n->vertex] = distance[currentDistance] + u.n->weight + 1;
        // printf("distance[u.n->vertex] = %d: u.n->vertex = %d\n", distance[u.n->vertex], u.n->vertex);
      }
      u.n = u.n->n;
    }
    for(i = 0; i < heapSize; i++){
      // printf("%d: %d\n", i, distance[i]);
    }
  }
  for(i = 0; i < heapSize; i++){
    fprintf(fp, "%d\n", distance[i]);
  }
  if(fclose(fp) != 0){
    exit(6);
  }
}
  //End backup plan



/*
  buildMinHeap(holder, heapSize);
  while(holder != NULL){
    int k;
    for(k = 0; k < heapSize; k++){
      // printf("holder[k].distance = %d\n", holder[k].distance);
    }
    heapSize--;
    // printf("Calling extractMin, holder[0].distance = %d\n", holder[0].distance);
    u = extractMin(holder, heapSize);
    // printf("Distance: %d\n", u.distance);
    if(arr[u.vertex].n == NULL){
      // printf("arr[u.vertex].n == NULL\n");
      break;
    }
    else{
      // printf("arr[u.vertex].n != NULL\n");
    }
    while(arr[u.vertex].n != NULL){
      vertex v;
      v.vertex = arr[arr[u.vertex].n->vertex].vertex;
      v.distance = arr[arr[u.vertex].n->vertex].distance;
      // printf("v.distance = %d\n", v.distance);
      // printf("weight = %d\n", arr[u.vertex].n->weight);
      relax(u, v, arr[u.vertex].n->weight, holder);
      // updateHeap(holder, v);
      arr[u.vertex].n = arr[u.vertex].n->n;
    }

    buildMinHeap(holder, heapSize);
  }
}
*/




//Extract Minimum start

//initSingleSource start
vertex* initSingleSource(Array* arr, vertex holder[]){
  int v;
  for(v = 0; v < arr->totalVert; v++){
    holder[v].distance = -1;
    holder[v].vertex = v;
    holder[v].n = arr[v].n;
  }
  holder[0].distance = 0;
  return holder;
}

//relax Start
void relax(vertex u, vertex v, int weight, vertex holder[]){
  if(v.distance == -1 || v.distance > u.distance + weight){
    printf("If statement in relax entered: u.distance = %d\n", u.distance);
    v.distance = u.distance + weight;
    printf("v.distance = %d\n", v.distance);
    updateHeap(holder, v);
  }
}
