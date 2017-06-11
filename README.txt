
//////////   MODULES:   ///////////
/**********************************/

"driver.cpp"  --------------------------- Driver module
"raw_input.cpp"  ------------------------ Module 1
"remove_inconsistency.cpp" -------------- Module 2
"module_matrix.cpp" --------------------- Module 3 
"rule_gen.cpp" -------------------------- Module 4    
"genetic1.cpp" -------------------------- Module 5
"genetic2.cpp" -------------------------- Module 6     
"compare.cpp"  -------------------------- Module 7    // compare efficiency.
"h_cross_rs_genetic.cpp"  ------------------- Module 8(external)

"ACCURACY_RESULT.txt"  some sample(12 files) output of average accuracy.


/////////   HOW TO RUN:   /////////
/**********************************/

$ g++ driver.cpp -o exec
$ ./exec
$ Enter the name of data file ( without .data ):<filename> 

/////////   OUTPUT  /////////////
/********************************/

Accuracy of RS:
Accuracy of GENETIC: 

AVG accuracy of RS & GENETIC for all(i.e. _10_fold<filename>i.test,......>
/////////////////////////////////////////////////////////////////////////////////////////

 
NOTE: 1. Put all .data files to be executed in the same folder with the code modules.
      2. Do not include .names files with .data files. (it will give segfault)
      3. Just ignore the messeges displayed while execution of  "h_cross_rs_genetic.cpp".
      4. No need to run manually "h_cross_rs_genetic.cpp" it is automated inside "driver.cpp"
