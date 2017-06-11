/*
****************************************************************
  6th Module.
****************************************************************
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************** Crossover phase *****************************************************/

struct gen_rule{ // rule body for cross over.
   object own;
   object p1;
   object p2;
   double fv;
};
vector<gen_rule> crossv;
/////////////////////////////////////////////////////////////////////
void assign(){ // initial assignment from rule_data to crossv rules. 
               // Method 1.
  for(ll i=0;i<rule_data.size();i++){
      gen_rule tmp;
      tmp.own=rule_data[i].first;
      tmp.p1=tmp.own;
      tmp.p2=tmp.own;
      tmp.fv=rule_data[i].second;
      crossv.push_back(tmp);   
  }
  crossv.clear();
} 
////////////////////////////////////////////////////////////////////
void cross(){  
               // Method 2.
  
  assign(); // initial assignment from rule_data to crossv rules. 
  ll sz=crossv.size();
  for(ll gen=0;gen<200;gen++){ // generation count.
     
     for(ll i=0;i<min(sz,ll(20));i++){ // select t=min(20,crossv.size()) rules for crossover in new generation.
         for(ll j=i+1;j<min(sz,ll(20));j++){
           
              gen_rule x1=crossv[i];
              gen_rule x2=crossv[j];
              gen_rule child1=x1;
              gen_rule child2=x2;
              child1.p1=x1.own;
              child1.p2=x2.own;
              child2.p1=x1.own;
              child2.p2=x2.own;  
              //1.0=parent1, 1=parent2, 2=grand p from parent1(0 1), 3=grand p from parent2(0 1). probability considerations.
              //For child 1.
              ll pr1=rand()%4;
              ll pr2=4; 
              if(pr1==2 || pr1==3)
                pr2=rand()%2;  
              if(pr1==0){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  child1.own.attr[at]=x1.own.attr[at];  
              }  
              else if(pr1==1){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  child1.own.attr[at]=x2.own.attr[at];  
              }   
              else if(pr1==2){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  if(pr2==0)  
                     child1.own.attr[at]=x1.p1.attr[at];
                  else
                     child1.own.attr[at]=x1.p2.attr[at];   
              }    
              else if(pr1==3){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  if(pr2==0)  
                     child1.own.attr[at]=x2.p1.attr[at];
                  else
                     child1.own.attr[at]=x2.p2.attr[at];   
              }   
               //For child 2.
              pr1=rand()%4;
              pr2=4; 
              if(pr1==2 || pr1==3)
                pr2=rand()%2;  
              if(pr1==0){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  child1.own.attr[at]=x1.own.attr[at];  
              }  
              else if(pr1==1){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  child1.own.attr[at]=x2.own.attr[at];  
              }   
              else if(pr1==2){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  if(pr2==0)  
                     child1.own.attr[at]=x1.p1.attr[at];
                  else
                     child1.own.attr[at]=x1.p2.attr[at];   
              }    
              else if(pr1==3){
                  ll at=rand()%rule_data[0].first.attr.size(); //select a random attribute to crossover.
                  if(pr2==0)  
                     child1.own.attr[at]=x2.p1.attr[at];
                  else
                     child1.own.attr[at]=x2.p2.attr[at];   
              }   
              //fitness value of child1 and child2.
              //child1.
              pair<object,double> rule_data1;
              object obj=child1.own;
              double d1=0; 
              rule_data1=make_pair(obj,d1);
              double div=0;
              double fvr=0;
              for(ll j=0;j<rule_data1.first.attr.size();j++){
                 if(rule_data1.first.attr[j]!="*"){
                     rule x;
                     x.atr_no=j;
                     x.atr_val=rule_data1.first.attr[j];
                     x.dis=rule_data1.first.dis;
                     fvr+=fitnessval(x);
                     div=div+1;
                  }
               }
               fvr=fvr/div; // average fitness value of each rule row.
               rule_data1.second=fvr; // store it.
               child1.fv=rule_data1.second;
              //child2.
              pair<object,double> rule_data2;
              obj=child2.own;
              double d2=0;
              rule_data1=make_pair(obj,d2);
              div=0;
              fvr=0;
              for(ll j=0;j<rule_data2.first.attr.size();j++){
                 if(rule_data2.first.attr[j]!="*"){
                     rule x;
                     x.atr_no=j;
                     x.atr_val=rule_data2.first.attr[j];
                     x.dis=rule_data2.first.dis;
                     fvr+=fitnessval(x);
                     div=div+1;
                  }
               }
               fvr=fvr/div; // average fitness value of each rule row.
               rule_data2.second=fvr; // store it.
               child2.fv=rule_data2.second;
              // compare with 2 worst fv in the population if better then replace with child1 and child2. 
              if(child1.fv>child2.fv){
                  if(child2.fv>crossv[crossv.size()-1].fv)
                     crossv[crossv.size()-1]=child2;
                  if(child1.fv>crossv[crossv.size()-2].fv)
                     crossv[crossv.size()-1]=child1; 
              }     
              else{
                  if(child1.fv>crossv[crossv.size()-1].fv)
                     crossv[crossv.size()-1]=child1;
                  if(child2.fv>crossv[crossv.size()-2].fv)
                     crossv[crossv.size()-1]=child2; 
              }   
         } 
     }
  } 
  string r1="rules_GENETIC.txt";
  ofstream fp(r1.c_str(),ofstream::app);
  //print rules.
  vector<gen_rule> :: iterator it;
  for(it=crossv.begin();it!=crossv.end();it++){
     
     for(ll i=0;i<m;i++)           // Print to the file "rules_GENETIC.txt".
        fp<<it->own.attr[i]<<",";
     fp<<it->own.dis<<endl;
  }
  fp.close();
  rule_data.clear();
}
