EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8350 4750 0    60   ~ 0
SEROut2
$Comp
L SerialIOProc-rescue:74HC595-SerialIOProc-rescue U2
U 1 1 5CEA010D
P 3200 4300
AR Path="/5CFC7757/5CEA010D" Ref="U2"  Part="1" 
AR Path="/5CFEE74D/5CEA010D" Ref="U?"  Part="1" 
AR Path="/5CE81FF5/5CEA010D" Ref="U6"  Part="1" 
AR Path="/5CE982AE/5CEA010D" Ref="U?"  Part="1" 
AR Path="/5CEA010D" Ref="U6"  Part="1" 
F 0 "U6" H 3350 4900 50  0000 C CNN
F 1 "74HC597" H 3200 3700 50  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 3200 4300 50  0001 C CNN
F 3 "" H 3200 4300 50  0001 C CNN
	1    3200 4300
	1    0    0    -1  
$EndComp
Text Label 1850 4150 0    60   ~ 0
nRST
Text Label 1850 4050 0    60   ~ 0
SerialCLK
$Comp
L power:VDD #PWR010
U 1 1 5CEA0110
P 3750 900
AR Path="/5CFC7757/5CEA0110" Ref="#PWR010"  Part="1" 
AR Path="/5CFEE74D/5CEA0110" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0110" Ref="#PWR0106"  Part="1" 
AR Path="/5CE982AE/5CEA0110" Ref="#PWR?"  Part="1" 
F 0 "#PWR0106" H 3750 750 50  0001 C CNN
F 1 "VDD" H 3750 1050 50  0000 C CNN
F 2 "" H 3750 900 50  0001 C CNN
F 3 "" H 3750 900 50  0001 C CNN
	1    3750 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4750 7700 4750
Wire Wire Line
	3750 1000 3750 900 
Wire Wire Line
	3900 3850 3900 1600
Connection ~ 3900 1600
Wire Wire Line
	3950 1700 3950 3950
Wire Wire Line
	3950 3950 3900 3950
Connection ~ 3950 1700
Wire Wire Line
	3900 4050 4000 4050
Wire Wire Line
	4000 4050 4000 1800
Connection ~ 4000 1800
Wire Wire Line
	4050 1900 4050 4150
Wire Wire Line
	4050 4150 3900 4150
Connection ~ 4050 1900
Wire Wire Line
	3900 4250 4100 4250
Wire Wire Line
	4100 4250 4100 2000
Connection ~ 4100 2000
Wire Wire Line
	4150 2100 4150 4350
Wire Wire Line
	4150 4350 3900 4350
Connection ~ 4150 2100
Wire Wire Line
	4200 2200 4200 4450
Wire Wire Line
	4200 4450 3900 4450
Connection ~ 4200 2200
Wire Wire Line
	3900 4550 4250 4550
Wire Wire Line
	4250 4550 4250 2300
Connection ~ 4250 2300
Wire Wire Line
	2500 4150 1850 4150
Wire Wire Line
	1850 4050 2500 4050
Wire Wire Line
	2500 4350 2400 4350
Wire Wire Line
	2400 4350 2400 4450
Wire Wire Line
	2400 4450 2500 4450
Wire Wire Line
	3600 1050 3600 1000
Wire Wire Line
	3800 1000 3800 1050
Connection ~ 3750 1000
Wire Wire Line
	4000 1000 4000 1050
Connection ~ 3800 1000
Wire Wire Line
	3600 1350 3600 1400
Wire Wire Line
	3800 1350 3800 1400
Connection ~ 3800 1400
Wire Wire Line
	4000 1350 4000 1400
Connection ~ 4000 1400
$Comp
L Device:C C16
U 1 1 5CEA0112
P 4200 1200
AR Path="/5CFC7757/5CEA0112" Ref="C16"  Part="1" 
AR Path="/5CFEE74D/5CEA0112" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA0112" Ref="C56"  Part="1" 
AR Path="/5CE982AE/5CEA0112" Ref="C?"  Part="1" 
F 0 "C56" H 4225 1300 50  0000 L CNN
F 1 "C" H 4225 1100 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 4238 1050 50  0001 C CNN
F 3 "" H 4200 1200 50  0001 C CNN
	1    4200 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1400 4200 1350
Connection ~ 4200 1400
Wire Wire Line
	4200 1000 4200 1050
Connection ~ 4000 1000
Connection ~ 4200 1000
$Comp
L power:VCC #PWR011
U 1 1 5CEA0136
P 4400 900
AR Path="/5CFC7757/5CEA0136" Ref="#PWR011"  Part="1" 
AR Path="/5CFEE74D/5CEA0136" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0136" Ref="#PWR0107"  Part="1" 
AR Path="/5CE982AE/5CEA0136" Ref="#PWR?"  Part="1" 
F 0 "#PWR0107" H 4400 750 50  0001 C CNN
F 1 "VCC" H 4400 1050 50  0000 C CNN
F 2 "" H 4400 900 50  0001 C CNN
F 3 "" H 4400 900 50  0001 C CNN
	1    4400 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 900  4400 1000
Wire Wire Line
	4400 1000 4200 1000
$Comp
L power:GND #PWR012
U 1 1 5CEA0139
P 4450 1400
AR Path="/5CFC7757/5CEA0139" Ref="#PWR012"  Part="1" 
AR Path="/5CFEE74D/5CEA0139" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0139" Ref="#PWR0108"  Part="1" 
AR Path="/5CE982AE/5CEA0139" Ref="#PWR?"  Part="1" 
F 0 "#PWR0108" H 4450 1150 50  0001 C CNN
F 1 "GND" H 4450 1250 50  0000 C CNN
F 2 "" H 4450 1400 50  0001 C CNN
F 3 "" H 4450 1400 50  0001 C CNN
	1    4450 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 1400 3800 1400
Wire Wire Line
	5800 1800 4000 1800
Wire Wire Line
	5900 1700 3950 1700
Text Label 6000 1400 1    60   ~ 0
OUT0
Text Label 5900 1400 1    60   ~ 0
OUT1
Text Label 5800 1400 1    60   ~ 0
OUT2
Text Label 5700 1400 1    60   ~ 0
OUT3
Text Label 5600 1400 1    60   ~ 0
OUT4
Text Label 5500 1400 1    60   ~ 0
OUT5
Text Label 5400 1400 1    60   ~ 0
OUT6
Text Label 5300 1400 1    60   ~ 0
OUT7
Text Label 8500 900  2    60   ~ 0
OUT0
Text Label 8500 1000 2    60   ~ 0
OUT2
Text Label 8500 1100 2    60   ~ 0
OUT4
Text Label 8500 1200 2    60   ~ 0
OUT6
Text Label 8500 1300 2    60   ~ 0
OUT8
Text Label 8500 1400 2    60   ~ 0
OUT10
Text Label 8500 1500 2    60   ~ 0
OUT12
Text Label 8500 1600 2    60   ~ 0
OUT14
Text Label 9650 1550 0    60   ~ 0
OUT1
Text Label 9650 1450 0    60   ~ 0
OUT3
Text Label 9650 1350 0    60   ~ 0
OUT5
Text Label 9650 1250 0    60   ~ 0
OUT7
Text Label 9650 1150 0    60   ~ 0
OUT9
Text Label 9650 1050 0    60   ~ 0
OUT11
Text Label 9650 950  0    60   ~ 0
OUT13
Text Label 9650 850  0    60   ~ 0
OUT15
Wire Wire Line
	3900 1600 6000 1600
Wire Wire Line
	4050 1900 5700 1900
Wire Wire Line
	4100 2000 5600 2000
Wire Wire Line
	4150 2100 5500 2100
Wire Wire Line
	4200 2200 5400 2200
Wire Wire Line
	4250 2300 5300 2300
Wire Wire Line
	3750 1000 3600 1000
Wire Wire Line
	3800 1000 3750 1000
Wire Wire Line
	3800 1400 4000 1400
Wire Wire Line
	4000 1400 4200 1400
Wire Wire Line
	4200 1400 4450 1400
Wire Wire Line
	4000 1000 3800 1000
Wire Wire Line
	4200 1000 4000 1000
Wire Wire Line
	1300 3850 2500 3850
Text HLabel 9250 4750 2    50   Input ~ 0
SEROut2
Text HLabel 1300 3850 0    50   Input ~ 0
SERIn2
Text HLabel 10100 2650 2    50   Input ~ 0
OUT[32..47]
Wire Bus Line
	10100 2650 7750 2650
Entry Wire Line
	7750 1000 7850 1100
Entry Wire Line
	7750 1100 7850 1200
Entry Wire Line
	7750 1200 7850 1300
Entry Wire Line
	7750 1300 7850 1400
Entry Wire Line
	7750 1400 7850 1500
Entry Wire Line
	7750 1500 7850 1600
Entry Wire Line
	7750 900  7850 1000
Entry Wire Line
	7750 800  7850 900 
Wire Bus Line
	7750 600  9550 600 
Entry Wire Line
	9550 750  9650 850 
Entry Wire Line
	9550 850  9650 950 
Entry Wire Line
	9550 950  9650 1050
Entry Wire Line
	9550 1050 9650 1150
Entry Wire Line
	9550 1150 9650 1250
Entry Wire Line
	9550 1250 9650 1350
Entry Wire Line
	9550 1350 9650 1450
Entry Wire Line
	9550 1450 9650 1550
Text HLabel 1850 4050 0    50   Input ~ 0
SerialCLK
Text HLabel 1850 4150 0    50   Input ~ 0
nRST
Text HLabel 1850 4350 0    50   Input ~ 0
InRegLoad
Wire Wire Line
	1850 4350 2400 4350
Connection ~ 2400 4350
Text Label 8900 900  2    60   ~ 0
OUT32
Text Label 8900 1000 2    60   ~ 0
OUT34
Text Label 8900 1100 2    60   ~ 0
OUT36
Text Label 8900 1200 2    60   ~ 0
OUT38
Text Label 8900 1300 2    60   ~ 0
OUT40
Text Label 8900 1400 2    60   ~ 0
OUT42
Text Label 8900 1500 2    60   ~ 0
OUT44
Text Label 8900 1600 2    60   ~ 0
OUT46
Text Label 9950 1550 0    60   ~ 0
OUT33
Text Label 9950 1450 0    60   ~ 0
OUT35
Text Label 9950 1350 0    60   ~ 0
OUT37
Text Label 9950 1250 0    60   ~ 0
OUT39
Text Label 9950 1150 0    60   ~ 0
OUT41
Text Label 9950 1050 0    60   ~ 0
OUT43
Text Label 9950 950  0    60   ~ 0
OUT45
Text Label 9950 850  0    60   ~ 0
OUT47
Wire Wire Line
	9650 1550 10250 1550
Wire Wire Line
	9650 1450 10250 1450
Wire Wire Line
	9650 1350 10250 1350
Wire Wire Line
	9650 1250 10250 1250
Wire Wire Line
	9650 1150 10250 1150
Wire Wire Line
	9650 1050 10250 1050
Wire Wire Line
	9650 950  10250 950 
Wire Wire Line
	9650 850  10250 850 
Wire Wire Line
	7850 900  9000 900 
Wire Wire Line
	7850 1000 9000 1000
Wire Wire Line
	7850 1100 9000 1100
Wire Wire Line
	7850 1200 9000 1200
Wire Wire Line
	7850 1300 9000 1300
Wire Wire Line
	7850 1400 9000 1400
Wire Wire Line
	7850 1500 9000 1500
Wire Wire Line
	7850 1600 9000 1600
Text Label 1800 3850 0    50   ~ 0
SERIn2
Wire Wire Line
	7700 3100 9800 3100
Connection ~ 7700 4750
Text GLabel 9800 3100 2    50   Input ~ 0
CHAINOUT
Wire Wire Line
	5300 1400 5300 2300
Wire Wire Line
	5400 1400 5400 2200
Wire Wire Line
	5500 1400 5500 2100
Wire Wire Line
	5600 1400 5600 2000
Wire Wire Line
	5700 1400 5700 1900
Wire Wire Line
	5800 1400 5800 1800
Wire Wire Line
	5900 1400 5900 1700
Wire Wire Line
	6000 1400 6000 1600
$Comp
L CLRLibrary:R_Network08_10Pin RN18
U 1 1 610AD5C5
P 2900 2700
F 0 "RN18" H 2370 2654 50  0000 R CNN
F 1 "R_Network08_10Pin" H 2370 2745 50  0000 R CNN
F 2 "CLRLibrary:EXBA10P" V 3475 2700 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 2900 2700 50  0001 C CNN
	1    2900 2700
	-1   0    0    1   
$EndComp
Text HLabel 2400 2900 0    50   Input ~ 0
PULLTERM
Wire Wire Line
	3300 2900 2600 2900
Connection ~ 2600 2900
Wire Wire Line
	2600 2900 2400 2900
Wire Wire Line
	1800 2300 3300 2300
Wire Wire Line
	1800 2200 3200 2200
Wire Wire Line
	1800 1600 2600 1600
Wire Wire Line
	3300 2500 3300 2300
Connection ~ 3300 2300
Wire Wire Line
	3300 2300 4250 2300
Wire Wire Line
	1800 2100 3100 2100
Wire Wire Line
	1800 2000 2800 2000
Wire Wire Line
	1800 1900 2900 1900
Wire Wire Line
	1800 1800 3000 1800
Wire Wire Line
	1800 1700 2700 1700
Wire Wire Line
	3200 2500 3200 2200
Connection ~ 3200 2200
Wire Wire Line
	3200 2200 4200 2200
Wire Wire Line
	3100 2500 3100 2100
Connection ~ 3100 2100
Wire Wire Line
	3100 2100 4150 2100
Wire Wire Line
	2800 2500 2800 2000
Connection ~ 2800 2000
Wire Wire Line
	2800 2000 4100 2000
Wire Wire Line
	2900 2500 2900 1900
Connection ~ 2900 1900
Wire Wire Line
	2900 1900 4050 1900
Wire Wire Line
	3000 2500 3000 1800
Connection ~ 3000 1800
Wire Wire Line
	3000 1800 4000 1800
Wire Wire Line
	2700 2500 2700 1700
Connection ~ 2700 1700
Wire Wire Line
	2700 1700 3950 1700
Wire Wire Line
	2600 2500 2600 1600
Connection ~ 2600 1600
Wire Wire Line
	2600 1600 3900 1600
Wire Wire Line
	7700 3100 7700 4750
Wire Wire Line
	3900 4750 7700 4750
$Comp
L Device:C C?
U 1 1 6343367C
P 1650 1600
AR Path="/5CFC7757/6343367C" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/6343367C" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/6343367C" Ref="C24"  Part="1" 
AR Path="/5CE982AE/6343367C" Ref="C?"  Part="1" 
F 0 "C24" V 1600 1100 50  0000 L CNN
F 1 "ESD" V 1600 1350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1450 50  0001 C CNN
F 3 "" H 1650 1600 50  0001 C CNN
	1    1650 1600
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63434238
P 1650 1700
AR Path="/5CFC7757/63434238" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63434238" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63434238" Ref="C25"  Part="1" 
AR Path="/5CE982AE/63434238" Ref="C?"  Part="1" 
F 0 "C25" V 1600 1200 50  0000 L CNN
F 1 "ESD" V 1600 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1550 50  0001 C CNN
F 3 "" H 1650 1700 50  0001 C CNN
	1    1650 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63434397
P 1650 1800
AR Path="/5CFC7757/63434397" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63434397" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63434397" Ref="C26"  Part="1" 
AR Path="/5CE982AE/63434397" Ref="C?"  Part="1" 
F 0 "C26" V 1600 1300 50  0000 L CNN
F 1 "ESD" V 1600 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1650 50  0001 C CNN
F 3 "" H 1650 1800 50  0001 C CNN
	1    1650 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63434531
P 1650 1900
AR Path="/5CFC7757/63434531" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63434531" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63434531" Ref="C27"  Part="1" 
AR Path="/5CE982AE/63434531" Ref="C?"  Part="1" 
F 0 "C27" V 1600 1400 50  0000 L CNN
F 1 "ESD" V 1600 1650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1750 50  0001 C CNN
F 3 "" H 1650 1900 50  0001 C CNN
	1    1650 1900
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63434EDF
P 1650 2000
AR Path="/5CFC7757/63434EDF" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63434EDF" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63434EDF" Ref="C28"  Part="1" 
AR Path="/5CE982AE/63434EDF" Ref="C?"  Part="1" 
F 0 "C28" V 1600 1500 50  0000 L CNN
F 1 "ESD" V 1600 1750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1850 50  0001 C CNN
F 3 "" H 1650 2000 50  0001 C CNN
	1    1650 2000
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63435009
P 1650 2100
AR Path="/5CFC7757/63435009" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63435009" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63435009" Ref="C29"  Part="1" 
AR Path="/5CE982AE/63435009" Ref="C?"  Part="1" 
F 0 "C29" V 1600 1600 50  0000 L CNN
F 1 "ESD" V 1600 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 1950 50  0001 C CNN
F 3 "" H 1650 2100 50  0001 C CNN
	1    1650 2100
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63435013
P 1650 2200
AR Path="/5CFC7757/63435013" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/63435013" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63435013" Ref="C30"  Part="1" 
AR Path="/5CE982AE/63435013" Ref="C?"  Part="1" 
F 0 "C30" V 1600 1700 50  0000 L CNN
F 1 "ESD" V 1600 1950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 2050 50  0001 C CNN
F 3 "" H 1650 2200 50  0001 C CNN
	1    1650 2200
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 6343501D
P 1650 2300
AR Path="/5CFC7757/6343501D" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/6343501D" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/6343501D" Ref="C31"  Part="1" 
AR Path="/5CE982AE/6343501D" Ref="C?"  Part="1" 
F 0 "C31" V 1600 1800 50  0000 L CNN
F 1 "ESD" V 1600 2050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 2150 50  0001 C CNN
F 3 "" H 1650 2300 50  0001 C CNN
	1    1650 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 1600 1500 1700
Wire Bus Line
	7750 600  7750 2650
Wire Bus Line
	9550 600  9550 1550
Connection ~ 1500 1700
Wire Wire Line
	1500 1700 1500 1800
Connection ~ 1500 1800
Wire Wire Line
	1500 1800 1500 1900
Connection ~ 1500 1900
Wire Wire Line
	1500 1900 1500 2000
Connection ~ 1500 2000
Wire Wire Line
	1500 2000 1500 2100
Connection ~ 1500 2100
Wire Wire Line
	1500 2100 1500 2200
Connection ~ 1500 2200
Wire Wire Line
	1500 2200 1500 2300
Connection ~ 1500 2300
Wire Wire Line
	1500 2300 1500 2650
$Comp
L power:GND #PWR?
U 1 1 6343CFAC
P 1500 2650
AR Path="/5CFC7757/6343CFAC" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/6343CFAC" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/6343CFAC" Ref="#PWR019"  Part="1" 
AR Path="/5CE982AE/6343CFAC" Ref="#PWR?"  Part="1" 
F 0 "#PWR019" H 1500 2400 50  0001 C CNN
F 1 "GND" H 1500 2500 50  0000 C CNN
F 2 "" H 1500 2650 50  0001 C CNN
F 3 "" H 1500 2650 50  0001 C CNN
	1    1500 2650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
