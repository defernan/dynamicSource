//
//  main.cpp
//  dynamicProgramming
//
//  Created by Stephen Kennicutt on 10/22/14.
//  Copyright (c) 2014 Stephen Kennicutt. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

void calcTable(map<pair<int, int>, int> &table, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int shares);
//DEZMON WORKED HERE ************************************************************************************************************************************

int recursiveSolution(map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit);
int dynamicSolution(map<pair<int,int>, int> &sharesAtDay, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit);
//DEZMON ENDED HERE**************************************************************************************************************************************
int main(int argc,  char * argv[]) {
   
    
    //Set up tests;
    int shares = 100000;
    int priceAtDay[3] = {90, 80, 40};
    //We will define the ranges for the
    map<pair<int, int>, int> ranges;
    ranges[pair<int,int>(0,40000)] = 1;
    ranges[pair<int,int>(40001,shares)] = 20;
	map<int, int> table; 
	int size = 3;
	//made this 2 because on day one, there are 2 days left
    int day = 2;
    int profit = 0;
    int price =0;
	int priceDrop=0;
	int maxProfit=0;
    //DEZMON WORKED HERE ************************************************************************************************************************************
	//the key is how many shares are left on that day, the value is the how many we sold(the choice we made) associated with it
	map<pair<int, int>, int> sharesLeft;
	cout<< "PART1 RECURSIVE SOLUTION" << endl;
	cout<< "The max profit for the recursive solution is " <<recursiveSolution(ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit) << "\n";
	cout<< "PART2 DYNAMIC SOLUTION" << endl;
	cout<< "The max profit for the dynamic solution is " <<dynamicSolution(sharesLeft, ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit) << "\n";
	cout<< "\n\nTHE DYNAMIC MAP IS.... \n";
	for(map<pair<int, int>, int>::iterator it=sharesLeft.begin(); it!=sharesLeft.end();it++){
		cout << "sharesLeft:" <<it->first.first << " day " << it->first.second << " and the amount sold for that key is " << it->second << endl;
	}
	//cout<< calcProfit(sharesLeft, ranges, priceAtDay, day, profit, shares) << "\n";
    //DEZMON ENDED HERE**************************************************************************************************************************************
   
    
    //Think about sorting ranges....
    //cout << "The table shows that..." << endl;
   /* calcTable(table, ranges, priceAtDay, day, shares);
    for (auto it = table.rbegin(); it != table.rend(); it++) {
        cout << it->first.first << " shares were sold on day " << it->first.second << " for a profit of " << it->second << endl;
    }*/
    system("pause");
	return 0;
}
//DEZMON WORKED HERE ************************************************************************************************************************************
////////RECURSIVE SOLUTION///////////////
int recursiveSolution(map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit){
	if(sharesLeft==0){
		return profit;
	}
	//case where you run out of days and must sell all
	if(daysLeft == 0){
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			if(sharesLeft >= range->first.first && sharesLeft <=range->first.second){
				//for testing
				int temp1=profit;
				int temp=sharesLeft;
				priceDrop+=range->second;
				profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
				sharesLeft-=sharesLeft;
				cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
				int calcProfit=recursiveSolution(ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
				if(calcProfit >  maxProfit){
					maxProfit=calcProfit;
				}
			}
		}	
	}else{
		//iterate through ranges and make recursive call
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			//check if there enough shares left to sell at this price range
			if(sharesLeft >= range->first.first){
				//sell max amount at range, otherwise sell everything we have left
				if(sharesLeft >= range->first.second){
					//for printing
					int temp1=profit;
					//decrement what were  selling and incorporate price drop
					sharesLeft-=range->first.second;
					priceDrop+=range->second;
					profit+= (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					cout<< "Profit is: " << profit << " =" << temp1 <<" " << " + " << (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop )<< "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << range->first.second << " shares\n"  << endl;
					//recursive call
					int calcProfit=recursiveSolution(ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						maxProfit=calcProfit;
					}
					cout<< "\nend of recursion profit is " << calcProfit << " && max profit is:" << maxProfit<< "\n\n\n\n";
					//restore profit, Stocks, and price drop
					profit-=(range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					sharesLeft+=range->first.second;
					priceDrop-=range->second;

				}else{
					//just for testing/printing
					int temp=sharesLeft;
					int temp1= profit;

					priceDrop+=range->second;
					profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					sharesLeft-=sharesLeft;
					cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
					int calcProfit=recursiveSolution(ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						maxProfit=calcProfit;
					}
				}
			}
		}
	}
	return maxProfit;
}
///////DYNAMIC SOLUTION////////////
int dynamicSolution(map<pair<int,int>, int> &sharesAtDay, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit){
	if(sharesLeft==0){
		return profit;
	}
	//CREATE PAIR FOR DYNAMIC PROGRAMMING
	pair<int, int> key(sharesLeft,daysLeft);
	//CHECK IF WE HAVE ALREADY FOUND THE PATH
	map<pair<int,int>, int>::iterator it=sharesAtDay.find(key);
	//IF WE FIND A VALUE IN OUR MAP, JUST FOLLOW IT BY DECREMENTING THE SHARES IN THE MAP, WILL TAKE US TO THE NEXT DECISION WE MADE
	if(it!=sharesAtDay.end()){
		while(it!=sharesAtDay.end()){
			sharesLeft-=it->second;
			for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
				if(sharesLeft >= range->first.first && sharesLeft <=range->first.second){
					//for testing
					int temp1=profit;
					priceDrop+=range->second;
					profit+= it->second*( (priceAtDay[ it->first.second]) - priceDrop );
					cout<< "IM IN DYNAMIC PART...Profit is: " << profit << "= " << temp1 << " + " << it->second*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << it->first.second << "\npriceDrop is: " <<priceDrop<< "\ni had shares= : "<< it->first.first << "\nI sold " << it->second << " shares\n"  << endl;
				}
			}
			pair<int, int> key(sharesLeft,daysLeft--);
			it=sharesAtDay.find(key);
		}
		if(profit >  maxProfit){
			maxProfit=profit;
		}
		return profit;
	}
	//HAVE NOT ADJUSTED DYNAMIC PART FOR THIS AT ALL
	//case where you run out of days and must sell all
	if(daysLeft == 0){
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			if(sharesLeft >= range->first.first && sharesLeft <=range->first.second){
				//for testing
				int temp1=profit;
				int temp=sharesLeft;
				priceDrop+=range->second;
				profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
				sharesLeft-=sharesLeft;
				cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
				int calcProfit=dynamicSolution(sharesAtDay,ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
				if(calcProfit >  maxProfit){
					maxProfit=calcProfit;
				}
			}
		}	
	}else{
		
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			//check if there enough shares left to sell at this price range
			if(sharesLeft >= range->first.first){
				//sell max amount at range, otherwise sell everything we have left
				if(sharesLeft >= range->first.second){
					//for printing
					int temp1=profit;
					//decrement what were  selling and incorporate price drop
					sharesLeft-=range->first.second;
					priceDrop+=range->second;
					profit+= (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					cout<< "Profit is: " << profit << " =" << temp1 <<" " << " + " << (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop )<< "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << range->first.second << " shares\n"  << endl;
					//MAKE PAIR TO POPULATE DYNAMIC MAP
					pair<int,int> key(sharesLeft,daysLeft);
					//recursive call
					int calcProfit=dynamicSolution(sharesAtDay, ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					//NEED TO ADJUST TO POPULATE MAP DYNAMIC CORRECTLY
					if(calcProfit >  maxProfit){
						sharesAtDay[key]=range->first.second;
						maxProfit=calcProfit;
					}
					cout<< "\nend of recursion profit is " << calcProfit << " && max profit is:" << maxProfit<< "\n\n\n\n";
					//restore profit, Stocks, and price drop
					profit-=(range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					sharesLeft+=range->first.second;
					priceDrop-=range->second;

				}else{
					//HAVE NOT ADJUSTED FOR DYNAMIC MAP
					//just for testing/printing
					int temp=sharesLeft;
					int temp1= profit;

					priceDrop+=range->second;
					profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					sharesLeft-=sharesLeft;
					cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
					int calcProfit=dynamicSolution(sharesAtDay, ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						maxProfit=calcProfit;
					}
				}
			}
		}
	}
	return maxProfit;
}
 //DEZMON ENDED HERE**************************************************************************************************************************************
void calcTable(map<pair<int, int>, int> &table, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int shares){
    
    /*
    //We will iterate through the different ranges to calculate the profit at each sale;
    for (auto it = ranges.rbegin(); it != ranges.rend(); it++) {
        
        //First, we will make sure that the values can fit within the range.
        
        if (shares >= it->first.first) {
            
            int sharesToSell;
            
            // We need to make sure that if we sell the maximum amount of shares at the range specified
            if (shares - it->first.first >= 0) {
                sharesToSell = it->first.first;
            }
            else{
                sharesToSell = shares;
            }
            //If the (shares sold, day sold) pair already exists in the table, don't do anything.
            if(table.find(pair<int,int>(sharesToSell, daysLeft)) == table.end()){
                cout << "Not in table" << endl;
                //We will need to either make the "3" variable global or change how days are handled.
                table[pair<int,int>(sharesToSell, daysLeft)] = sharesToSell*priceAtDay[3-daysLeft];
            }
            //Only call recursively if our base case has not been hit.
            if (daysLeft != 1 || shares-sharesToSell != 0) {
                calcTable(table, ranges, priceAtDay, daysLeft--, shares-sharesToSell);
            }
            
            
        }
    }*/
}

