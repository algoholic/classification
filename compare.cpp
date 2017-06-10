//Efficiency compare
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double compare_eff(string file1,string file){ // file1 is the file name of rule set.(rules_RS.txt or rules_GENETIC.txt).
  string s,str;
  ifstream fp(file.c_str());  //Enter the desired data file name. 
  while(getline(fp,s)){
    string buf;
    object temp; 
    for(ll i=0;i<s.length();i++){
       while(s[i]!=',' && i<s.length()){
          buf.push_back(s[i++]);
       }
       if(i<s.length()) // For condition attributes.
          temp.attr.push_back(buf);
       else             // For dicision attributes.
          temp.dis=buf;
       buf.clear();
    }  
    raw_cmp.push_back(temp);
  }   
  //raw_cmp contains all objects from original file with class.
  ll sz=raw_cmp.size();
  ll correct=0;
  //1st classify by "rules_RS.txt".
  vector<object> rs;
  ifstream fprs(file1.c_str(),ofstream::in); 
  while(getline(fprs,s)){
    string buf;
    object temp; 
    for(ll i=0;i<s.length();i++){
       while(s[i]!=',' && i<s.length()){
          buf.push_back(s[i++]);
       }
       if(i<s.length()) // For condition attributes.
          temp.attr.push_back(buf);
       else             // For dicision attributes.
          temp.dis=buf;
       buf.clear();
    }  
    rs.push_back(temp);
  }   
  for(ll i=0;i<sz;i++){
     int flag=0;
     for(ll j=0;j<rs.size();j++){
        for(ll k=0;k<rs[j].attr.size();k++){
           if(rs[j].attr[k]==raw_cmp[i].attr[k] && rs[j].dis==raw_cmp[i].dis){
              correct++;
              flag=1;
              break;
           }
        }  
        if(flag)
          break;   
     } 
     if(!flag){//no match with any rule compare with default class.
       if(raw_cmp[i].dis==max_accuracy)
          correct++;
     }   
  } 
  double accr=(double)correct/(double)sz;
  accr*=100;
  fprs.close();
  return accr;
}
