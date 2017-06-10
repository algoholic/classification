// sort rules from rules.txt according to their class.

struct rule{ // rule body.
  ll atr_no; //ith attribute.
  string dis; //dis class.
  string atr_val; // val of attr. 
};
vector<pair<object,double> > rule_data;  // got rules from rules.txt. 2nd field is of fitness vale.
bool cmpdis(pair<object,double> l,pair<object,double> r){   //sort based on decision class.
  return (l.first.dis)<(r.first.dis);
 
}
bool cmpfv(pair<object,double> l,pair<object,double> r){ // sort based on decending order of fitness value.
  return l.second>r.second;
}
/////////////////////////////////////////////////////////////////////////////////////////
double fitnessval(rule x){ // for each rule.
   ll tp=0;
   ll tn=0;
   ll fp=0;
   ll fn=0;
   double fv=0.0; 
   double div=1.0;
   for(ll i=0;i<raw_arrfile.size();i++){
      if(raw_arrfile[i].attr[x.atr_no]==x.atr_val){ // attr value matches.
          if(raw_arrfile[i].dis==x.dis)
             tp++;
          else
             fp++; 
      } 
      else{
          if(raw_arrfile[i].dis==x.dis)
             fn++;
          else
             tn++;  

      } 
   }
   fv=double((tp+tn)-(fp+fn));
   div=double(tp+tn+fp+fn);
   if(div==0)
      return 0; 
   fv=(fv/div)*100;    // scaled fitness value. 
   return fv;
}
//////////////////////////////////////////////////////////////////////////////////////////

void seperate_rules(){// 1.rules are seperated from rules.txt and formed a group (same class).2 fitness value removal 3.again sort on avg fitness value desc.
  string file1="rules_RS.txt";
  string s,str;
  ifstream fp(file1.c_str()); 
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
    rule_data.push_back(make_pair(temp,0));
  }  
  /************************************************************************/
  sort(rule_data.begin(),rule_data.end(),cmpdis); // sort it based on dis classes.
  string dis_class;
  double total_fv=0;
  double avg_fv=0;
  double div=0; 
  for(ll j=0;j<rule_data[0].first.attr.size();j++){
       //cout<<"k "; 
       if(rule_data[0].first.attr[j]!="*"){
           //cout<<"k1"; 
           rule x;
           x.atr_no=j;
           x.atr_val=rule_data[0].first.attr[j];
           x.dis=rule_data[0].first.dis;
           total_fv+=fitnessval(x);
           div++; 
       }
  } 
  for(ll i=1;i<rule_data.size()+1;i++){
      if(i==rule_data.size() || rule_data[i].first.dis!=rule_data[i-1].first.dis){
          if(div==0)
            avg_fv=0;
          else 
            avg_fv=total_fv/div; 
           //cout<<"avg fv="<<avg_fv<<endl; 
          ll k=i-1;
          dis_class=rule_data[i-1].first.dis;
          while(k>=0 && rule_data[k].first.dis==dis_class){ // remove whose fitness value < avg_fv
             for(ll j=0;j<rule_data[k].first.attr.size();j++){
                if(rule_data[k].first.attr[j]!="*"){
                   rule x;
                   x.atr_no=j;
                   x.atr_val=rule_data[k].first.attr[j];
                   x.dis=rule_data[k].first.dis;
                   double fv=fitnessval(x);
                   //cout<<"fv="<<fv<<endl;
                   if(fv<avg_fv || fv<=0){
                      rule_data[k].first.attr[j]="*";
                      //cout<<"fv="<<fv<<" "<<"Trashed rule\n";
                   } 
                }
             } 
             k--;
          }
          if(i==rule_data.size())
            break; 
          total_fv=0;
          avg_fv=0;
          div=0;
          for(ll j=0;j<rule_data[i].first.attr.size();j++){
				      if(rule_data[i].first.attr[j]!="*"){
						     rule x;
						     x.atr_no=j;
						     x.atr_val=rule_data[i].first.attr[j];
						     x.dis=rule_data[i].first.dis;
						     total_fv+=fitnessval(x);
						     div++; 
				      }
          } 
      }
      else{ // rules inside same class.
        for(ll j=0;j<rule_data[i].first.attr.size();j++){
           if(rule_data[i].first.attr[j]!="*"){
               rule x;
               x.atr_no=j;
               x.atr_val=rule_data[i].first.attr[j];
               x.dis=rule_data[i].first.dis;
               total_fv+=fitnessval(x);
               div=div+1; 
           }
        } 
      }  
        
  }
  /***********************************************************************************/
  // got rules in *,*, _,*,_,C form where <avgfv(for each class) rules replaced by just *.
  vector<double> fv; //contains average fitness value of each rule row.
  div=0;
  double fvr=0;
  for(ll i=0;i<rule_data.size();i++){
     for(ll j=0;j<rule_data[i].first.attr.size();j++){
         if(rule_data[i].first.attr[j]!="*"){
            rule x;
            x.atr_no=j;
            x.atr_val=rule_data[i].first.attr[j];
            x.dis=rule_data[i].first.dis;
            fvr+=fitnessval(x);
            div=div+1;
         }
     }
     fvr=fvr/div; // average fitness value of each rule row.
     rule_data[i].second=fvr; // store it.
  }
  sort(rule_data.begin(),rule_data.end(),cmpfv); // sort based on fitness value.*/
}

