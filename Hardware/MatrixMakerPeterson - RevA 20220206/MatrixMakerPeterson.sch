EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 1 2
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
L 156adapter-rescue:Conn_01x12-conn J1
U 1 1 5A3EB6EB
P 4000 2300
F 0 "J1" H 4000 2900 50  0000 C CNN
F 1 "Conn_01x12" H 4000 1600 50  0000 C CNN
F 2 "CLRConnector:KK156-12" H 4000 2300 50  0001 C CNN
F 3 "" H 4000 2300 50  0001 C CNN
	1    4000 2300
	-1   0    0    -1  
$EndComp
Text GLabel 4200 1800 2    60   Input ~ 0
D0
Text GLabel 4200 1900 2    60   Input ~ 0
D1
Text GLabel 4200 2000 2    60   Input ~ 0
D2
Text GLabel 4200 2100 2    60   Input ~ 0
D3
Text GLabel 4200 2200 2    60   Input ~ 0
D4
Text GLabel 4200 2300 2    60   Input ~ 0
D5
Text GLabel 4200 2400 2    60   Input ~ 0
D6
Text GLabel 4200 2500 2    60   Input ~ 0
D7
Text GLabel 4200 2700 2    60   Input ~ 0
D9
Text GLabel 4200 2800 2    60   Input ~ 0
D10
Text GLabel 4200 2900 2    60   Input ~ 0
D11
Text GLabel 4200 2600 2    60   Input ~ 0
D8
Text GLabel 6800 3750 0    60   Input ~ 0
D8
Text GLabel 6800 3350 0    60   Input ~ 0
D0
Text GLabel 7300 3350 2    60   Input ~ 0
D1
Text GLabel 6800 3450 0    60   Input ~ 0
D2
Text GLabel 7300 3450 2    60   Input ~ 0
D3
Text GLabel 6800 3550 0    60   Input ~ 0
D4
Text GLabel 7300 3550 2    60   Input ~ 0
D5
Text GLabel 6800 3650 0    60   Input ~ 0
D6
Text GLabel 7300 3650 2    60   Input ~ 0
D7
Text GLabel 6800 3850 0    60   Input ~ 0
D10
Text GLabel 7300 3750 2    60   Input ~ 0
D9
Text GLabel 7300 3850 2    60   Input ~ 0
D11
$Sheet
S 7150 1350 1400 450 
U 6018273B
F0 "Mounting" 50
F1 "Mounting.sch" 50
$EndSheet
Text GLabel 2000 1800 2    60   Input ~ 0
D0
Text GLabel 2000 2000 2    60   Input ~ 0
D1
Text GLabel 2000 2350 2    60   Input ~ 0
D2
Text GLabel 2000 2550 2    60   Input ~ 0
D3
Text GLabel 2000 2900 2    60   Input ~ 0
D4
Text GLabel 2000 3100 2    60   Input ~ 0
D5
Text GLabel 2000 3450 2    60   Input ~ 0
D6
Text GLabel 2000 3650 2    60   Input ~ 0
D7
Text GLabel 2000 4200 2    60   Input ~ 0
D9
Text GLabel 2000 4600 2    60   Input ~ 0
D10
Text GLabel 2000 4800 2    60   Input ~ 0
D11
Text GLabel 2000 4000 2    60   Input ~ 0
D8
Wire Wire Line
	7150 10400 7150 10350
$Comp
L Connector_Generic:Conn_01x05 J3
U 1 1 5F10A059
P 10800 2100
F 0 "J3" H 10880 2142 50  0000 L CNN
F 1 "Conn_01x05" H 10880 2051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 10800 2100 50  0001 C CNN
F 3 "~" H 10800 2100 50  0001 C CNN
	1    10800 2100
	-1   0    0    -1  
$EndComp
Text Label 10550 3000 0    50   ~ 0
RA0
Text Label 10550 3100 0    50   ~ 0
RA1
Text Label 10550 3200 0    50   ~ 0
RA2
Text Label 10550 3300 0    50   ~ 0
RA3
Text Label 10550 3400 0    50   ~ 0
RA4
Text Label 10550 3500 0    50   ~ 0
RA5
Text Label 10550 3600 0    50   ~ 0
RA6
Text Label 10550 3700 0    50   ~ 0
RA7
Wire Wire Line
	10800 3000 10200 3000
Wire Wire Line
	10800 3100 10200 3100
Wire Wire Line
	10800 3200 10200 3200
Wire Wire Line
	10800 3300 10200 3300
Wire Wire Line
	10800 3400 10200 3400
Wire Wire Line
	10800 3500 10200 3500
Wire Wire Line
	10800 3700 10200 3700
Wire Wire Line
	10800 3600 10200 3600
Text Label 11900 3450 0    50   ~ 0
RC0
Text Label 11900 3550 0    50   ~ 0
RC1
Text Label 11900 3650 0    50   ~ 0
RC2
Text Label 11900 3850 0    50   ~ 0
RC4
Text Label 11900 3950 0    50   ~ 0
RC5
Text Label 11900 4050 0    50   ~ 0
RC6
Text Label 11900 4150 0    50   ~ 0
RC7
Wire Wire Line
	11800 3550 12200 3550
Text Label 11900 3750 0    50   ~ 0
RC3
Wire Wire Line
	11800 3450 12200 3450
Wire Wire Line
	11800 3750 12200 3750
Wire Wire Line
	11800 3650 12200 3650
Wire Wire Line
	11800 4050 12200 4050
Wire Wire Line
	11800 4150 12200 4150
Wire Wire Line
	11800 3850 12200 3850
Wire Wire Line
	11800 3950 12200 3950
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J9
U 1 1 5F279C05
P 11550 6500
F 0 "J9" H 11600 6917 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 11600 6826 50  0000 C CNN
F 2 "CLRLibrary:RibbonCableSocket_10_OddEven" H 11550 6500 50  0001 C CNN
F 3 "~" H 11550 6500 50  0001 C CNN
	1    11550 6500
	1    0    0    -1  
$EndComp
Text GLabel 10200 3000 0    60   Input ~ 0
D0
Text GLabel 10200 3100 0    60   Input ~ 0
D1
Text GLabel 10200 3200 0    60   Input ~ 0
D2
Text GLabel 10200 3300 0    60   Input ~ 0
D3
Text GLabel 10200 3400 0    60   Input ~ 0
D4
Text GLabel 10200 3500 0    60   Input ~ 0
D5
Text GLabel 10200 3600 0    60   Input ~ 0
D6
Text GLabel 10200 3700 0    60   Input ~ 0
D7
Text GLabel 6800 3950 0    60   Input ~ 0
C0
Text GLabel 6800 4050 0    60   Input ~ 0
C2
Text GLabel 7300 3950 2    60   Input ~ 0
C1
Text GLabel 6800 4150 0    60   Input ~ 0
C4
Text GLabel 7300 4050 2    60   Input ~ 0
C3
Wire Wire Line
	1500 1650 1500 1800
$Comp
L CLRLibrary:BAS21PG D1
U 1 1 60880236
P 1850 1700
F 0 "D1" H 1950 1825 50  0000 C CNN
F 1 "BAS21PG" H 1950 1734 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 1700 50  0001 C CNN
F 3 "" H 1850 1700 50  0001 C CNN
	1    1850 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 2000 1500 2350
Wire Wire Line
	1500 1800 1500 2000
Connection ~ 1500 1800
Connection ~ 1500 2000
$Comp
L CLRLibrary:BAS21PG D2
U 1 1 60885D52
P 1850 2250
F 0 "D2" H 1950 2375 50  0000 C CNN
F 1 "BAS21PG" H 1950 2284 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 2250 50  0001 C CNN
F 3 "" H 1850 2250 50  0001 C CNN
	1    1850 2250
	-1   0    0    -1  
$EndComp
$Comp
L CLRLibrary:BAS21PG D3
U 1 1 608862B4
P 1850 2800
F 0 "D3" H 1950 2925 50  0000 C CNN
F 1 "BAS21PG" H 1950 2834 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 2800 50  0001 C CNN
F 3 "" H 1850 2800 50  0001 C CNN
	1    1850 2800
	-1   0    0    -1  
$EndComp
$Comp
L CLRLibrary:BAS21PG D4
U 1 1 60886A9D
P 1850 3350
F 0 "D4" H 1950 3475 50  0000 C CNN
F 1 "BAS21PG" H 1950 3384 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 3350 50  0001 C CNN
F 3 "" H 1850 3350 50  0001 C CNN
	1    1850 3350
	-1   0    0    -1  
$EndComp
$Comp
L CLRLibrary:BAS21PG D5
U 1 1 60887243
P 1850 3900
F 0 "D5" H 1950 4025 50  0000 C CNN
F 1 "BAS21PG" H 1950 3934 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 3900 50  0001 C CNN
F 3 "" H 1850 3900 50  0001 C CNN
	1    1850 3900
	-1   0    0    -1  
$EndComp
$Comp
L CLRLibrary:BAS21PG D6
U 1 1 60887975
P 1850 4500
F 0 "D6" H 1950 4625 50  0000 C CNN
F 1 "BAS21PG" H 1950 4534 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 1850 4500 50  0001 C CNN
F 3 "" H 1850 4500 50  0001 C CNN
	1    1850 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 2350 1500 2550
Connection ~ 1500 2350
Connection ~ 1500 2550
Wire Wire Line
	1500 2550 1500 2900
Connection ~ 1500 2900
Wire Wire Line
	1500 2900 1500 3100
Connection ~ 1500 3100
Wire Wire Line
	1500 3100 1500 3450
Connection ~ 1500 3450
Wire Wire Line
	1500 3450 1500 3650
Connection ~ 1500 3650
Wire Wire Line
	1500 3650 1500 4000
Connection ~ 1500 4000
Wire Wire Line
	1500 4000 1500 4200
Connection ~ 1500 4200
Wire Wire Line
	1500 4200 1500 4600
Connection ~ 1500 4600
Wire Wire Line
	1500 4600 1500 4800
$Comp
L Connector_Generic:Conn_01x06 J4
U 1 1 608A7FC9
P 2950 3500
F 0 "J4" H 2868 3917 50  0000 C CNN
F 1 "Conn_01x06" H 2868 3826 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2950 3500 50  0001 C CNN
F 3 "~" H 2950 3500 50  0001 C CNN
	1    2950 3500
	-1   0    0    -1  
$EndComp
Text GLabel 3150 3300 2    60   Input ~ 0
C0
Text GLabel 3150 3400 2    60   Input ~ 0
C1
Text GLabel 3150 3500 2    60   Input ~ 0
C2
Text GLabel 3150 3600 2    60   Input ~ 0
C3
Text GLabel 3150 3700 2    60   Input ~ 0
C4
$Comp
L Connector_Generic:Conn_01x06 J5
U 1 1 61FF5223
P 2950 4350
F 0 "J5" H 2868 4767 50  0000 C CNN
F 1 "Conn_01x06" H 2868 4676 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2950 4350 50  0001 C CNN
F 3 "~" H 2950 4350 50  0001 C CNN
	1    2950 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 4800 1500 5300
Wire Wire Line
	1500 5300 3150 5300
Wire Wire Line
	3150 5300 3150 4650
Connection ~ 1500 4800
Connection ~ 3150 4250
Wire Wire Line
	3150 4250 3150 4150
Connection ~ 3150 4350
Wire Wire Line
	3150 4350 3150 4250
Connection ~ 3150 4450
Wire Wire Line
	3150 4450 3150 4350
Connection ~ 3150 4550
Wire Wire Line
	3150 4550 3150 4450
Connection ~ 3150 4650
Wire Wire Line
	3150 4650 3150 4550
$Comp
L CLRLibrary:R_Network08_10Pin RN1
U 1 1 61FFA258
P 5150 2200
F 0 "RN1" V 4483 2200 50  0000 C CNN
F 1 "R_Network08_10Pin" V 4574 2200 50  0000 C CNN
F 2 "CLRLibrary:EXBA10P" V 5725 2200 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 5150 2200 50  0001 C CNN
	1    5150 2200
	0    -1   1    0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 61FFE544
P 4950 2500
AR Path="/5CFC7757/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/61FFE544" Ref="#PWR?"  Part="1" 
AR Path="/61FFE544" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 4950 2350 50  0001 C CNN
F 1 "VDD" H 4950 2650 50  0000 C CNN
F 2 "" H 4950 2500 50  0001 C CNN
F 3 "" H 4950 2500 50  0001 C CNN
	1    4950 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 61FFED93
P 4950 1800
AR Path="/5CFC7757/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/61FFED93" Ref="#PWR?"  Part="1" 
AR Path="/61FFED93" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 4950 1650 50  0001 C CNN
F 1 "VDD" H 4950 1950 50  0000 C CNN
F 2 "" H 4950 1800 50  0001 C CNN
F 3 "" H 4950 1800 50  0001 C CNN
	1    4950 1800
	0    -1   -1   0   
$EndComp
Text GLabel 5350 1800 2    60   Input ~ 0
D0
Text GLabel 5350 2000 2    60   Input ~ 0
D1
Text GLabel 5350 2200 2    60   Input ~ 0
D2
Text GLabel 5350 2400 2    60   Input ~ 0
D3
Text GLabel 5350 1900 2    60   Input ~ 0
D4
Text GLabel 5350 2300 2    60   Input ~ 0
D5
Text GLabel 5350 2100 2    60   Input ~ 0
D6
Text GLabel 5350 2500 2    60   Input ~ 0
D7
$Comp
L CLRLibrary:R_Network08_10Pin RN2
U 1 1 62001578
P 5150 3400
F 0 "RN2" V 4483 3400 50  0000 C CNN
F 1 "R_Network08_10Pin" V 4574 3400 50  0000 C CNN
F 2 "CLRLibrary:EXBA10P" V 5725 3400 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 5150 3400 50  0001 C CNN
	1    5150 3400
	0    -1   1    0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 62001956
P 4950 3700
AR Path="/5CFC7757/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/62001956" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/62001956" Ref="#PWR?"  Part="1" 
AR Path="/62001956" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 4950 3550 50  0001 C CNN
F 1 "VDD" H 4950 3850 50  0000 C CNN
F 2 "" H 4950 3700 50  0001 C CNN
F 3 "" H 4950 3700 50  0001 C CNN
	1    4950 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 62001960
P 4950 3000
AR Path="/5CFC7757/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/62001960" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/62001960" Ref="#PWR?"  Part="1" 
AR Path="/62001960" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 4950 2850 50  0001 C CNN
F 1 "VDD" H 4950 3150 50  0000 C CNN
F 2 "" H 4950 3000 50  0001 C CNN
F 3 "" H 4950 3000 50  0001 C CNN
	1    4950 3000
	0    -1   -1   0   
$EndComp
Text GLabel 5350 3500 2    60   Input ~ 0
D9
Text GLabel 5350 3300 2    60   Input ~ 0
D10
Text GLabel 5350 3700 2    60   Input ~ 0
D11
Text GLabel 5350 3100 2    60   Input ~ 0
D8
$Comp
L 156adapter-rescue:Conn_02x08_Odd_Even-conn J6
U 1 1 6200879A
P 4300 4500
F 0 "J6" H 4350 5017 50  0000 C CNN
F 1 "Conn_02x08_Odd_Even-conn" H 4350 4926 50  0000 C CNN
F 2 "CLRLibrary:MicromaTch-16" H 4300 4500 50  0001 C CNN
F 3 "" H 4300 4500 50  0001 C CNN
	1    4300 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D32
U 1 1 5E9B74C4
P 12700 4550
F 0 "D32" H 12691 4766 50  0000 C CNN
F 1 "LED" H 12691 4675 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 12700 4550 50  0001 C CNN
F 3 "~" H 12700 4550 50  0001 C CNN
	1    12700 4550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R41
U 1 1 5E9B74CA
P 12700 4850
F 0 "R41" V 12800 4800 50  0000 L CNN
F 1 "3K3" V 12700 4750 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 12630 4850 50  0001 C CNN
F 3 "~" H 12700 4850 50  0001 C CNN
	1    12700 4850
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5D07AF17
P 10900 5400
AR Path="/5CFC7757/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5D07AF17" Ref="#PWR?"  Part="1" 
AR Path="/5D07AF17" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 10900 5250 50  0001 C CNN
F 1 "VDD" H 10900 5550 50  0000 C CNN
F 2 "" H 10900 5400 50  0001 C CNN
F 3 "" H 10900 5400 50  0001 C CNN
	1    10900 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 5500 10900 5400
$Comp
L Device:C C?
U 1 1 5D07AF05
P 10750 5700
AR Path="/5CFC7757/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5CE982AE/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5D01CD70/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5D08CCAD/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5D117FD0/5D07AF05" Ref="C?"  Part="1" 
AR Path="/5D07AF05" Ref="C2"  Part="1" 
F 0 "C2" H 10775 5800 50  0000 L CNN
F 1 "302010138" H 10775 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10788 5550 50  0001 C CNN
F 3 "" H 10750 5700 50  0001 C CNN
	1    10750 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 5550 10750 5500
Wire Wire Line
	10950 5500 10950 5550
Connection ~ 10900 5500
Wire Wire Line
	11150 5500 11150 5550
Connection ~ 10950 5500
Wire Wire Line
	10750 5850 10750 5900
Wire Wire Line
	10950 5850 10950 5900
Connection ~ 10950 5900
Wire Wire Line
	11150 5850 11150 5900
Connection ~ 11150 5900
$Comp
L Device:C C?
U 1 1 5D07AF19
P 11350 5700
AR Path="/5CFC7757/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5CFEE74D/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5CE81FF5/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5CE982AE/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5D01CD70/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5D08CCAD/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5D117FD0/5D07AF19" Ref="C?"  Part="1" 
AR Path="/5D07AF19" Ref="C3"  Part="1" 
F 0 "C3" H 11375 5800 50  0000 L CNN
F 1 "302010138" H 11375 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 11388 5550 50  0001 C CNN
F 3 "" H 11350 5700 50  0001 C CNN
	1    11350 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	11350 5900 11350 5850
Connection ~ 11350 5900
Wire Wire Line
	11350 5500 11350 5550
Connection ~ 11150 5500
Connection ~ 11350 5500
$Comp
L power:VCC #PWR?
U 1 1 5D07AF20
P 11550 5400
AR Path="/5CFC7757/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5D07AF20" Ref="#PWR?"  Part="1" 
AR Path="/5D07AF20" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 11550 5250 50  0001 C CNN
F 1 "VCC" H 11550 5550 50  0000 C CNN
F 2 "" H 11550 5400 50  0001 C CNN
F 3 "" H 11550 5400 50  0001 C CNN
	1    11550 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 5400 11550 5500
Wire Wire Line
	11550 5500 11350 5500
$Comp
L power:GND #PWR?
U 1 1 5D07AF23
P 11600 5900
AR Path="/5CFC7757/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5D07AF23" Ref="#PWR?"  Part="1" 
AR Path="/5D07AF23" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 11600 5650 50  0001 C CNN
F 1 "GND" H 11600 5750 50  0000 C CNN
F 2 "" H 11600 5900 50  0001 C CNN
F 3 "" H 11600 5900 50  0001 C CNN
	1    11600 5900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10750 5900 10950 5900
Wire Wire Line
	10900 5500 10750 5500
Wire Wire Line
	10950 5500 10900 5500
Wire Wire Line
	10950 5900 11150 5900
Wire Wire Line
	11150 5900 11350 5900
Wire Wire Line
	11350 5900 11600 5900
Wire Wire Line
	11150 5500 10950 5500
Wire Wire Line
	11350 5500 11150 5500
Wire Wire Line
	11550 2000 11550 1650
Wire Wire Line
	11000 2000 11550 2000
$Comp
L power:VDD #PWR?
U 1 1 5E2D530B
P 11550 1650
AR Path="/5CFC7757/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E2D530B" Ref="#PWR?"  Part="1" 
AR Path="/5E2D530B" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 11550 1500 50  0001 C CNN
F 1 "VDD" H 11550 1800 50  0000 C CNN
F 2 "" H 11550 1650 50  0001 C CNN
F 3 "" H 11550 1650 50  0001 C CNN
	1    11550 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 2100 11950 2100
Wire Wire Line
	11000 2200 11750 2200
Wire Wire Line
	11700 2300 11000 2300
Text Label 10250 7200 0    50   ~ 0
PERIPHOUT
Text Label 10250 7300 0    50   ~ 0
MASTEROUT
Text Label 10250 7100 0    50   ~ 0
CLOCK
Text Label 10250 7400 0    50   ~ 0
SYNC_LOAD
$Comp
L power:VDD #PWR?
U 1 1 5E3C70B6
P 11350 6400
AR Path="/5CFC7757/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E3C70B6" Ref="#PWR?"  Part="1" 
AR Path="/5E3C70B6" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 11350 6250 50  0001 C CNN
F 1 "VDD" H 11350 6550 50  0000 C CNN
F 2 "" H 11350 6400 50  0001 C CNN
F 3 "" H 11350 6400 50  0001 C CNN
	1    11350 6400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E3C7124
P 11300 7000
AR Path="/5CFC7757/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E3C7124" Ref="#PWR?"  Part="1" 
AR Path="/5E3C7124" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 11300 6750 50  0001 C CNN
F 1 "GND" H 11300 6850 50  0000 C CNN
F 2 "" H 11300 7000 50  0001 C CNN
F 3 "" H 11300 7000 50  0001 C CNN
	1    11300 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	10750 5250 10750 5500
Connection ~ 10750 5500
Text Notes 10950 7750 0    50   Italic 10
PERIPHOUT - Output from peripheral to master (output here)\nMASTEROUT - Output from master to peripheral (input here)\nSYNC/LOAD- display to outputs on falling edge\nCLOCK - Change on rising edge, read on falling edge
Wire Wire Line
	9750 7100 10800 7100
Wire Wire Line
	10800 7100 10800 6600
Wire Wire Line
	10800 6600 11350 6600
Wire Wire Line
	9750 7200 10900 7200
Wire Wire Line
	10900 7200 10900 6300
Wire Wire Line
	10900 6300 11350 6300
Wire Wire Line
	9750 7300 12100 7300
Wire Wire Line
	12100 7300 12100 6300
Wire Wire Line
	12100 6300 11850 6300
Wire Wire Line
	9750 7400 12200 7400
Wire Wire Line
	12200 7400 12200 6500
Wire Wire Line
	12200 6500 11850 6500
Wire Wire Line
	11300 7000 11300 6500
Wire Wire Line
	11300 6500 11350 6500
Wire Wire Line
	11300 7000 12000 7000
Wire Wire Line
	12000 7000 12000 6600
Wire Wire Line
	12000 6600 11850 6600
Connection ~ 11300 7000
Wire Wire Line
	11350 6700 11350 7100
Wire Wire Line
	11350 7100 12400 7100
Wire Wire Line
	11850 6700 12400 6700
Wire Wire Line
	12400 6700 12400 7100
$Comp
L CLRLibrary:PIC16F15375-IPT U1
U 1 1 5E2B4FED
P 11050 2550
F 0 "U1" H 11300 2765 50  0000 C CNN
F 1 "PIC16F15375-IPT" H 11300 2674 50  0000 C CNN
F 2 "Package_QFP:LQFP-44_10x10mm_P0.8mm" H 11050 2550 50  0001 C CNN
F 3 "" H 11050 2550 50  0001 C CNN
	1    11050 2550
	1    0    0    -1  
$EndComp
Text Label 10500 4350 0    50   ~ 0
CLOCK
Text Label 10350 4250 0    50   ~ 0
PERIPHOUT
Text Label 10350 4150 0    50   ~ 0
MASTEROUT
Text Label 10350 4050 0    50   ~ 0
SYNC_LOAD
Wire Wire Line
	10300 4150 10800 4150
Wire Wire Line
	10300 4050 10800 4050
Wire Wire Line
	10300 4350 10800 4350
Wire Wire Line
	10300 4250 10800 4250
$Comp
L power:GND #PWR?
U 1 1 5E4937EA
P 10800 4850
AR Path="/5CFC7757/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E4937EA" Ref="#PWR?"  Part="1" 
AR Path="/5E4937EA" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 10800 4600 50  0001 C CNN
F 1 "GND" H 10800 4700 50  0000 C CNN
F 2 "" H 10800 4850 50  0001 C CNN
F 3 "" H 10800 4850 50  0001 C CNN
	1    10800 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 4850 10800 4750
Connection ~ 10800 4750
Wire Wire Line
	10800 4750 10800 4650
$Comp
L power:VDD #PWR?
U 1 1 5E4BC2C7
P 11900 4650
AR Path="/5CFC7757/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E4BC2C7" Ref="#PWR?"  Part="1" 
AR Path="/5E4BC2C7" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 11900 4500 50  0001 C CNN
F 1 "VDD" H 11900 4800 50  0000 C CNN
F 2 "" H 11900 4650 50  0001 C CNN
F 3 "" H 11900 4650 50  0001 C CNN
	1    11900 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	11900 4650 11800 4650
Wire Wire Line
	11800 4650 11800 4750
Connection ~ 11800 4650
Text Label 11150 1900 0    50   ~ 0
nMCLR
Text Label 11150 2200 0    50   ~ 0
IDTA
Text Label 11150 2300 0    50   ~ 0
ICLK
Wire Wire Line
	10300 2700 10800 2700
Wire Wire Line
	10300 2600 10800 2600
Wire Wire Line
	10300 2800 10800 2800
Text Label 10450 2600 0    50   ~ 0
nMCLR
Text Label 10500 2800 0    50   ~ 0
IDTA
Text Label 10500 2700 0    50   ~ 0
ICLK
$Comp
L power:GND #PWR?
U 1 1 5E53921E
P 11950 2100
AR Path="/5CFC7757/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E53921E" Ref="#PWR?"  Part="1" 
AR Path="/5E53921E" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 11950 1850 50  0001 C CNN
F 1 "GND" H 11950 1950 50  0000 C CNN
F 2 "" H 11950 2100 50  0001 C CNN
F 3 "" H 11950 2100 50  0001 C CNN
	1    11950 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11000 1900 11750 1900
Text Label 10450 3950 0    50   ~ 0
ADDRLO
Text Label 10450 3850 0    50   ~ 0
ADDRHI
Wire Wire Line
	10300 3850 10800 3850
Wire Wire Line
	10300 3950 10800 3950
Wire Wire Line
	11800 4300 12700 4300
Wire Wire Line
	12700 4300 12700 4400
$Comp
L power:GND #PWR?
U 1 1 5EA5F3CD
P 12700 5000
AR Path="/5CFC7757/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5EA5F3CD" Ref="#PWR?"  Part="1" 
AR Path="/5EA5F3CD" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 12700 4750 50  0001 C CNN
F 1 "GND" H 12700 4850 50  0000 C CNN
F 2 "" H 12700 5000 50  0001 C CNN
F 3 "" H 12700 5000 50  0001 C CNN
	1    12700 5000
	1    0    0    -1  
$EndComp
$Comp
L CLRLibrary:R_Network08_10Pin RN7
U 1 1 616E92FB
P 8900 3750
F 0 "RN7" V 8233 3750 50  0000 C CNN
F 1 "R_Network08_10Pin" V 8324 3750 50  0000 C CNN
F 2 "CLRLibrary:EXBA10P" V 9475 3750 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 8900 3750 50  0001 C CNN
	1    8900 3750
	0    1    1    0   
$EndComp
Text GLabel 12200 3550 2    60   Input ~ 0
D9
Text GLabel 12200 3650 2    60   Input ~ 0
D10
Text GLabel 12200 3750 2    60   Input ~ 0
D11
Text GLabel 12200 3450 2    60   Input ~ 0
D8
Text GLabel 12200 2600 2    60   Input ~ 0
C0
Text GLabel 12200 2700 2    60   Input ~ 0
C1
Text GLabel 12200 2800 2    60   Input ~ 0
C2
Text GLabel 12200 2900 2    60   Input ~ 0
C3
Text GLabel 12200 3000 2    60   Input ~ 0
C4
Text GLabel 12200 3100 2    60   Input ~ 0
C5
Text GLabel 12200 3200 2    60   Input ~ 0
C6
Text GLabel 12200 3300 2    60   Input ~ 0
C7
Text GLabel 12200 3850 2    60   Input ~ 0
C8
Text GLabel 12200 3950 2    60   Input ~ 0
C9
Text GLabel 12200 4050 2    60   Input ~ 0
C10
Text GLabel 12200 4150 2    60   Input ~ 0
C11
Text Label 11900 2600 0    50   ~ 0
RD0
Text Label 11900 2700 0    50   ~ 0
RD1
Text Label 11900 2800 0    50   ~ 0
RD2
Text Label 11900 3000 0    50   ~ 0
RD4
Text Label 11900 3100 0    50   ~ 0
RD5
Text Label 11900 3200 0    50   ~ 0
RD6
Text Label 11900 3300 0    50   ~ 0
RD7
Wire Wire Line
	11800 2700 12200 2700
Text Label 11900 2900 0    50   ~ 0
RD3
Wire Wire Line
	11800 2600 12200 2600
Wire Wire Line
	11800 2900 12200 2900
Wire Wire Line
	11800 2800 12200 2800
Wire Wire Line
	11800 3200 12200 3200
Wire Wire Line
	11800 3300 12200 3300
Wire Wire Line
	11800 3000 12200 3000
Wire Wire Line
	11800 3100 12200 3100
Text GLabel 8700 4050 0    60   Input ~ 0
C0
Text GLabel 8700 3950 0    60   Input ~ 0
C1
Text GLabel 8700 3850 0    60   Input ~ 0
C2
Text GLabel 8700 3750 0    60   Input ~ 0
C3
Text GLabel 5350 3600 2    60   Input ~ 0
C4
Text GLabel 5350 3400 2    60   Input ~ 0
C5
Text GLabel 5350 3200 2    60   Input ~ 0
C6
Text GLabel 5350 3000 2    60   Input ~ 0
C7
Text GLabel 8700 3650 0    60   Input ~ 0
C8
Text GLabel 8700 3550 0    60   Input ~ 0
C9
Text GLabel 8700 3450 0    60   Input ~ 0
C10
Text GLabel 8700 3350 0    60   Input ~ 0
C11
$Comp
L power:VDD #PWR?
U 1 1 620F2205
P 9100 3350
AR Path="/5CFC7757/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/620F2205" Ref="#PWR?"  Part="1" 
AR Path="/620F2205" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 9100 3200 50  0001 C CNN
F 1 "VDD" H 9100 3500 50  0000 C CNN
F 2 "" H 9100 3350 50  0001 C CNN
F 3 "" H 9100 3350 50  0001 C CNN
	1    9100 3350
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 620F2522
P 9100 4050
AR Path="/5CFC7757/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/620F2522" Ref="#PWR?"  Part="1" 
AR Path="/620F2522" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 9100 3900 50  0001 C CNN
F 1 "VDD" H 9100 4200 50  0000 C CNN
F 2 "" H 9100 4050 50  0001 C CNN
F 3 "" H 9100 4050 50  0001 C CNN
	1    9100 4050
	0    1    1    0   
$EndComp
Text GLabel 4600 4200 2    60   Input ~ 0
D0
Text GLabel 4600 4300 2    60   Input ~ 0
D1
Text GLabel 4600 4400 2    60   Input ~ 0
D2
Text GLabel 4600 4500 2    60   Input ~ 0
D3
Text GLabel 4600 4600 2    60   Input ~ 0
D4
Text GLabel 4600 4700 2    60   Input ~ 0
D5
Text GLabel 4600 4800 2    60   Input ~ 0
D6
Text GLabel 4600 4900 2    60   Input ~ 0
D7
Text GLabel 4100 4200 0    60   Input ~ 0
C0
Text GLabel 4100 4300 0    60   Input ~ 0
C1
Text GLabel 4100 4400 0    60   Input ~ 0
C2
Text GLabel 4100 4500 0    60   Input ~ 0
C3
Text GLabel 4100 4600 0    60   Input ~ 0
C4
Text GLabel 4100 4700 0    60   Input ~ 0
C5
Text GLabel 4100 4800 0    60   Input ~ 0
C6
Text GLabel 4100 4900 0    60   Input ~ 0
C7
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J8
U 1 1 6210E705
P 7000 3950
F 0 "J8" H 7050 4767 50  0000 C CNN
F 1 "Conn_02x13_Odd_Even" H 7050 4676 50  0000 C CNN
F 2 "CLRLibrary:RibbonCableSocket_26_OddEven" H 7000 3950 50  0001 C CNN
F 3 "~" H 7000 3950 50  0001 C CNN
	1    7000 3950
	1    0    0    -1  
$EndComp
Text GLabel 6800 4250 0    60   Input ~ 0
C6
Text GLabel 6800 4350 0    60   Input ~ 0
C8
Text GLabel 6800 4450 0    60   Input ~ 0
C10
Text GLabel 7300 4150 2    60   Input ~ 0
C5
Text GLabel 7300 4250 2    60   Input ~ 0
C7
Text GLabel 7300 4350 2    60   Input ~ 0
C9
Text GLabel 7300 4450 2    60   Input ~ 0
C11
$Comp
L power:VDD #PWR?
U 1 1 6212743A
P 6800 4550
AR Path="/5CFC7757/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/6212743A" Ref="#PWR?"  Part="1" 
AR Path="/6212743A" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 6800 4400 50  0001 C CNN
F 1 "VDD" H 6800 4700 50  0000 C CNN
F 2 "" H 6800 4550 50  0001 C CNN
F 3 "" H 6800 4550 50  0001 C CNN
	1    6800 4550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 62127835
P 7300 4550
F 0 "#PWR02" H 7300 4300 50  0001 C CNN
F 1 "GND" H 7300 4400 50  0000 C CNN
F 2 "" H 7300 4550 50  0001 C CNN
F 3 "" H 7300 4550 50  0001 C CNN
	1    7300 4550
	0    -1   -1   0   
$EndComp
Text GLabel 3150 3800 2    60   Input ~ 0
C5
$Comp
L 156adapter-rescue:Conn_02x08_Odd_Even-conn J7
U 1 1 6212C02C
P 5550 4500
F 0 "J7" H 5600 5017 50  0000 C CNN
F 1 "Conn_02x08_Odd_Even-conn" H 5600 4926 50  0000 C CNN
F 2 "CLRLibrary:MicromaTch-16" H 5550 4500 50  0001 C CNN
F 3 "" H 5550 4500 50  0001 C CNN
	1    5550 4500
	1    0    0    -1  
$EndComp
Text GLabel 5850 4200 2    60   Input ~ 0
D0
Text GLabel 5850 4300 2    60   Input ~ 0
D1
Text GLabel 5850 4400 2    60   Input ~ 0
D2
Text GLabel 5850 4500 2    60   Input ~ 0
D3
Text GLabel 5850 4600 2    60   Input ~ 0
D4
Text GLabel 5850 4700 2    60   Input ~ 0
D5
Text GLabel 5850 4800 2    60   Input ~ 0
D6
Text GLabel 5850 4900 2    60   Input ~ 0
D7
Text GLabel 5350 4200 0    60   Input ~ 0
D8
Text GLabel 5350 4300 0    60   Input ~ 0
D9
Text GLabel 5350 4400 0    60   Input ~ 0
D10
Text GLabel 5350 4500 0    60   Input ~ 0
D11
Text GLabel 5350 4600 0    60   Input ~ 0
C8
Text GLabel 5350 4700 0    60   Input ~ 0
C9
Text GLabel 5350 4800 0    60   Input ~ 0
C10
Text GLabel 5350 4900 0    60   Input ~ 0
C11
Text Notes 4200 5700 0    50   ~ 0
Proper (opposite Rodgers) diode orientation\nColumns: A0,2,4,6; C0,2,4,6: Odd pins\nRows: Even pins
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 62155114
P 3350 5300
F 0 "J2" H 3430 5342 50  0000 L CNN
F 1 "Conn_01x01" H 3430 5251 50  0000 L CNN
F 2 "CLRLibrary:KK156-1" H 3350 5300 50  0001 C CNN
F 3 "~" H 3350 5300 50  0001 C CNN
	1    3350 5300
	1    0    0    -1  
$EndComp
Connection ~ 3150 5300
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J10
U 1 1 620098F7
P 12000 4400
F 0 "J10" H 12050 4617 50  0000 C CNN
F 1 "Conn_02x02_Odd_Even" H 12050 4526 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical" H 12000 4400 50  0001 C CNN
F 3 "~" H 12000 4400 50  0001 C CNN
	1    12000 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6200B9B0
P 12300 4600
AR Path="/5CFC7757/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/6200B9B0" Ref="#PWR?"  Part="1" 
AR Path="/6200B9B0" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 12300 4350 50  0001 C CNN
F 1 "GND" H 12300 4450 50  0000 C CNN
F 2 "" H 12300 4600 50  0001 C CNN
F 3 "" H 12300 4600 50  0001 C CNN
	1    12300 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	12300 4400 12300 4500
Connection ~ 12300 4500
Wire Wire Line
	12300 4500 12300 4600
$EndSCHEMATC
