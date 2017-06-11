/*
    External module for 10 fold cross validation
*/
/////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string>
#include<bits/stdc++.h>
#define False 0
#define True 1
#define Max_Example_Length  500


 struct Example
        {
                      char Line[Max_Example_Length];
                      short Group_No;
                      short Status;
       };


//int global_count;
//float ACCURACY[100];
void C4P5Rules_ten_fold(char * filename);
//void Find_Accuracy_C4P5Rules();
//void C4P5Rules_avg_accu_sd();
int main(int argc,char **argv)
    {
         char command[200],command1[200];
         char file_command[200];
         int  No_Of_Times,Track,ii=0;


         if(argc!=3)
           {
               printf("\\a.out  <filestem> <no_of_times>\\ \n");
               exit(0);
           }

         No_Of_Times=*argv[2]-'0';
/*   Names_file_operation(argv[8]);*/
         //global_count=0;
         char a1[]="";
         char a2[]="";
         char a3[]=""; 
         while(ii< No_Of_Times)
            {
              C4P5Rules_ten_fold(argv[1]);
             for(Track=1;Track<=10;Track++)
                {
                   sprintf(file_command,"%s%s%d","_10_fold_",argv[1],Track);

                   sprintf(command,"%s.data",file_command);
                   printf("\n now process....... %s ",command);
                   sprintf(command,"%s.test",file_command);
                   printf("\n now process....... %s\n\n ",command);
     
 
                   //sprintf(command,"%s.names",file_command);
                   sprintf(command1,"cp %s.names %s",argv[1],command);
                   system(command1); 


                   sprintf(command,"%s.data",file_command);
                   //sprintf(command1,"./c4.5  %s %s <%s %s",a2,a3,command,file_command);
                   system(command1);


                  sprintf(command,"%s.unpruned",file_command);
                  //sprintf(command1,"./c4.5rules %s %s <%s %s > %s",a2,a3,command,file_command,"C4P5Rules_Accuracy");
                  system(command1);
            
                 //Find_Accuracy_C4P5Rules();
                 printf("\n................................................\n");
               /*  sprintf(command,"rm %s.data",file_command);
                 system(command);
                 sprintf(command,"rm %s.names",file_command);
                 system(command);
                 sprintf(command,"rm %s.tree",file_command);
                 system(command);
                 sprintf(command,"rm %s.unpruned",file_command);
                 system(command);
                 sprintf(command,"rm %s.rules",file_command);
                 system(command);
                 sprintf(command,"rm %s.test",file_command);
                 system(command);*/
                 //system("rm C4P5Rules_Accuracy");
            }
          ii++;
        }
      //C4P5Rules_avg_accu_sd();

      printf("\n");

    }
/**********************************************************************/

 void C4P5Rules_ten_fold(char * filename)
    {
      FILE *fp1,*fp2,*k;
      struct Example *An_Example;
     int No_Of_Lines,Index,Index1,Limit,i,count=0,count1=0;
     long int temp;
    short Increment=1,Group_No=1;
    char arr[50],filestem[100],example[100],cm[100];
    float accuracy[10],ava_acc;
    int acc=0;
    strcpy(filestem,filename);
   strcpy(example,filestem);
   strcat(example,".data");
   strcpy(cm,filename);
   strcat(cm,".cm");
   sprintf(arr,"%s%s%s","wc -l ",example," > temp ");
   system(arr);
  fp1=fopen("temp","r");
  fscanf(fp1,"%d",&No_Of_Lines);
  fclose(fp1);
  remove("temp");

  An_Example=(struct Example *)malloc(sizeof(struct Example)*No_Of_Lines);
   Index=0;

   fp1=fopen(example,"r");

   while(Index<No_Of_Lines)
    {
     fgets(An_Example[Index].Line,Max_Example_Length,fp1);
     An_Example[Index].Status=False;
     Index++;
     }
    fclose(fp1);

    Index=0;
    Limit=No_Of_Lines/10;
    Limit*=10;
    while(Index<Limit)
       {
        while(1)
         {
	       /*temp=rand()%RAND_MAX;*/
	       temp=rand()%32767;
               /*temp=(long int)((float)temp*No_Of_Lines/(RAND_MAX+0.0)); */
               temp=(long int)((float)temp*No_Of_Lines/(32767+0.0)); 
              if(temp<No_Of_Lines)
                {
                  if(An_Example[temp].Status==False)
                    break;
                }
         }
        An_Example[temp].Status=True;
        An_Example[temp].Group_No=Group_No;
        Increment++;
        if(Increment>No_Of_Lines/10)
            {
               Group_No++;
               Increment=1;
             }
         Index++;
        }
       Index=0;
       Group_No=1;

       while(Index<No_Of_Lines)
         {
            if(An_Example[Index].Status==False)
              {
              An_Example[Index].Group_No=Group_No;
                Group_No++;
              }
           Index++;
         }

       for(Index=1;Index<=10;Index++)
          {
            count=Index;count1=Index;
            sprintf(cm,"%s%s%d%s","_10_fold_",filename,Index,".test");
           fp1=fopen(cm,"w");
           sprintf(example,"%s%s%d%s","_10_fold_",filename,Index,".data");
           fp2=fopen(example,"w");
           for(Index1=0;Index1<No_Of_Lines;Index1++)
             {
                if(An_Example[Index1].Group_No!=*(&Index))
                  {
                    count++; 
                    fprintf(fp2,"%s",An_Example[Index1].Line);
                  }
                else
                 {
                    count1++;
                    fprintf(fp1,"%s",An_Example[Index1].Line);
                 }
              }
           fclose(fp1);
           fclose(fp2);
           printf("\n%s---->   %d  ,  %s---->   %d",cm,count1-Index,example,count-Index);
        }

      printf("\n");
    }
/************************************************************************************************************/
/* void Find_Accuracy_C4P5Rules()
      {
         FILE *fp;
         char dd[500],*p,command[100],accuray[10];
         int i,deno=10,flag=0,FLAG=0;
         float k=0,term;
         fp=fopen("C4P5Rules_Accuracy","r");
         if(fp==NULL)
           {

             printf("\n FILE C4P5Rules unable to open\n");
                 exit(0);
           }
        fscanf(fp,"%[^\n]",dd);
        fgetc(fp);
        while(!feof(fp))
            {
               
                 p=strstr(dd,"Tested");
                 if(p && FLAG==1)
                   {
                        p=strtok(dd,"(");
                       p=strtok(NULL,"(");
                      i=0;
                     while(*p!='%')
                    {
                       if(*p!=' ')
                        dd[i++]=*p;
                        p++;
                     }
                   dd[i]='\0';
                   strcpy(accuray,dd);
          }
         if(p)  FLAG=1;
         strcpy(dd,"\0");
         fscanf(fp,"%[^\n]",dd);
         fgetc(fp);
      }
      fclose(fp);

      /********************************* STRING TO FLOAT CONVERSION *********************/

 /*          i=0;
           while(accuray[i]!='\0')
            {
              if(accuray[i]=='.')
                {
                   flag=1;
                  i++;
                }
            if(flag==0)
              {
                k=k*10+(accuray[i]-'0');
              }
            else
              {
                 term=accuray[i]-'0';
                 k=k+term/deno;
                 deno=deno*10;
              }
             i++;
           }
         ACCURACY[global_count]=100.0-k;
         printf("\n C4p5Rules's Accuracy.......................   ");
       printf("%f\n",ACCURACY[global_count]);
  global_count++;
        }
*/
/************************************************************************************************************/
 /*  void C4P5Rules_avg_accu_sd()
    {

        int i;
        float  AVG_ACCU,SD;
        float  SUM_ACCU=0,SQR_TOTAL=0;
       for(i=0;i<global_count;i++)
           {
                 SUM_ACCU=SUM_ACCU+ACCURACY[i];
                 SQR_TOTAL=SQR_TOTAL+ACCURACY[i]*ACCURACY[i];
          }
       AVG_ACCU= SUM_ACCU/global_count;
       SD=sqrt(SQR_TOTAL/global_count - AVG_ACCU*AVG_ACCU);
       
      printf("\n C4P5Rules's average accuracy= %f\n",AVG_ACCU);
      printf("\n C4P5Rules's standard deviation= %f\n",SD);
   }*/

/*************************************************************************************************/

