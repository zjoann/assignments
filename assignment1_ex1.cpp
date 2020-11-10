#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

static const int TESTS = 5;

typedef unsigned int data_type;
typedef unsigned short int counter;

void ones_counter(data_type d_t, counter cnt){
  data_type a;

  for(int i=0; i<=31; ++i){
        a = 1;
    if((d_t&(a<<i)) != 0){
        cnt = cnt + 1;
        }
     else cnt = cnt;
  }
   cout<<"Number of ones:"<<cnt<<endl;
}

main(){

    srand(time(NULL));
    data_type data;
    counter count1 = 0;

    for(int i=0; i<=TESTS; ++i){
     data = rand();
      cout<<"The number is:"<<data<<endl;
       ones_counter(data, count1);
}
return(0);
}
