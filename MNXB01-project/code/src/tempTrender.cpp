#include <iostream>
#include "../include/tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	ifstream dataFile(filePath);
	string line;
    while(!dataFile.eof()){		
		getline (dataFile,line);
    	dataArray.push_back(line);
	}
	dataFile.close();
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { 
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);		
	for (const string &data: dataArray){
		if(!data.empty()){
			int monthOfDate = std::stoi(data.substr(5,2));
			int dayOfDate = std::stoi(data.substr(8,2));
			if( monthOfDate == monthToCalculate && dayOfDate == dayToCalculate){
				double temp = std::stod(data.substr(20,4));
				hist->Fill(temp);
			}
		}
	}
	TCanvas* can = new TCanvas();
	hist->Draw();
}	
	

	


// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
