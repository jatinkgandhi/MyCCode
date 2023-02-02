import csv
import os.path


outputfile = 'sensordata.csv'

header = ['Data 1', 'Data 2', 'Data 3', 'Data 4']

# string format data coming from UART., 
# Need to convert integer to string before sending out from the arduino/controller
# sprintf(buffer, "Data 1 %d, Data 2 %d, Data 3 %d, Data 4 %d\n");
# or equivalent method.,
# from_uart can be individually fetched line. for testing we are using list.

from_uart = [   "Data 1 234, Data 2 34, Data 3 14, Data 4 99",
                "Data 1 236, Data 2 33, Data 3 16, Data 4 102",
                "Data 1 238, Data 2 33, Data 3 18, Data 4 105",
                "Data 1 230, Data 2 33, Data 3 13, Data 4 108"
            ]

writeheader = True;
if os.path.exists (outputfile) and os.path.isfile (outputfile):
    writeheader = False;

# without newline='', it will add extra empty line.
resultfile = open(outputfile, 'a', newline='', encoding='UTF8')

# create the csv writer
writer = csv.writer(resultfile)

if (writeheader):
    # write the header
    writer.writerow(header);


for line in from_uart:
    print (line);
    line = line.replace(',', '');

    data = line.split(" ");

    values = [ data[2], data[5], data[8], data [11] ]
    # write the data
    writer.writerow(values);

