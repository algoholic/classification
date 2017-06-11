/*
  ****************************************************************
  4th Module.
  ****************************************************************
  Rule generation and store generated rules in file "rules_RS.txt"
/*****************************************************************/
///////////////////////////////////////////////////////////////////
/**************************  Methods  ****************************/
//Initialize number of objects. 
/*void objs_size(){ //Method 1.
  n=arr.size(); 
}
//Construct discernibility matrix.
void construct_matrix(){ //Method 2.
   ll i,j,k;   
   for(i=0;i<n;i++){
     for(j=0;j<i;j++){
        for(k=0;k<m;k++){
            if(arr[i].attr[k]!=arr[j].attr[k]){
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
        if(arr[i].dis!=arr[j].dis){
           v[i].push_back(j);
           v[j].push_back(i);
        }
      }
   }   
}*/
/********************************** file after "module_matrix.cpp" ********************************************/
/*struct compare {
   bool operator()(const object& left, const object& right) const {
     
       return left.attr < right.attr || (left.attr == right.attr && left.dis < right.dis);
   }
};*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rule_gen(ll &cn_rules){          
  ll i,j,k,x,y;
  map<ll,ll> mp;
  set<object,compare> st; // Set of minimal certain decision rules.
  set<object,compare> :: iterator it;
  int flag=0; 
  object temp_obj;
  ll sz;    //To get the size in each entry of Discernibility matrix matr.
  string r1="rules_RS.txt";
  ofstream fp(r1.c_str(),ofstream::app);
  for(i=0;i<n;i++){
    vector<string> attr_temp(m+1,"*"); // Temporary attribute array to generate file of rules. 
    flag=0;             // To check if any rules generated from v[i] or not. 
    for(j=0;j<v[i].size();j++){
       x=min(v[i][j],i);  // x,y : Index in the Discernibility matrix matr. 
       y=max(v[i][j],i); 
             
       for(k=0;k<matr[y][x].attr.size();k++){
          mp[matr[y][x].attr[k]]++;
          if(mp[matr[y][x].attr[k]]==v[i].size() ){
             attr_temp[matr[y][x].attr[k]]=raw_arr[i].attr[matr[y][x].attr[k]]; 
             flag=1;
          }  
       }
    }
    string dis_temp=raw_arr[i].dis;
    if(flag){
      
      temp_obj.attr=attr_temp;
      temp_obj.dis=dis_temp; 
      st.insert(temp_obj);
    } 
   
    v[i].clear(); 
    mp.clear();
  }
 
  for(it=st.begin();it!=st.end();it++){
     cn_rules++;
     for(i=0;i<m;i++)           // Print to the file "rules_RS.txt".
        fp<<it->attr[i]<<",";
     fp<<it->dis<<endl;
  }
  fp.close();
}
