#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include<utility>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<sstream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef double dd;
#include "raw_input.cpp"
#include "remove_inconsistency.cpp"
#include "module_matrix.cpp"
#include "rule_gen.cpp"
#include "genetic1.cpp"
#include "genetic2.cpp"
#include "compare.cpp"

vector<dd> acc_rs;
vector<dd> acc_gen;
string to_string(ll n){
  string r="";
  while(n!=0){
    r+=('0'+(n%10));
    n/=10; 
  }
  ll l=r.size();
  for(ll i=0;i<=l/2;i++){
     swap(r[i],r[l-1]);  
  } 
  return r; 
}
int main(){
  string file_org; //get the data file name.
  string name=file_org;
 
  cout<<"Enter the name of data file ( XYZ.data ):";
  cin>>file_org;
  FILE *p1=fopen("rules_RS.txt","w");
  FILE *p2=fopen("rules_GENETIC.txt","w"); 
  system("g++ h_cross_mod.cpp");
  string iter=to_string(1);
  string command="./a.out "+file_org+" "+iter;
  system(command.c_str());
  string s="_10_fold_";
  for(ll i=1;i<=10;i++){
     
     string file=s;
     file+=file_org+to_string(i)+".data";
     //cout<<file<<endl;
     read(file);        
     remove_incons();
     objs_size();
     construct_matrix();
     construct_examples();
     ll cn_rules=0; //no of final rules got from rough set classification.
     rule_gen(cn_rules);
     if(cn_rules>=2){// Entry condition to fed it to genetic algo part.  
       seperate_rules(); 
       cross();
     }
   
  }
  ll divrs=0;
  ll divgen=0;
  dd sumrs=0;
  dd sumgen=0;
  for(ll i=0;i<10;i++){
     string file1=s+file_org+to_string(i+1)+".test";
     string file2=s+file_org+to_string(i+1)+".data";
     double rs_value=compare_eff("rules_RS.txt",file1);
     acc_rs.push_back(rs_value);
     cout<<"efficiency in RS="<<rs_value<<endl;
     double gen_value=compare_eff("rules_GENETIC.txt",file1);
     acc_gen.push_back(gen_value);
     cout<<"efficiency in GENETIC="<<gen_value<<endl<<endl;
     sumgen+=(acc_gen[i]);
     sumrs+=(acc_rs[i]);
     divrs++;
     divgen++; 
     string tmp1="rm "+file1;
     string tmp2="rm "+file2; 
     system(tmp1.c_str());
     system(tmp2.c_str());
  }
  dd rs_acc=sumrs/divrs;
  dd gen_acc=sumgen/divgen;
  cout<<endl<<"*******************************************"<<endl<<endl; 
  cout<<"efficiency in RS="<<rs_acc<<endl;
  cout<<"efficiency in GENETIC="<<gen_acc<<endl;
  system("rm rules_RS.txt");
  system("rm rules_GENETIC.txt"); 
  string tmp1="rm "+s+file_org+to_string(1)+".names";
  system(tmp1.c_str());
  return 0;
}
