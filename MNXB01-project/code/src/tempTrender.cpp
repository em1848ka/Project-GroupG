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
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 200, -15, 25);		
	hist->SetFillColor(kRed+1);
	hist->SetLineColor(kRed+1);
	for (const string &data: dataArray){
		if(!data.empty()){
			int monthOfDate = std::stoi(data.substr(5,2)); //Substring starting at 5 with length 2 corresponds to month in the data set
			int dayOfDate = std::stoi(data.substr(8,2));   //Substring starting at 8 with length 2 corresponds to day in the data set
			if( monthOfDate == monthToCalculate && dayOfDate == dayToCalculate){
				double temp = std::stod(data.substr(22,5));//Substring starting at 22 with length 5 corresponds to temp in the data set
				hist->Fill(temp);
			}
		}
	}
	double mean = hist->GetMean(); 
	double stdev = hist->GetRMS(); 
	TCanvas* c1 = new TCanvas("c1","tempOnDay");	
	TLegend* legend = new TLegend(0.2,0.9,0.5,0.75);
    legend->AddEntry(hist,"Temperatures on 27/10","f");
	legend->SetBorderSize(0);
	hist->Draw();
	legend->Draw();
	c1->SaveAs("tempOnDay.jpg");
}

void tempTrender::tempPerDay(int year) const {
        TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 200, -15, 30);
		hist->SetMinimum(0);
        int currMonth = -1;
		int currDay = -1;
        double sum = 0;
        double n = 0;
	for (const string &data: dataArray){
               if (!data.empty() && year == std::stoi(data.substr(0,4))) {
                   if (currMonth == -1 && currDay == -1) {
                       currMonth = std::stoi(data.substr(5,2));
                       currDay = std::stoi(data.substr(8,2));
                       sum += std::stod(data.substr(22,5));
                       n += 1;
                   } else if (currMonth != std::stoi(data.substr(5,2)) || currDay != std::stoi(data.substr(8,2))) {
                       hist->GetStdDev();
                       hist->Fill(sum/n);
                       hist->SetBinError(n, hist->GetStdDev());
                       currMonth = std::stoi(data.substr(5,2));
  		       		   currDay = std::stoi(data.substr(8,2));
                       n = 1;
                       sum = std::stod(data.substr(22,5));
		   } else {
                       sum += std::stod(data.substr(22,5));
                       n += 1;
                   }
              }
        }
        TCanvas* c2 = new TCanvas("c2","tempPerDay");
		hist->SetMarkerStyle(21);
		hist->SetLineColor(kRed+1);
		hist->SetMarkerColor(1);
		TLegend* legend = new TLegend(0.2,0.9,0.5,0.75);
    	legend->AddEntry(hist,"Temperature per day, year 2000","P");
		legend->SetBorderSize(0);      
		hist->Draw();
		legend->Draw();
		c2->SaveAs("tempPerDay.jpg");
}

// our histogram calculates the average temperature of a month for every year
void tempTrender::tempPerMonth(int month) const {
        TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 200, -20, 20);		
		hist->SetFillColor(kRed+1);
		hist->SetLineColor(kRed+1);
        int currYear = 1863;
        double sum = 0;
        double n = 0;
        for (const string &data: dataArray) {
            if (!data.empty()) {
                if (currYear != std::stoi(data.substr(0,4))) {
                    hist->Fill(sum/n);
                    sum = 0;
                    n = 0;
                }
                if (month == std::stoi(data.substr(5,2))) {
                    sum += std::stod(data.substr(22,5));
                    n += 1;
                }
             }
        }
        TCanvas* c3 = new TCanvas("c3","tempPerMonth");
		TLegend* legend = new TLegend(0.6,0.9,0.9,0.75);
    	legend->AddEntry(hist,"Temperatures in January","f");
		legend->SetBorderSize(0);
        hist->Draw();
		legend->Draw();
		c3->SaveAs("tempPerMonth.jpg");
}
	

// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
