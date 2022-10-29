tail -n +14 LundData.csv | cut -b 1-28 | sed 's/;/  /g' | grep 'G' > CleanedLundData.csv  

