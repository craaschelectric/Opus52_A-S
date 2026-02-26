EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SerialIOProc-rescue:74HC595-SerialIOProc-rescue U3
U 1 1 5CEA012A
P 5700 4300
AR Path="/5CFC7757/5CEA012A" Ref="U3"  Part="1" 
AR Path="/5CFEE74D/5CEA012A" Ref="U?"  Part="1" 
AR Path="/5CE81FF5/5CEA012A" Ref="U?"  Part="1" 
AR Path="/5CEA012A" Ref="U3"  Part="1" 
F 0 "U3" H 5850 4900 50  0000 C CNN
F 1 "74HC597" H 5700 3700 50  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 5700 4300 50  0001 C CNN
F 3 "" H 5700 4300 50  0001 C CNN
	1    5700 4300
	1    0    0    -1  
$EndComp
Text Label 4350 4350 0    60   ~ 0
InRegLoad
Text Label 4350 4150 0    60   ~ 0
nRST
Text Label 4350 4050 0    60   ~ 0
SerialCLK
$Comp
L SerialIOProc-rescue:74HC595-SerialIOProc-rescue U2
U 1 1 5CEA010C
P 3200 4300
AR Path="/5CFC7757/5CEA010C" Ref="U2"  Part="1" 
AR Path="/5CFEE74D/5CEA010C" Ref="U?"  Part="1" 
AR Path="/5CE81FF5/5CEA010C" Ref="U?"  Part="1" 
AR Path="/5CEA010C" Ref="U2"  Part="1" 
F 0 "U2" H 3350 4900 50  0000 C CNN
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
U 1 1 5CEA0111
P 3750 900
AR Path="/5CFC7757/5CEA0111" Ref="#PWR010"  Part="1" 
AR Path="/5CFEE74D/5CEA0111" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0111" Ref="#PWR?"  Part="1" 
F 0 "#PWR010" H 3750 750 50  0001 C CNN
F 1 "VDD" H 3750 1050 50  0000 C CNN
F 2 "" H 3750 900 50  0001 C CNN
F 3 "" H 3750 900 50  0001 C CNN
	1    3750 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4750 7700 4750
Wire Wire Line
	2600 2300 2600 1400
Wire Wire Line
	2700 1400 2700 2200
Wire Wire Line
	2800 2100 2800 1400
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
	6450 3950 6400 3950
Wire Wire Line
	6400 4050 6500 4050
Wire Wire Line
	6550 4150 6400 4150
Wire Wire Line
	3900 4750 4750 4750
Wire Wire Line
	4750 4750 4750 3850
Wire Wire Line
	4750 3850 5000 3850
Wire Wire Line
	4350 4150 5000 4150
Wire Wire Line
	2500 4150 1850 4150
Wire Wire Line
	1850 4050 2500 4050
Wire Wire Line
	4350 4050 5000 4050
Wire Wire Line
	5000 4350 4350 4350
Wire Wire Line
	4350 4350 4350 4450
Wire Wire Line
	2500 4350 2400 4350
Wire Wire Line
	2400 4350 2400 4450
Wire Wire Line
	2400 4450 2500 4450
$Comp
L Device:C C15
U 1 1 5CEA0135
P 4000 1200
AR Path="/5CFC7757/5CEA0135" Ref="C15"  Part="1" 
AR Path="/5CFEE74D/5CEA0135" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA0135" Ref="C?"  Part="1" 
F 0 "C15" H 4025 1300 50  0000 L CNN
F 1 "C" H 4025 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4038 1050 50  0001 C CNN
F 3 "" H 4000 1200 50  0001 C CNN
	1    4000 1200
	1    0    0    -1  
$EndComp
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
U 1 1 5CEA0113
P 4200 1200
AR Path="/5CFC7757/5CEA0113" Ref="C16"  Part="1" 
AR Path="/5CFEE74D/5CEA0113" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA0113" Ref="C?"  Part="1" 
F 0 "C16" H 4225 1300 50  0000 L CNN
F 1 "C" H 4225 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4238 1050 50  0001 C CNN
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
U 1 1 5CEA0137
P 4400 900
AR Path="/5CFC7757/5CEA0137" Ref="#PWR011"  Part="1" 
AR Path="/5CFEE74D/5CEA0137" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0137" Ref="#PWR?"  Part="1" 
F 0 "#PWR011" H 4400 750 50  0001 C CNN
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
U 1 1 5CFFCB71
P 4450 1400
AR Path="/5CFC7757/5CFFCB71" Ref="#PWR012"  Part="1" 
AR Path="/5CFEE74D/5CFFCB71" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CFFCB71" Ref="#PWR?"  Part="1" 
F 0 "#PWR012" H 4450 1150 50  0001 C CNN
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
Text Label 5200 1400 1    60   ~ 0
OUT8
Text Label 5100 1400 1    60   ~ 0
OUT9
Text Label 5000 1400 1    60   ~ 0
OUT10
Text Label 4900 1400 1    60   ~ 0
OUT11
Text Label 9700 4250 0    60   ~ 0
OUT12
Text Label 9700 4350 0    60   ~ 0
OUT13
Text Label 9700 4450 0    60   ~ 0
OUT14
Text Label 9700 4550 0    60   ~ 0
OUT15
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
	6400 3850 6400 2400
Wire Wire Line
	6400 2400 5200 2400
Wire Wire Line
	6450 3950 6450 2500
Wire Wire Line
	6450 2500 5100 2500
Wire Wire Line
	6500 4050 6500 2600
Wire Wire Line
	6500 2600 6300 2600
Wire Wire Line
	6550 2700 6550 4150
Wire Wire Line
	2600 2300 4250 2300
Wire Wire Line
	2700 2200 4200 2200
Wire Wire Line
	2800 2100 4150 2100
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
	4900 2700 6550 2700
Wire Wire Line
	4350 4450 5000 4450
Wire Wire Line
	1300 3850 2500 3850
Text HLabel 9250 4750 2    50   Input ~ 0
SEROut1
Text HLabel 1300 3850 0    50   Input ~ 0
SERIn1
Text HLabel 10100 2650 2    50   Input ~ 0
OUT[16..31]
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
Text HLabel 1400 1000 0    50   Input ~ 0
PULLTERM
Wire Wire Line
	2050 650  2050 1000
Connection ~ 2050 1000
Wire Wire Line
	2050 1000 1400 1000
$Comp
L Device:C C20
U 1 1 5CEA014B
P 8850 3900
AR Path="/5CFC7757/5CEA014B" Ref="C20"  Part="1" 
AR Path="/5CFEE74D/5CEA014B" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA014B" Ref="C?"  Part="1" 
F 0 "C20" V 8850 3550 50  0000 L CNN
F 1 "1nF or ESD" V 8850 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8888 3750 50  0001 C CNN
F 3 "" H 8850 3900 50  0001 C CNN
	1    8850 3900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C19
U 1 1 5CEA014C
P 8750 3900
AR Path="/5CFC7757/5CEA014C" Ref="C19"  Part="1" 
AR Path="/5CFEE74D/5CEA014C" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA014C" Ref="C?"  Part="1" 
F 0 "C19" V 8750 3550 50  0000 L CNN
F 1 "1nF or ESD" V 8750 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8788 3750 50  0001 C CNN
F 3 "" H 8750 3900 50  0001 C CNN
	1    8750 3900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C18
U 1 1 5CEA0129
P 8650 3900
AR Path="/5CFC7757/5CEA0129" Ref="C18"  Part="1" 
AR Path="/5CFEE74D/5CEA0129" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CEA0129" Ref="C?"  Part="1" 
F 0 "C18" V 8650 3550 50  0000 L CNN
F 1 "1nF or ESD" V 8650 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8688 3750 50  0001 C CNN
F 3 "" H 8650 3900 50  0001 C CNN
	1    8650 3900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C17
U 1 1 5CFFCB86
P 8550 3900
AR Path="/5CFC7757/5CFFCB86" Ref="C17"  Part="1" 
AR Path="/5CFEE74D/5CFFCB86" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CFFCB86" Ref="C?"  Part="1" 
F 0 "C17" V 8550 3550 50  0000 L CNN
F 1 "1nF or ESD" V 8550 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8588 3750 50  0001 C CNN
F 3 "" H 8550 3900 50  0001 C CNN
	1    8550 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5CEA0150
P 8250 3750
AR Path="/5CFC7757/5CEA0150" Ref="#PWR013"  Part="1" 
AR Path="/5CFEE74D/5CEA0150" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5CEA0150" Ref="#PWR?"  Part="1" 
F 0 "#PWR013" H 8250 3500 50  0001 C CNN
F 1 "GND" H 8250 3600 50  0000 C CNN
F 2 "" H 8250 3750 50  0001 C CNN
F 3 "" H 8250 3750 50  0001 C CNN
	1    8250 3750
	0    1    1    0   
$EndComp
Connection ~ 8750 3750
Wire Wire Line
	8750 3750 8850 3750
Connection ~ 8650 3750
Wire Wire Line
	8650 3750 8750 3750
Connection ~ 8550 3750
Wire Wire Line
	8550 3750 8650 3750
Wire Wire Line
	8850 4050 8850 4250
Connection ~ 8850 4250
Wire Wire Line
	8750 4050 8750 4350
Connection ~ 8750 4350
Wire Wire Line
	8650 4050 8650 4450
Connection ~ 8650 4450
Wire Wire Line
	8550 4050 8550 4550
Connection ~ 8550 4550
Wire Wire Line
	8250 3750 8550 3750
Text HLabel 1850 4050 0    50   Input ~ 0
SerialCLK
Text HLabel 1850 4150 0    50   Input ~ 0
nRST
Text HLabel 1850 4350 0    50   Input ~ 0
InRegLoad
Wire Wire Line
	1850 4350 2400 4350
Connection ~ 2400 4350
Wire Wire Line
	2400 4450 2400 5100
Wire Wire Line
	2400 5100 4350 5100
Wire Wire Line
	4350 5100 4350 4450
Connection ~ 2400 4450
Connection ~ 4350 4450
Text Label 8900 900  2    60   ~ 0
OUT16
Text Label 8900 1000 2    60   ~ 0
OUT18
Text Label 8900 1100 2    60   ~ 0
OUT20
Text Label 8900 1200 2    60   ~ 0
OUT22
Text Label 8900 1300 2    60   ~ 0
OUT24
Text Label 8900 1400 2    60   ~ 0
OUT26
Text Label 8900 1500 2    60   ~ 0
OUT28
Text Label 8900 1600 2    60   ~ 0
OUT30
Text Label 9950 1550 0    60   ~ 0
OUT17
Text Label 9950 1450 0    60   ~ 0
OUT19
Text Label 9950 1350 0    60   ~ 0
OUT21
Text Label 9950 1250 0    60   ~ 0
OUT23
Text Label 9950 1150 0    60   ~ 0
OUT25
Text Label 9950 1050 0    60   ~ 0
OUT27
Text Label 9950 950  0    60   ~ 0
OUT29
Text Label 9950 850  0    60   ~ 0
OUT31
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
Text Label 1700 3850 0    50   ~ 0
SERIn1
Text Label 7650 4750 0    50   ~ 0
SEROut1
$Comp
L Device:C C14
U 1 1 5CE4B454
P 3800 1200
AR Path="/5CFC7757/5CE4B454" Ref="C14"  Part="1" 
AR Path="/5CFEE74D/5CE4B454" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5CE4B454" Ref="C?"  Part="1" 
F 0 "C14" H 3825 1300 50  0000 L CNN
F 1 "C" H 3825 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3838 1050 50  0001 C CNN
F 3 "" H 3800 1200 50  0001 C CNN
	1    3800 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5D11710B
P 7700 3500
F 0 "R7" H 7770 3546 50  0000 L CNN
F 1 "DNP" H 7770 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7630 3500 50  0001 C CNN
F 3 "~" H 7700 3500 50  0001 C CNN
	1    7700 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5D23FF01
P 4750 3600
F 0 "R6" H 4820 3646 50  0000 L CNN
F 1 "DNP" H 4820 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4680 3600 50  0001 C CNN
F 3 "~" H 4750 3600 50  0001 C CNN
	1    4750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3850 4750 3750
Connection ~ 4750 3850
Wire Wire Line
	4750 3450 4750 3100
Wire Wire Line
	4750 3100 7700 3100
Wire Wire Line
	7700 3350 7700 3100
Connection ~ 7700 3100
Wire Wire Line
	7700 3100 9800 3100
Wire Wire Line
	7700 3650 7700 4750
Connection ~ 7700 4750
Wire Wire Line
	7700 4750 6400 4750
Text GLabel 9800 3100 2    50   Input ~ 0
CHAINOUT
Wire Wire Line
	6250 650  2050 650 
Wire Wire Line
	6400 4550 6950 4550
Wire Wire Line
	6400 4450 6850 4450
Wire Wire Line
	6400 4350 6750 4350
Wire Wire Line
	6950 1050 6950 4550
Connection ~ 6950 4550
Wire Wire Line
	6950 4550 8550 4550
Wire Wire Line
	6850 1050 6850 4450
Connection ~ 6850 4450
Wire Wire Line
	6850 4450 8650 4450
Wire Wire Line
	6750 1050 6750 4350
Connection ~ 6750 4350
Wire Wire Line
	6750 4350 8750 4350
Wire Wire Line
	6550 2700 6550 1050
Connection ~ 6550 2700
Wire Wire Line
	6500 1150 6450 1150
Wire Wire Line
	6450 1150 6450 1050
Wire Wire Line
	6450 2500 6450 1200
Wire Wire Line
	6450 1200 6350 1200
Wire Wire Line
	6350 1200 6350 1050
Connection ~ 6450 2500
Wire Wire Line
	6400 1300 6250 1300
Wire Wire Line
	6250 1300 6250 1050
Connection ~ 2600 1000
$Comp
L CLRLibrary:R_Network08_10Pin RN1
U 1 1 610FC7FB
P 3000 1200
F 0 "RN1" H 3430 1246 50  0000 L CNN
F 1 "R_Network08_10Pin" H 3430 1155 50  0000 L CNN
F 2 "CLRLibrary:EXBA10P" V 3575 1200 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 3000 1200 50  0001 C CNN
	1    3000 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1000 3300 1000
Wire Wire Line
	2050 1000 2600 1000
Wire Wire Line
	6400 1300 6400 2400
Connection ~ 6400 2400
Wire Wire Line
	3100 1400 3100 2000
Wire Wire Line
	3100 2000 4100 2000
Wire Wire Line
	3000 1400 3000 1900
Wire Wire Line
	3000 1900 4050 1900
Wire Wire Line
	2900 1400 2900 1800
Wire Wire Line
	2900 1800 4000 1800
Wire Wire Line
	3200 1400 3200 1700
Wire Wire Line
	3200 1700 3950 1700
Wire Wire Line
	3300 1400 3300 1600
Wire Wire Line
	3300 1600 3900 1600
Wire Wire Line
	6950 650  7100 650 
Connection ~ 6250 650 
Wire Wire Line
	6400 4250 6650 4250
Connection ~ 6950 650 
Wire Wire Line
	6250 650  6950 650 
$Comp
L CLRLibrary:R_Network08_10Pin RN3
U 1 1 6110A330
P 6550 850
F 0 "RN3" H 6020 896 50  0000 R CNN
F 1 "R_Network08_10Pin" H 6020 805 50  0000 R CNN
F 2 "CLRLibrary:EXBA10P" V 7125 850 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 6550 850 50  0001 C CNN
	1    6550 850 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6500 1150 6500 2100
Wire Wire Line
	6500 2100 6650 2100
Wire Wire Line
	6650 2100 6650 4250
Connection ~ 6650 4250
Wire Wire Line
	6650 4250 8850 4250
Wire Wire Line
	6650 1050 6650 1800
Wire Wire Line
	6650 1800 6300 1800
Wire Wire Line
	6300 1800 6300 2600
Connection ~ 6300 2600
Wire Wire Line
	6300 2600 5000 2600
Wire Wire Line
	8850 4250 9700 4250
Wire Wire Line
	8750 4350 9700 4350
Wire Wire Line
	8650 4450 9700 4450
Wire Wire Line
	8550 4550 9700 4550
Wire Wire Line
	4900 1400 4900 2700
Wire Wire Line
	5000 1400 5000 2600
Wire Wire Line
	5100 1400 5100 2500
Wire Wire Line
	5200 1400 5200 2400
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
L Device:C C1
U 1 1 63335283
P 1750 1600
AR Path="/5CFC7757/63335283" Ref="C1"  Part="1" 
AR Path="/5CFEE74D/63335283" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63335283" Ref="C?"  Part="1" 
F 0 "C1" V 1750 1250 50  0000 L CNN
F 1 "1nF or ESD" V 1750 750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1450 50  0001 C CNN
F 3 "" H 1750 1600 50  0001 C CNN
	1    1750 1600
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 63335489
P 1750 1700
AR Path="/5CFC7757/63335489" Ref="C2"  Part="1" 
AR Path="/5CFEE74D/63335489" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63335489" Ref="C?"  Part="1" 
F 0 "C2" V 1750 1350 50  0000 L CNN
F 1 "1nF or ESD" V 1750 850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1550 50  0001 C CNN
F 3 "" H 1750 1700 50  0001 C CNN
	1    1750 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 63335493
P 1750 1800
AR Path="/5CFC7757/63335493" Ref="C3"  Part="1" 
AR Path="/5CFEE74D/63335493" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63335493" Ref="C?"  Part="1" 
F 0 "C3" V 1750 1450 50  0000 L CNN
F 1 "1nF or ESD" V 1750 950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1650 50  0001 C CNN
F 3 "" H 1750 1800 50  0001 C CNN
	1    1750 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 6333549D
P 1750 1900
AR Path="/5CFC7757/6333549D" Ref="C4"  Part="1" 
AR Path="/5CFEE74D/6333549D" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/6333549D" Ref="C?"  Part="1" 
F 0 "C4" V 1750 1550 50  0000 L CNN
F 1 "1nF or ESD" V 1750 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1750 50  0001 C CNN
F 3 "" H 1750 1900 50  0001 C CNN
	1    1750 1900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 633354A7
P 1600 2300
AR Path="/5CFC7757/633354A7" Ref="#PWR017"  Part="1" 
AR Path="/5CFEE74D/633354A7" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/633354A7" Ref="#PWR?"  Part="1" 
F 0 "#PWR017" H 1600 2050 50  0001 C CNN
F 1 "GND" H 1600 2150 50  0000 C CNN
F 2 "" H 1600 2300 50  0001 C CNN
F 3 "" H 1600 2300 50  0001 C CNN
	1    1600 2300
	1    0    0    -1  
$EndComp
Connection ~ 1600 1700
Wire Wire Line
	1600 1700 1600 1600
Connection ~ 1600 1800
Wire Wire Line
	1600 1800 1600 1700
Connection ~ 1600 1900
Wire Wire Line
	1600 1900 1600 1800
Wire Wire Line
	1600 2200 1600 2100
$Comp
L Device:C C5
U 1 1 63340F93
P 1750 2000
AR Path="/5CFC7757/63340F93" Ref="C5"  Part="1" 
AR Path="/5CFEE74D/63340F93" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63340F93" Ref="C?"  Part="1" 
F 0 "C5" V 1750 1650 50  0000 L CNN
F 1 "1nF or ESD" V 1750 1150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1850 50  0001 C CNN
F 3 "" H 1750 2000 50  0001 C CNN
	1    1750 2000
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 633411ED
P 1750 2100
AR Path="/5CFC7757/633411ED" Ref="C6"  Part="1" 
AR Path="/5CFEE74D/633411ED" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/633411ED" Ref="C?"  Part="1" 
F 0 "C6" V 1750 1750 50  0000 L CNN
F 1 "1nF or ESD" V 1750 1250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 1950 50  0001 C CNN
F 3 "" H 1750 2100 50  0001 C CNN
	1    1750 2100
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 633411F7
P 1750 2200
AR Path="/5CFC7757/633411F7" Ref="C7"  Part="1" 
AR Path="/5CFEE74D/633411F7" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/633411F7" Ref="C?"  Part="1" 
F 0 "C7" V 1750 1850 50  0000 L CNN
F 1 "1nF or ESD" V 1750 1350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 2050 50  0001 C CNN
F 3 "" H 1750 2200 50  0001 C CNN
	1    1750 2200
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 63341201
P 1750 2300
AR Path="/5CFC7757/63341201" Ref="C8"  Part="1" 
AR Path="/5CFEE74D/63341201" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/63341201" Ref="C?"  Part="1" 
F 0 "C8" V 1750 1950 50  0000 L CNN
F 1 "1nF or ESD" V 1750 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 2150 50  0001 C CNN
F 3 "" H 1750 2300 50  0001 C CNN
	1    1750 2300
	0    1    1    0   
$EndComp
Connection ~ 1600 2000
Wire Wire Line
	1600 2000 1600 1900
Connection ~ 1600 2100
Wire Wire Line
	1600 2100 1600 2000
Connection ~ 1600 2200
Wire Wire Line
	1600 2200 1600 2300
Connection ~ 1600 2300
Wire Wire Line
	1900 1600 3300 1600
Connection ~ 3300 1600
Wire Wire Line
	1900 1700 3200 1700
Connection ~ 3200 1700
Wire Wire Line
	1900 1800 2900 1800
Connection ~ 2900 1800
Wire Wire Line
	1900 1900 3000 1900
Connection ~ 3000 1900
Wire Wire Line
	1900 2000 3100 2000
Connection ~ 3100 2000
Wire Wire Line
	1900 2100 2800 2100
Connection ~ 2800 2100
Wire Wire Line
	1900 2200 2700 2200
Connection ~ 2700 2200
Wire Wire Line
	1900 2300 2600 2300
Connection ~ 2600 2300
Wire Bus Line
	7750 600  7750 2650
Wire Bus Line
	9550 600  9550 1550
$EndSCHEMATC
