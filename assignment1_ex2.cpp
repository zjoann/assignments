#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

typedef unsigned int data_type;

void checksum(data_type A){
  int x=1;
  int digit[10];
  int sum;
  int n;
  int m;

 for(int i=0; i<=9; ++i){
    digit[i] = (A/x) %10;
    x = x*10;
    cout<<"digit "<<i<<" is: "<<digit[i]<<endl;
 }

    for(int j=1; j<=9; j+=2){
       digit[j] = 2*digit[j];
         if (digit[j] >= 10){
           digit[j] = (digit[j])%10 + ((digit[j])/10)%10;
         }
    }
   sum = digit[0] + digit[1] + digit[2] + digit[3] + digit[4] + digit[5] + digit[6] + digit[7] + digit[8] + digit[9];

    cout<<"Sum of digits: "<<sum;
}

int main()
{
      srand(time(NULL));
    data_type thisNumber;
    thisNumber = rand();
    cout<<"My number is:"<<thisNumber<<endl;
    checksum(thisNumber);

        return 0;
}
