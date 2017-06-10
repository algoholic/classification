/* 
  1st module.
  Takes raw data input from files named file.data.
  //** TESTED.**
*/

struct object{
  vector<string> attr; // Condition attributes. 
  string dis;       // Dicision attribute(class).
};
struct compare {
   bool operator()(const object& left, const object& right) const {
     
       return left.attr < right.attr || (left.attr == right.attr && left.dis < right.dis);
   }
};
vector<object> raw_arr,raw_arrfile,raw_cmp;      //Array of objects with inconsistency. 
//Read raw data from file.data
void read(string &file){ // Method 1.
  string s,str;
  //raw_arr.clear();      /***************************/
  //raw_arrfile.clear();  //   initialize vectors 
  //raw_cmp.clear();      /***************************/
  //string file;  // Data file name input from user.
  //cout<<"Enter the name of data file ( XYZ.data ):";
  //cin>>file;
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
    raw_arr.push_back(temp);
  }  
  set<object,compare> inpst(raw_arr.begin(),raw_arr.end()); // Using set to remove duplicates.
  vector<object> raw_tmp(inpst.begin(),inpst.end());
  raw_arr=raw_tmp;
 
  raw_tmp.clear();
  raw_arrfile=raw_arr;  //contains the raw data of data file.
} 

