#include <iostream>
#include <ctime>
#include "ac_channel.h"
#include "ac_fixed.h"
#include "ac_int.h"

using namespace std;

static const int W = 4;
typedef ac_int<4, false> dtype;

 void runlength_encode(ac_channel<dtype> &in, ac_channel<dtype> &out){
   dtype data[10];
   dtype data_in;
   ac_int<4, false> cnt = 1;

   if(in.available(10)){
     for(int i=0; i<10; ++i){
        data_in = in.read();
        data[i] = data_in;
        cout<<data[i];
             }
      cout<<"\n";
      for(int j=0; j<10; ++j){
       if(data[j]==data[j+1]){
        cnt++;
       }
       else{
        out.write(data[j]);
        out.write(cnt);
        cnt=1;
       }
      }
    }
 }

int main(){

       srand(time(NULL));

 ac_channel<dtype> in_stream;
 ac_channel<dtype> out_stream;
 dtype out;
 dtype test_input[10]; //= {1,1,1,3,3,2,3,3,9,9};

for(int i=0; i<10; ++i){
  test_input[i] = rand() %10;
  in_stream.write(test_input[i]);
}

runlength_encode(in_stream, out_stream);

while(out_stream.available(1)){
	out = out_stream.read();
	cout << out;
}
return 0;
}
