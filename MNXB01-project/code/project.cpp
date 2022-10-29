#include "include/tempTrender.h"
#include <string>

void project() {
    const std::string pathToFile = "data/CleanedLundData.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
        
        t.tempOnDay(10, 27); //Call some functions that you've implemented
        t.tempPerDay(2000);
	t.tempPerMonth(1);
}
