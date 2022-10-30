# About

This folder contains all the code nessecary to run the functions and create the histograms.

# Data Processing
In the `data` folder you can find both a direct copy of the data set we used called `LundData.csv`, the cleaned up data set `CleanedLundData.csv`, along with the script used to clean it, `Clean.sh`. 

To clean data, ensure it follows the same format as `LundData.csv`. Navigate to the `data` folder and run the following in your terminal.

```bash
./Clean.sh
```
`./Clean.sh` will produce a csv of cleaned data ready to be analyzed, called `CleanedLundData.csv`.

# Data Visualization

**Note:** Before being able to visualize the data, a working version of root is required. If there are errors with root, please refer to course documentation for more details and troubleshooting. 

To run the code that visualizes our data and aggregates it, start by navigating to the `code` directory. Log in to root by running `root` in your terminal. This will automatically run `rootlogon.C` that sets up root for you, including compiling `project.cpp`.

To execute `project.cpp` and generate the histograms, run the following on root:

```
project()
```

This generates three histograms: `tempOnDay.jpg`, `tempPerDay.jpg`, and `tempPerMonth.jpg`. These generated histograms will come up in separate windows and can also be found in the `histograms` directory after running `project()`.
