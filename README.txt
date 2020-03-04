This Project is the development of MPPT (Maximum Power Point Tracker) System. 
This system tracks the mechanical sun to produce maximum power from the solar panel.
The MPPT charges the battery and an inverter is connected with battery to convert
DC to AC for the load attached with it. Furthermore, battery charging is monitored
via LabVIEW and online website is created for monitoring of battery state of charge, 
sun’s position (angle), and power generated from the solar panel.

MICROCONTROLLER

For this system, MSP430 is integrated with the LabVIEW program,
so that the sampling of datas and calculation can be performed easily.
The microcontroller is coded using IAR Embedded System and the code 
is written to sense the analog voltage of the battery, voltage from 
the solar panel, and current from the solar panel.  And finally the 
sensed data are sent to the labVIEW through the USB.

LabVIEW

LabVIEW accepts the datas from microcontroller using the USB port. 
LabVIEW has a driver called Virtual Instrument Software Architecture (VISA)
which is used for configuring programming, and provides the programming 
interface between the hardware and development environment such as LabVIEW.
In this system, data sent through the USB cable is received by the VISA 
open and is sent to VISA Configure Serial Port which reads the data with 
baud rate of 9600 and 8 data bits. And the obtained data is converted into
original ADC reading from ASCII value using Scan from String function.
The function alson trash all the value if the available data is not string.
Then, the sampled value are stacked in array (Battery Voltage, Solar panel 
voltage, and Vout from ACS712 sensor respectively). Now, the obtained values 
are converted into their original values using the voltage divider circuit.

MySQL database 

For this system, a database named ‘state’ is created with table ‘table1’. 
A localhost is hosted using third party application called ‘xampp’ which is 
used to create a local web server for testing and deployment purposes. 
LabVIEW push all the sampled data to the database using the database drive tool kit. 
All the required information is saved in this database table with the specific date 
and time for that data.  

WEBSITE

The ‘Online Monitoring System’ consists of a website which is developed using HTML 
and PHP language.  The website displays all the data i.e. the battery percentage, solar 
panel power, solar panel angle and the date and time of the obtained data. A safe connection 
is established between the database and the website using the localhost and then php language 
is used to load the database table in the website. A jQuery script file is used for the auto 
refresh of the website on every thirty milliseconds so that the website can fetch all the data 
from the database and keep on updating it on the real time.   

