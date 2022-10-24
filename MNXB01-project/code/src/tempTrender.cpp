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

void tempTrender::tempPerDay(int year) const {
        TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
        int currMonth = -1;
	int currDay = -1; 
        double sum = 0;
        double n = 0;
	for (const string &data: dataArray){
               if (!data.empty() && year == std::stoi(data.substr(0,4))) {
                   if (currMonth == -1 && currDay == -1) {
                       currMonth = std::stoi(data.substr(5,2));
                       currDay = std::stoi(data.substr(8,2));
                       sum += std::stod(data.substr(20,4));
                       n += 1;
                   } else if (currMonth != std::stoi(data.substr(5,2)) || currDay != std::stoi(data.substr(8,2))) {
                       hist->GetStdDev();
                       hist->Fill(sum/n);
                       currMonth = std::stoi(data.substr(5,2));
  		       currDay = std::stoi(data.substr(8,2));
                       n = 1;
                       sum = std::stod(data.substr(20,4));
		   } else {
                       sum += std::stod(data.substr(20,4));
                       n += 1;
                   }
              }
        }
        TCanvas* can = new TCanvas();
        //for(int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
       //     hist->SetBinContent(bin, 5);
        //    hist->SetBinError(bin, sqrt(5.));
        //}
        hist->Draw();
}
	

// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
