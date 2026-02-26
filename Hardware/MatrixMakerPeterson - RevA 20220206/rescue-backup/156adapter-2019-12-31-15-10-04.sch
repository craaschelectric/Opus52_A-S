EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:156adapter-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1400 1800 4600 1800
Wire Wire Line
	1400 1900 4600 1900
Wire Wire Line
	1400 2000 5050 2000
Wire Wire Line
	1400 2100 5050 2100
$Comp
L Conn_01x12 J1
U 1 1 5A3EB6EB
P 1200 2300
F 0 "J1" H 1200 2900 50  0000 C CNN
F 1 "Conn_01x12" H 1200 1600 50  0000 C CNN
F 2 "CLRConnector:KK156-12" H 1200 2300 50  0001 C CNN
F 3 "" H 1200 2300 50  0001 C CNN
	1    1200 2300
	-1   0    0    -1  
$EndComp
$Comp
L R_Pack02 DN1
U 1 1 5AD21C9B
P 4800 1800
F 0 "DN1" V 4600 1800 50  0000 C CNN
F 1 "BAV23,235" V 4900 1800 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 4975 1800 50  0001 C CNN
F 3 "" H 4800 1800 50  0001 C CNN
	1    4800 1800
	0    -1   -1   0   
$EndComp
Text Notes 4400 1650 0    60   ~ 0
ANODE pins 3&4
Text GLabel 6050 1800 2    60   Input ~ 0
D0
Text GLabel 6050 1900 2    60   Input ~ 0
D1
Text GLabel 6050 2000 2    60   Input ~ 0
D2
Text GLabel 6050 2100 2    60   Input ~ 0
D3
Wire Wire Line
	5000 1800 6050 1800
Wire Wire Line
	5000 1900 6050 1900
Wire Wire Line
	5450 2000 6050 2000
Wire Wire Line
	6050 2100 5450 2100
Wire Wire Line
	1400 2200 4600 2200
Wire Wire Line
	1400 2300 4600 2300
Wire Wire Line
	1400 2400 5050 2400
Wire Wire Line
	1400 2500 5050 2500
Text GLabel 6050 2200 2    60   Input ~ 0
D4
Text GLabel 6050 2300 2    60   Input ~ 0
D5
Text GLabel 6050 2400 2    60   Input ~ 0
D6
Text GLabel 6050 2500 2    60   Input ~ 0
D7
Wire Wire Line
	5000 2200 6050 2200
Wire Wire Line
	5000 2300 6050 2300
Wire Wire Line
	5450 2400 6050 2400
Wire Wire Line
	6050 2500 5450 2500
Wire Wire Line
	1400 2600 4600 2600
Wire Wire Line
	1400 2700 4600 2700
Wire Wire Line
	1400 2800 5050 2800
Wire Wire Line
	1400 2900 5050 2900
Text GLabel 6050 2600 2    60   Input ~ 0
D8
Text GLabel 6050 2700 2    60   Input ~ 0
D9
Text GLabel 6050 2800 2    60   Input ~ 0
D10
Text GLabel 6050 2900 2    60   Input ~ 0
D11
Connection ~ 3900 2600
Connection ~ 3800 2700
Connection ~ 3700 2800
Connection ~ 3600 2900
Wire Wire Line
	5000 2600 6050 2600
Wire Wire Line
	6050 2700 5000 2700
Wire Wire Line
	5450 2800 6050 2800
Wire Wire Line
	6050 2900 5450 2900
Text GLabel 7650 2500 0    60   Input ~ 0
D0
Text GLabel 8150 2500 2    60   Input ~ 0
D1
Text GLabel 7650 2600 0    60   Input ~ 0
D2
Text GLabel 8150 2600 2    60   Input ~ 0
D3
Text GLabel 7650 2700 0    60   Input ~ 0
D4
Text GLabel 8150 2700 2    60   Input ~ 0
D5
Text GLabel 7650 2800 0    60   Input ~ 0
D6
Text GLabel 8150 2800 2    60   Input ~ 0
D7
$Comp
L Conn_01x12 J3
U 1 1 5AD226FC
P 2400 1300
F 0 "J3" H 2400 1900 50  0000 C CNN
F 1 "Conn_01x12" H 2400 600 50  0000 C CNN
F 2 "CLRConnector:2.5mmW2BStaggered12pin" H 2400 1300 50  0001 C CNN
F 3 "" H 2400 1300 50  0001 C CNN
	1    2400 1300
	0    1    -1   0   
$EndComp
Wire Wire Line
	1800 1500 1800 2900
Connection ~ 1800 2900
Wire Wire Line
	1900 1500 1900 2800
Connection ~ 1900 2800
Wire Wire Line
	2000 1500 2000 2700
Connection ~ 2000 2700
Wire Wire Line
	2100 1500 2100 2600
Connection ~ 2100 2600
Wire Wire Line
	2200 1500 2200 2500
Connection ~ 2200 2500
Wire Wire Line
	2300 1500 2300 2400
Connection ~ 2300 2400
Wire Wire Line
	2400 1500 2400 2300
Connection ~ 2400 2300
Wire Wire Line
	2500 1500 2500 2200
Connection ~ 2500 2200
Wire Wire Line
	2600 1500 2600 2100
Connection ~ 2600 2100
Wire Wire Line
	2700 1500 2700 2000
Connection ~ 2700 2000
Wire Wire Line
	2800 1500 2800 1900
Connection ~ 2800 1900
Wire Wire Line
	2900 1500 2900 1800
Connection ~ 2900 1800
$Comp
L R_Pack02 DN5
U 1 1 5AD22C8B
P 5250 2000
F 0 "DN5" V 5050 2000 50  0000 C CNN
F 1 "BAV23,235" V 5350 2000 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 5425 2000 50  0001 C CNN
F 3 "" H 5250 2000 50  0001 C CNN
	1    5250 2000
	0    -1   -1   0   
$EndComp
$Comp
L R_Pack02 DN2
U 1 1 5AD22CBC
P 4800 2200
F 0 "DN2" V 4600 2200 50  0000 C CNN
F 1 "BAV23,235" V 4900 2200 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 4975 2200 50  0001 C CNN
F 3 "" H 4800 2200 50  0001 C CNN
	1    4800 2200
	0    -1   -1   0   
$EndComp
$Comp
L R_Pack02 DN6
U 1 1 5AD22CEE
P 5250 2400
F 0 "DN6" V 5050 2400 50  0000 C CNN
F 1 "BAV23,235" V 5350 2400 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 5425 2400 50  0001 C CNN
F 3 "" H 5250 2400 50  0001 C CNN
	1    5250 2400
	0    -1   -1   0   
$EndComp
$Comp
L R_Pack02 DN7
U 1 1 5AD22D27
P 5250 2800
F 0 "DN7" V 5050 2800 50  0000 C CNN
F 1 "BAV23,235" V 5350 2800 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 5425 2800 50  0001 C CNN
F 3 "" H 5250 2800 50  0001 C CNN
	1    5250 2800
	0    -1   -1   0   
$EndComp
$Comp
L R_Pack02 DN3
U 1 1 5AD22DD6
P 4800 2600
F 0 "DN3" V 4600 2600 50  0000 C CNN
F 1 "BAV23,235" V 4900 2600 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-143" V 4975 2600 50  0001 C CNN
F 3 "" H 4800 2600 50  0001 C CNN
	1    4800 2600
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x06 J2
U 1 1 5AFB8F61
P 7850 2700
F 0 "J2" H 7850 3000 50  0000 C CNN
F 1 "Conn_01x06" H 7850 2300 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H6-2.54" H 7850 2700 50  0001 C CNN
F 3 "" H 7850 2700 50  0001 C CNN
	1    7850 2700
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J4
U 1 1 5AFB8FE6
P 7950 2700
F 0 "J4" H 7950 3000 50  0000 C CNN
F 1 "Conn_01x06" H 7950 2300 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H6-2.54" H 7950 2700 50  0001 C CNN
F 3 "" H 7950 2700 50  0001 C CNN
	1    7950 2700
	-1   0    0    -1  
$EndComp
Text GLabel 7650 2900 0    60   Input ~ 0
D8
Text GLabel 7650 3000 0    60   Input ~ 0
D10
Text GLabel 8150 2900 2    60   Input ~ 0
D9
Text GLabel 8150 3000 2    60   Input ~ 0
D11
Wire Wire Line
	7700 1400 7700 1500
Wire Wire Line
	7700 1600 7700 1800
$Comp
L Conn_01x06 J5
U 1 1 5AFB9DCE
P 7900 1600
F 0 "J5" H 7900 1900 50  0000 C CNN
F 1 "Conn_01x06" H 7900 1200 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H6-2.54" H 7900 1600 50  0001 C CNN
F 3 "" H 7900 1600 50  0001 C CNN
	1    7900 1600
	1    0    0    -1  
$EndComp
Connection ~ 7700 1700
$EndSCHEMATC
