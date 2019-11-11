//mfset is 2d array with first row containing parent vertex key
//second row contains the count of vertices belonging to that particular parent vertex set
//initialization creates total N disjoint sets for N vertices
void initialize(int **mfset,int n){
    for(int i=0;i<n;i++){
        mfset[0][i]=-1;    //-1 implies the vertex itself is it's parent vertex
        mfset[1][i]=1;      //every set has element(vertex) initially
    }
}

//returns the parent vertex of the set which given vertex(key) belongs to
int find(int** mfset, int key){
    if(mfset[0][key-1]==-1)
        return key;
    return find(mfset, mfset[0][key-1]);    
}

//takes union of the sets to which vertex1(src_key) and vertex2(dest_key) belongs to
void merge(int** mfset,int src_key,int dest_key){
    int u = find(mfset, src_key);
    int v = find(mfset, dest_key);
    if(u!=v){       //only if both vertex1 and vertex2 doesn't belong to same set
        if(mfset[1][u-1]<mfset[1][v-1])
        {
            mfset[0][u-1]=v;
            mfset[1][v-1]+=mfset[1][u-1];
        }
        else{
            mfset[0][v-1]=u;
            mfset[1][u-1]+=mfset[1][v-1];
        }
    }
}