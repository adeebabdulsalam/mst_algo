struct p_node{
    int src_key;    //start vertex of an edge
    int dest_key;   //end vertex of the edge
    int priority;   //cost of the edge {Higher the value,lower the actual priority of the edge}
    p_node *next;
};

// Creates a new node in the priority list, with start vertex(src_key) and end vertex(dest_key)
//returns the newly created node
p_node* newnode(int src_key,int dest_key,int p){
    p_node* newnode = new p_node;
    newnode->src_key = src_key;
    newnode->dest_key = dest_key;
    newnode->priority = p;
    newnode->next = NULL;
    return newnode;
}

// p is cost of the edge. Higher the value ,lower the priority for the edge
void insert_pnode(p_node** head,int src_key,int dest_key,int p){
    p_node* newn = newnode(src_key,dest_key,p);
    if((*head)!=NULL && (*head)->priority < newn->priority){
       p_node* temp = (*head);
       while((temp->next!=NULL) && ((temp->next)->priority) < newn->priority){
           temp=temp->next;
       }
        newn->next = temp->next;
        temp->next = newn;    
    }
    else{
       newn->next = (*head);
       (*head) = newn;
    }
}