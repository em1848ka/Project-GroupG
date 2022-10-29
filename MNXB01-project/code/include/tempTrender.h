#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>
#include <vector>
#include <TH1F.h> 
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TGraph.h>
class tempTrender {
	public:
	explicit tempTrender(const std::string& filePath) ; //Construct using the specified file

	~tempTrender() {} //Destructor
	
	void tempOnDay(int monthToCalculate, int dayToCalculate) const; //Make a histogram of the temperature on this day
	void tempPerDay(int year) const; //Make a histogram of the average temperature of each day of the year
	void tempPerMonth(int month) const; //Make a histogram of the average temperature of each day of a month
	private:
	std::vector<string> dataArray;
};
#endif
