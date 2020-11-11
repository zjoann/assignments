#include <iostream>
#include <ctime>
#include "ac_channel.h"
#include "ac_int.h"

using namespace std;

const int TESTS = 3;
typedef ac_int<4,false> Card;

class BlackJack {
  private:
   // internal state
    ac_int<5,false> sumOfCards;
    ac_int<4,false> cnt_samples; //samples=cards
    Card card;

  public:
   // constructor - init internal state
    BlackJack() {
    //reset
     cnt_samples = 0;
     sumOfCards = 0;
    }
    void print_sum(){
	  cout << "cards sum: " << sumOfCards;
    }
    // top-level interface
    void run (ac_channel<Card> &in_card, bool &end_round, bool &win) {

            if(in_card.available(1)){
              card = in_card.read();

            if (card == 1) card = 11;  //ace value = 11

               sumOfCards += card;
               cnt_samples++;

       //check if card 1 AND card 2 are both aces:
            if(cnt_samples == 2){
              if(sumOfCards == 22){
                win = true;
                end_round = true;
                sumOfCards = 21;
             }
           }
            else if(cnt_samples == 5){ //last card..the end_round is for sure, so I have to check whether the sum is <,>or= 21 to get the win signal
                if(sumOfCards <= 21){
                    win = true;
                    end_round = true;
                }
                else{
                    win = false;
                    end_round  = true;
                }
             }
           else{
             if(sumOfCards == 21){
                win = true;
                end_round  = true;
            }
            else if(sumOfCards > 21){
                win = false;
                end_round  = true;
            }
            else {
                win = false;
                end_round = false;
            }
    }
   }
  }
};

int main(int argc, char* argv[]){

    srand(time(NULL));

  Card test_input[TESTS][5];
  Card randomCard;

 for(int i=0; i<TESTS; ++i){
  for(int j=0; j<5; ++j){
    randomCard = rand() % 10 + 1;
    test_input[i][j] = randomCard; //filling each test with 5 random cards
//can't have more than 4 same cards:
      while(test_input[i][1]==test_input[i][2]==test_input[i][3]==test_input[i][4]==test_input[i][5]){
        test_input[i][5] = randomCard;
       }
  }
 }

  for(int i=0; i<TESTS; ++i){
    cout<<"TEST: "<<i+1<<"\n\n";
     ac_channel<Card> crd;
     //initial states:
     bool finished = false;
     bool winner = false;

     BlackJack black;

   for(int j=0; j<5; ++j){
     cout<<"card "<<j+1<<"= "<<test_input[i][j]<<"\n";
      crd.write(test_input[i][j]);
      black.run(crd, finished, winner);

            if(!finished){
                cout << "Give me another one.\n\n";
			}
			else if(winner){
				cout << "\nYou won!\n";
				break;
			}
			else{
				cout << "\nYou lost.\n";
                break;
			}
  }
  black.print_sum();
  cout<<"\n______________________\n\n";
}
  return 0;
}
