//
//  main.cpp
//  dynamicProgramming
//
//  Created by Stephen Kennicutt on 10/22/14.
//  Copyright (c) 2014 Stephen Kennicutt. All rights reserved.
//

#include <iostream>
#include <map>

using namespace std;


int recursiveSolution(map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit);
int dynamicSolution(map<pair<int,int>, int> &sharesAtDay, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int profit, int sharesLeft, int priceDrop, int numberOfDays, int maxProfit);
void traceBack(map<pair<int,int>, int> &sharesAtDay, int shares, int dayOne, int numDays);
int main(int argc,  char * argv[]) {
    //Set up tests;
	const int NUMBER_OF_DAYS=5;
    int shares = 100;
	int priceAtDay[NUMBER_OF_DAYS] = {90, 80, 70, 60, 50};
    //We will define the ranges for the
    map<pair<int, int>, int> ranges;
    ranges[pair<int,int>(0,20)] = 1;
    ranges[pair<int,int>(21,40)] = 3;
	ranges[pair<int,int>(41,60)] = 5;
    ranges[pair<int,int>(61,shares)] = 15;
	map<int, int> table; 
	int size = NUMBER_OF_DAYS;
	//made this -1 because on day one, there are priceAtDay.size-1 days left ie 3 days, day 2 is really the first day
    int day = NUMBER_OF_DAYS-1;
    int profit = 0;
	int priceDrop=0;
	int maxProfit=0;
	//the key is how many shares are left on that day, the value is the how many we sold(the choice we made) associated with it
	map<pair<int, int>, int> sharesLeft;
	//cout<< "PART1 RECURSIVE SOLUTION" << endl;
	int recursiveSol=recursiveSolution(ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit);
	int dynamicSol=dynamicSolution(sharesLeft, ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit);
	//cout<< "\n\n\n\nPART2 DYNAMIC SOLUTION" << endl;
	//cout<< "The max profit for the recursive solution is " << recursiveSol<< "\n";
	cout<< "The max profit for the dynamic solution is " << dynamicSol << "\n";
	
	/*cout<< "\n\nTHE DYNAMIC MAP IS.... \n";
	for(map<pair<int, int>, int>::iterator it=sharesLeft.begin(); it!=sharesLeft.end();it++){
		cout << "sharesLeft:" <<it->first.first << " day " << it->first.second << " and the amount sold for that key is " << it->second << endl;
	}*/
	traceBack(sharesLeft, shares, day, size);
    system("pause");
	return 0;
}

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
				//cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
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
					
					priceDrop+=range->second;
					profit+= (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					//cout<< "Profit is: " << profit << " =" << temp1 <<" " << " + " << (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop )<< "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << range->first.second << " shares\n"  << endl;
					sharesLeft-=range->first.second;
					//recursive call
					int calcProfit=recursiveSolution(ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						maxProfit=calcProfit;
					}
					//cout<< "\nend of recursion profit is " << calcProfit << " && max profit is:" << maxProfit<< "\n\n\n\n";
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
					//cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
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
	//IF WE FIND A VALUE IN OUR MAP, JUST FOLLOW IT BY DECREMENTING THE SHARES IN THE MAP, WILL TAKE US TO THE NEXT DECISION WE MAKE
	if(it!=sharesAtDay.end()){
		while(it!=sharesAtDay.end()){
			sharesLeft-=it->second;
			for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
				if(it->second >= range->first.first && sharesLeft <=range->first.second){
					priceDrop+=range->second;
					profit+= it->second*( (priceAtDay[ numberOfDays - 1 - daysLeft]) - priceDrop );
					break;
				}
			}
			daysLeft--;
			pair<int, int> key(sharesLeft,daysLeft);
			it=sharesAtDay.find(key);
		}
		if(profit >  maxProfit){
			maxProfit=profit;
		}
		return profit;
	}
	//case where you run out of days and must sell all
	if(daysLeft == 0){
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			if(sharesLeft >= range->first.first && sharesLeft <=range->first.second){
				priceDrop+=range->second;
				profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
				//MAKE PAIR TO POPULATE DYNAMIC MAP
				pair<int,int> key(sharesLeft,daysLeft);
				sharesLeft-=sharesLeft;
				int calcProfit=dynamicSolution(sharesAtDay,ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
				if(calcProfit >  maxProfit){
					sharesAtDay[key]=key.first;
					maxProfit=calcProfit;
				}
			}
		}
		return profit;
	}//If path not yet discovered, recurse
	else{
		
		for(map<pair<int,int>,int>::iterator range=ranges.begin(); range!=ranges.end(); range++){
			//check if there enough shares left to sell at this price range
			if(sharesLeft >= range->first.first){
				//sell max amount at range, otherwise sell everything we have left
				if(sharesLeft >= range->first.second){
					//decrement what were  selling and incorporate price drop
					priceDrop+=range->second;
					profit+= (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					//MAKE PAIR TO POPULATE DYNAMIC MAP
					pair<int,int> key(sharesLeft,daysLeft);
					sharesLeft-=range->first.second;
					//recursive call
					int calcProfit=dynamicSolution(sharesAtDay, ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						sharesAtDay[key]=range->first.second;
						maxProfit=calcProfit;
					}
					//restore profit, Stocks, and price drop
					profit-=(range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					sharesLeft+=range->first.second;
					priceDrop-=range->second;

				}else{
					priceDrop+=range->second;
					profit+= sharesLeft*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					pair<int,int> key(sharesLeft,daysLeft);
					sharesLeft-=sharesLeft;
					int calcProfit=dynamicSolution(sharesAtDay, ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
					if(calcProfit >  maxProfit){
						sharesAtDay[key]=range->first.second;
						maxProfit=calcProfit;
					}
				}
			}
		}
	}
	return maxProfit;
}
void traceBack(map<pair<int,int>, int> &sharesAtDay, int shares, int dayOne, int numDays){
	pair<int,int> key(shares,dayOne);
	map<pair<int,int>, int>::iterator it=sharesAtDay.find(key);
	cout<< "The optimal path is... " << endl;
	while(it!=sharesAtDay.end()){
		
		cout << "Sell " << it->second << " shares on day " << numDays-it->first.second << endl;
		dayOne=dayOne-1;
		shares=shares-it->second;
		pair<int,int> key(shares,dayOne);
		it=sharesAtDay.find(key);
	}
}