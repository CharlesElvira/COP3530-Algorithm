#include<unistd.h>
#include<fstream>
#include<stdlib.h>
#include<iostream>
int main(int, char**){
int size1=0,sizeaddi1=0;
std::cout<<"max randomize first list size: ";
std::cin>>size1;
std::cout<<"max randomize number of additional list: ";
std::cin>>sizeaddi1;
srand ( time(NULL) );
std::ofstream myfile;
  myfile.open("input.txt");
int size = 0;
while(size<=0){
size = rand()% size1;
}
myfile<<size<<std::endl;

int *list=new int[size];

 
for(int i = 0 ; i < size;i++){
if(i+1<size){
list[i]= rand()%200;
myfile<<list[i]<<" ";

}
else
{
list[i]= rand()%200;
myfile<<list[i];
}
}

int addi=0;
while(addi <= 0){
addi = rand()%20;
}
myfile<<std::endl<<addi;
int *list1=new int[addi];

int step =0, step1=0;
std::cout<<"Size of Step";
std::cin>>step1;
while (step <=0)
{
step= rand()%step1;

}
//myfile<<step<<std::endl;
int sizeaddi=0;
while(sizeaddi <= 0 &&(step * addi)<size ){
sizeaddi = rand()%sizeaddi1;
}
//myfile<<sizeaddi<<std::endl;
for(int i = 0; i<addi; i++){
myfile<<std::endl<<step<<std::endl;


myfile<<sizeaddi<<std::endl;
for(int j = 0 ; j < sizeaddi;j++){
if(j+1<sizeaddi ){
list1[j]=rand()%200;
myfile<<list1[j]<<" ";
} else
{
list1[j]=rand()%200;
myfile<<list1[j];

}
}


}
myfile<<std::endl;
myfile.close();
}
