/*
  Construct
  *******************************************
  1. Discernibility Matrix.
  2. Example objects with different decision.
  *******************************************
*/

//Read data from the file of objects without inconsistency.
/*struct object{ // declared in 1st module.
  vector<string> attr; // Condition attributes. 
  string dis;       // Dicision attribute(class).
};*/
struct data{
  vector<ll> attr; //Set of mismatching attributes.
};
data **matr;  //Discernibility matrix.
//vector<object> arr;      //Array of objects without inconsistency.
ll n;  //Number of objects.
ll m;  //Number of Condition attributes.
vector<ll> tmp;  //Temporary vector. 
vector<ll> *v;   //Example objects with different decisions.

/**************************  Methods  ************************************/
//Initialize number of objects. 
void objs_size(){ //Method 1.
  n=raw_arr.size(); 
  m=raw_arr[0].attr.size();
  matr=new data *[n];
  for(ll i=0;i<n;i++){
     
     matr[i]=new data[n];
  }
}
//Construct discernibility matrix.
void construct_matrix(){ //Method 2.
   ll i,j,k;   
   for(i=0;i<n;i++){
     for(j=0;j<i;j++){
        for(k=0;k<m;k++){
            if(raw_arr[i].attr[k]!=raw_arr[j].attr[k]){
               tmp.push_back(k);
            }
        }
        matr[i][j].attr=tmp;
        tmp.clear();
     }
   }  
}
// Construct example objects with different decisions.
void construct_examples(){ //Method 3.
   ll i,j;
   v=new vector<ll> [n];
   for(i=0;i<n;i++){
      for(j=i+1;j<n;j++){
        if(raw_arr[i].dis!=raw_arr[j].dis){
           v[i].push_back(j);
           v[j].push_back(i);
        }
      }
   }   
}

