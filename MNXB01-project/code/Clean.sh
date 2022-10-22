#Removes all ; and any lines longer than 27 chars and shorter than 23(arbitrary),
sed 's/;/ /g' LundData.csv | awk 'length($0)<27'  | awk 'length($0)>23' | cat > CleanedLundData.csv  
#(note, this removes first 10 measurements from o.g file)
