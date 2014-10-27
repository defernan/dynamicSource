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

void calcTable(map<pair<int, int>, int> &table, map<pair<int,int>, int> ranges, int priceAtDay[], int daysLeft, int shares);


int main(int argc,  char * argv[]) {
   
    
    //Set up tests;
    int shares = 100000;
    int priceAtDay[3] = {90, 80, 40};
    //We will define the ranges for the
    map<pair<int, int>, int> ranges;
    ranges[pair<int,int>(0,40000)] = 1;
    ranges[pair<int,int>(40001,shares)] = 20;
    
    
    map<pair<int,int>, int> table;
    int size = 3;
    int day = 3;
    int profit = 0;
    int price =0;
    
    //Think about sorting ranges....
    cout << "The table shows that..." << endl;
    calcTable(table, ranges, priceAtDay, day, shares);
    for (auto it = table.rbegin(); it != table.rend(); it++) {
        cout << it->first.first << " shares were sold on day " << it->first.second << " for a profit of " << it->second << endl;
    }
    system("pause");
	return 0;
}

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

