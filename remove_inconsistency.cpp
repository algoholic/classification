/* 
  2nd module.
  Takes raw data input from rw_input.cpp.
  Remove inconsistency.
  write back to file.datamod. 

*/

/*struct object{
  vector<string> attr; // Condition attributes. 
  string dis;       // Dicision attribute(class).
};
vector<object> raw_arr;      //Array of objects with inconsistency. 
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ll *mark;        // To mark the inconsistent objects.
string max_accuracy; // to get the default class.
bool cmp(pair<string,dd> lhs,pair<string,dd> rhs){
   return lhs.second<rhs.second;

}
///////////////////////////////////////////////////////////////////
void remove_incons(){
  ll sz=raw_arr.size();
  mark=new  ll[sz];
  for(ll i=0;i<sz;i++)
     mark[i]=0; 
  map<vector<string>,vector<ll> > mp; // To create IND(B).
  map<vector<string>,vector<ll> > :: iterator it1;
  map<string,vector<ll> > concept;    // Concepts.(object set of different classes/concepts).
  map<string,vector<ll> > :: iterator it2;
  map<string,vector<ll> > lowerb;    // Lower approximation of different classes/concepts.
  vector<pair<string,dd> > accuracy;   // Accuracy of different concepts.
  vector<string> v;
  vector<ll> tmp,indtmp,lbtmp;
  vector<ll> :: iterator it_t;
  for(ll i=0;i<sz;i++){          // Create IND(B) and Concept map.
     for(ll j=0;j<raw_arr[0].attr.size();j++)
        v.push_back(raw_arr[i].attr[j]);
     mp[v].push_back(i);
     concept[raw_arr[i].dis].push_back(i);
     v.clear();
  } 
  /*********************************/ 
  for(it2=concept.begin();it2!=concept.end();it2++){  // Create Lower approximation map of different classes/concepts.
     tmp=it2->second;      
     // For a particular concept.
     for(it1=mp.begin();it1!=mp.end();it1++){
        indtmp=it1->second;
        int flag=0;
        for(ll i=0;i<indtmp.size();i++){
            if(!binary_search (tmp.begin(), tmp.end(), indtmp[i]) ){
               flag=1;                          
               break;
            } 
        }
        if(flag==0){
           for(ll i=0;i<indtmp.size();i++){           
              lbtmp.push_back(indtmp[i]);
           }
        }   
     }  
     lowerb[it2->first]=lbtmp;
     lbtmp.clear(); 
  } 
  /*********************************/
  dd minm=1.0;
  string str;
  for(it2=lowerb.begin();it2!=lowerb.end();it2++){  // Get the minimum accuracy concept.
      dd acc= dd(it2->second.size()) ;///raw_arr.size();
      //cout<<acc<<" "; 
      string str=it2->first;
      //cout<<str<<endl;
      accuracy.push_back(make_pair(str,acc));
      if(acc<minm){
        minm=acc;
        str=it2->first;
      }
  }
  sort(accuracy.begin(),accuracy.end(),cmp);
  max_accuracy=accuracy[accuracy.size()-1].first;
  /*********************************/
  
  vector<ll> rmtmp; // To store possible object indexes to be removed. 
  for(ll j=0;j<accuracy.size();j++){
     
     str=accuracy[j].first;
     tmp=concept[str]; 
     for(it1=mp.begin();it1!=mp.end();it1++){
        indtmp=it1->second;
        ll count=0; 
        for(ll i=0;i<indtmp.size();i++){
            if(mark[indtmp[i]]){
               count++;
               continue;
            }                 
            if(binary_search (tmp.begin(), tmp.end(), indtmp[i]) ){
               rmtmp.push_back(indtmp[i]);
            } 
        }
        if(rmtmp.size()>=2 || rmtmp.size()<(indtmp.size()-count)){
           for(ll i=0;i<rmtmp.size();i++){
              mark[rmtmp[i]]=1;   // This has to be removed from raw data.
           } 
        }
        rmtmp.clear();
     }
  }
  rmtmp.clear();
  accuracy.clear();
  /***********************************/
  // Now re construct raw_arr with data without inconsistency.
  vector<object> arr_tmp;
  for(ll i=0;i<raw_arr.size();i++){
     if(!mark[i])
       arr_tmp.push_back(raw_arr[i]);
  }  
  
  raw_arr=arr_tmp;
 
  arr_tmp.clear();
  delete[] mark;
}
