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
	cout<< "PART1 RECURSIVE SOLUTION" << endl;
	int recursiveSol=recursiveSolution(ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit);
	
	cout<< "\n\n\n\nPART2 DYNAMIC SOLUTION" << endl;
	cout<< "The max profit for the dynamic solution is " <<dynamicSolution(sharesLeft, ranges, priceAtDay, day, profit, shares, priceDrop, size,  maxProfit) << "\n";
	cout<< "The max profit for the recursive solution is " << recursiveSol<< "\n";
	cout<< "\n\nTHE DYNAMIC MAP IS.... \n";
	for(map<pair<int, int>, int>::iterator it=sharesLeft.begin(); it!=sharesLeft.end();it++){
		cout << "sharesLeft:" <<it->first.first << " day " << it->first.second << " and the amount sold for that key is " << it->second << endl;
	}
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
					
					priceDrop+=range->second;
					profit+= (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop );
					cout<< "Profit is: " << profit << " =" << temp1 <<" " << " + " << (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop )<< "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << range->first.second << " shares\n"  << endl;
					sharesLeft-=range->first.second;
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
				if(it->second >= range->first.first && sharesLeft <=range->first.second){
					//for testing
					int temp1=profit;
					priceDrop+=range->second;
					cout << "DAYS LEFT " << daysLeft << "AND PRICE AT THIS DAY IS" << priceAtDay[ numberOfDays - 1 - daysLeft] << "&& shares left after sale are " <<sharesLeft << endl;
					profit+= it->second*( (priceAtDay[ numberOfDays - 1 - daysLeft]) - priceDrop );
					cout<< "IM IN DYNAMIC PART...Profit is: " << profit << "= " << temp1 << " + " << it->second*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\ni had shares= : "<< it->first.first << "\nI sold " << it->second << " shares\n"  << endl;
					break;
				}
			}
			daysLeft--;
			cout<< "shares left are " << sharesLeft << " and days left are " << daysLeft;
			
			pair<int, int> key(sharesLeft,daysLeft);
			it=sharesAtDay.find(key);
		}
		cout << "IM NOT REPEATING";
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
				//MAKE PAIR TO POPULATE DYNAMIC MAP
				pair<int,int> key(sharesLeft,daysLeft);
				
				cout<< "Profit is: " << profit << "= " << temp1 << " + " << temp*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop ) << "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << temp << " shares\n"  << endl;
				sharesLeft-=sharesLeft;
				int calcProfit=dynamicSolution(sharesAtDay,ranges, priceAtDay, daysLeft-1, profit, sharesLeft, priceDrop, numberOfDays, maxProfit);
				if(calcProfit >  maxProfit){
					//cout<< "IM POPULTATING MAP sharesLeft: " << key.first << " day: " << key.second << "
					sharesAtDay[key]=key.first;
					maxProfit=calcProfit;
				}
			}
		}
		return profit;
	}else{
		
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
					cout<< "Profit is: " << profit << " =" << temp1 <<" " << " + " << (range->first.second)*( (priceAtDay[ numberOfDays-1-daysLeft]) - priceDrop )<< "\nday is" << daysLeft << "\npriceDrop is: " <<priceDrop<< "\nsharesLeft= : "<< sharesLeft << "\nI sold " << range->first.second << " shares\n"  << endl;
					//MAKE PAIR TO POPULATE DYNAMIC MAP
					pair<int,int> key(sharesLeft,daysLeft);
					sharesLeft-=range->first.second;
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
 