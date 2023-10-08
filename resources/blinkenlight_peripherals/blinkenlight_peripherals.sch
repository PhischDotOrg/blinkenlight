EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:blinkenlight_peripherals-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Blinkenlight"
Date "9 jun 2015"
Rev "1"
Comp "PhiSch.org"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PWR_FLAG #FLG103
U 1 1 5546040A
P 1500 800
F 0 "#FLG103" H 1500 895 50  0001 C CNN
F 1 "PWR_FLAG" H 1500 980 50  0000 C CNN
F 2 "" H 1500 800 60  0000 C CNN
F 3 "" H 1500 800 60  0000 C CNN
	1    1500 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR104
U 1 1 5546049E
P 1500 1000
F 0 "#PWR104" H 1500 750 50  0001 C CNN
F 1 "GND" H 1500 850 50  0000 C CNN
F 2 "" H 1500 1000 60  0000 C CNN
F 3 "" H 1500 1000 60  0000 C CNN
	1    1500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  750  650  950 
$Comp
L PWR_FLAG #FLG101
U 1 1 5546084F
P 650 950
F 0 "#FLG101" H 650 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 650 1130 50  0000 C CNN
F 2 "" H 650 950 60  0000 C CNN
F 3 "" H 650 950 60  0000 C CNN
	1    650  950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1500 800  1500 1000
$Comp
L CONN_01X02 P103
U 1 1 55575CD9
P 2300 850
F 0 "P103" H 2300 1000 50  0000 C CNN
F 1 "CONN_01X02" V 2400 850 50  0000 C CNN
F 2 "" H 2300 850 60  0000 C CNN
F 3 "" H 2300 850 60  0000 C CNN
	1    2300 850 
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 P102
U 1 1 5557605F
P 1000 2850
F 0 "P102" H 1000 3000 50  0000 C CNN
F 1 "CONN_01X02" V 1100 2850 50  0000 C CNN
F 2 "" H 1000 2850 60  0000 C CNN
F 3 "" H 1000 2850 60  0000 C CNN
	1    1000 2850
	-1   0    0    1   
$EndComp
$Comp
L GNDA #PWR103
U 1 1 555761AE
P 1400 3650
F 0 "#PWR103" H 1400 3400 50  0001 C CNN
F 1 "GNDA" H 1400 3500 50  0000 C CNN
F 2 "" H 1400 3650 60  0000 C CNN
F 3 "" H 1400 3650 60  0000 C CNN
	1    1400 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2900 1400 2900
Wire Wire Line
	1400 2900 1400 3650
Wire Wire Line
	1200 2800 1800 2800
$Comp
L R R102
U 1 1 555762D3
P 1950 2800
F 0 "R102" V 2030 2800 50  0000 C CNN
F 1 "150" V 1950 2800 50  0000 C CNN
F 2 "" V 1880 2800 30  0000 C CNN
F 3 "" H 1950 2800 30  0000 C CNN
	1    1950 2800
	0    1    1    0   
$EndComp
$Comp
L C C101
U 1 1 55576416
P 2300 3050
F 0 "C101" H 2325 3150 50  0000 L CNN
F 1 "100n" H 2325 2950 50  0000 L CNN
F 2 "" H 2338 2900 30  0000 C CNN
F 3 "" H 2300 3050 60  0000 C CNN
	1    2300 3050
	1    0    0    -1  
$EndComp
Connection ~ 1400 3500
$Comp
L R R105
U 1 1 55576683
P 3000 2550
F 0 "R105" V 3080 2550 50  0000 C CNN
F 1 "10k" V 3000 2550 50  0000 C CNN
F 2 "" V 2930 2550 30  0000 C CNN
F 3 "" H 3000 2550 30  0000 C CNN
	1    3000 2550
	1    0    0    -1  
$EndComp
$Comp
L R R106
U 1 1 555767D2
P 3000 3050
F 0 "R106" V 3080 3050 50  0000 C CNN
F 1 "10k" V 3000 3050 50  0000 C CNN
F 2 "" V 2930 3050 30  0000 C CNN
F 3 "" H 3000 3050 30  0000 C CNN
	1    3000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 900  2600 900 
Wire Wire Line
	2600 800  2500 800 
$Comp
L C C102
U 1 1 55576E55
P 2650 2800
F 0 "C102" H 2675 2900 50  0000 L CNN
F 1 "470n" H 2675 2700 50  0000 L CNN
F 2 "" H 2688 2650 30  0000 C CNN
F 3 "" H 2650 2800 60  0000 C CNN
	1    2650 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 2700 3000 2900
Connection ~ 3000 2800
Wire Wire Line
	3000 3200 3000 3650
$Comp
L GND #PWR110
U 1 1 5557712F
P 3000 3650
F 0 "#PWR110" H 3000 3400 50  0001 C CNN
F 1 "GND" H 3000 3500 50  0000 C CNN
F 2 "" H 3000 3650 60  0000 C CNN
F 3 "" H 3000 3650 60  0000 C CNN
	1    3000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2300 3000 2400
$Comp
L GND #PWR108
U 1 1 55577322
P 2600 1000
F 0 "#PWR108" H 2600 750 50  0001 C CNN
F 1 "GND" H 2600 850 50  0000 C CNN
F 2 "" H 2600 1000 60  0000 C CNN
F 3 "" H 2600 1000 60  0000 C CNN
	1    2600 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 900  2600 1000
Wire Wire Line
	2600 800  2600 700 
Connection ~ 3000 3500
Text Label 1300 2800 0    60   ~ 0
Analog_In
Text Label 3200 2800 0    60   ~ 0
Analog_Out
$Comp
L CONN_01X02 P104
U 1 1 5557751E
P 4000 2850
F 0 "P104" H 4000 3000 50  0000 C CNN
F 1 "CONN_01X02" V 4100 2850 50  0000 C CNN
F 2 "" H 4000 2850 60  0000 C CNN
F 3 "" H 4000 2850 60  0000 C CNN
	1    4000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2800 3800 2800
Wire Wire Line
	3800 2900 3300 2900
Wire Wire Line
	3300 2900 3300 3500
Wire Wire Line
	2300 2900 2300 2800
Connection ~ 2300 2800
Wire Wire Line
	2300 3200 2300 3500
Wire Wire Line
	2100 2800 2500 2800
Wire Wire Line
	2300 3500 1400 3500
Wire Wire Line
	3300 3500 3000 3500
Wire Notes Line
	700  1700 4300 1700
Wire Notes Line
	4300 1700 4300 4100
Wire Notes Line
	4300 4100 700  4100
Wire Notes Line
	700  4100 700  1700
Text Notes 800  1850 0    60   ~ 0
Analog Filter and Level Shifter
$Comp
L BS170 Q101
U 1 1 55578671
P 2350 5750
F 0 "Q101" H 2550 5825 50  0000 L CNN
F 1 "BS170" H 2550 5750 50  0000 L CNN
F 2 "TO-92" H 2550 5675 50  0000 L CIN
F 3 "" H 2350 5750 50  0000 L CNN
	1    2350 5750
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR107
U 1 1 5557871F
P 2600 700
F 0 "#PWR107" H 2600 550 50  0001 C CNN
F 1 "+3V3" H 2600 840 50  0000 C CNN
F 2 "" H 2600 700 60  0000 C CNN
F 3 "" H 2600 700 60  0000 C CNN
	1    2600 700 
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR101
U 1 1 55578746
P 650 750
F 0 "#PWR101" H 650 600 50  0001 C CNN
F 1 "+3V3" H 650 890 50  0000 C CNN
F 2 "" H 650 750 60  0000 C CNN
F 3 "" H 650 750 60  0000 C CNN
	1    650  750 
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR109
U 1 1 55578776
P 3000 2300
F 0 "#PWR109" H 3000 2150 50  0001 C CNN
F 1 "+3V3" H 3000 2440 50  0000 C CNN
F 2 "" H 3000 2300 60  0000 C CNN
F 3 "" H 3000 2300 60  0000 C CNN
	1    3000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 750  1100 950 
$Comp
L PWR_FLAG #FLG102
U 1 1 55578863
P 1100 950
F 0 "#FLG102" H 1100 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 1130 50  0000 C CNN
F 2 "" H 1100 950 60  0000 C CNN
F 3 "" H 1100 950 60  0000 C CNN
	1    1100 950 
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR102
U 1 1 55578886
P 1100 750
F 0 "#PWR102" H 1100 600 50  0001 C CNN
F 1 "+5V" H 1100 890 50  0000 C CNN
F 2 "" H 1100 750 60  0000 C CNN
F 3 "" H 1100 750 60  0000 C CNN
	1    1100 750 
	1    0    0    -1  
$EndComp
$Comp
L R R103
U 1 1 55578916
P 2450 5300
F 0 "R103" V 2530 5300 50  0000 C CNN
F 1 "220" V 2450 5300 50  0000 C CNN
F 2 "" V 2380 5300 30  0000 C CNN
F 3 "" H 2450 5300 30  0000 C CNN
	1    2450 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR106
U 1 1 55578A0D
P 2450 6050
F 0 "#PWR106" H 2450 5800 50  0001 C CNN
F 1 "GND" H 2450 5900 50  0000 C CNN
F 2 "" H 2450 6050 60  0000 C CNN
F 3 "" H 2450 6050 60  0000 C CNN
	1    2450 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5950 2450 6050
$Comp
L R R101
U 1 1 55578BFE
P 1900 5800
F 0 "R101" V 1980 5800 50  0000 C CNN
F 1 "100" V 1900 5800 50  0000 C CNN
F 2 "" V 1830 5800 30  0000 C CNN
F 3 "" H 1900 5800 30  0000 C CNN
	1    1900 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 5800 2150 5800
$Comp
L +5V #PWR105
U 1 1 55578D35
P 2450 5050
F 0 "#PWR105" H 2450 4900 50  0001 C CNN
F 1 "+5V" H 2450 5190 50  0000 C CNN
F 2 "" H 2450 5050 60  0000 C CNN
F 3 "" H 2450 5050 60  0000 C CNN
	1    2450 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5450 2450 5550
Connection ~ 2450 5500
$Comp
L R R104
U 1 1 55578DD4
P 2700 5500
F 0 "R104" V 2780 5500 50  0000 C CNN
F 1 "1k" V 2700 5500 50  0000 C CNN
F 2 "" V 2630 5500 30  0000 C CNN
F 3 "" H 2700 5500 30  0000 C CNN
	1    2700 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 5800 1750 5800
$Comp
L CONN_01X02 P101
U 1 1 55578F6B
P 900 5850
F 0 "P101" H 900 6000 50  0000 C CNN
F 1 "CONN_01X02" V 1000 5850 50  0000 C CNN
F 2 "" H 900 5850 60  0000 C CNN
F 3 "" H 900 5850 60  0000 C CNN
	1    900  5850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 5900 1100 5900
Text Label 1150 5800 0    60   ~ 0
WS2812_In
Text Label 3400 5500 0    60   ~ 0
WS2812_Out
$Comp
L CONN_01X02 P105
U 1 1 555793BF
P 4100 5550
F 0 "P105" H 4100 5700 50  0000 C CNN
F 1 "CONN_01X02" V 4200 5550 50  0000 C CNN
F 2 "" H 4100 5550 60  0000 C CNN
F 3 "" H 4100 5550 60  0000 C CNN
	1    4100 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5500 2550 5500
Text Notes 750  4800 0    60   ~ 0
WS2812 Level Shifter (3V -> 5V)
Wire Wire Line
	2450 5050 2450 5150
Wire Wire Line
	1700 5900 1700 6000
Wire Wire Line
	1700 6000 3700 6000
Connection ~ 2450 6000
$Comp
L C C103
U 1 1 5557A20C
P 2950 5750
F 0 "C103" H 2975 5850 50  0000 L CNN
F 1 "10p" H 2975 5650 50  0000 L CNN
F 2 "" H 2988 5600 30  0000 C CNN
F 3 "" H 2950 5750 60  0000 C CNN
	1    2950 5750
	1    0    0    -1  
$EndComp
$Comp
L R R107
U 1 1 5557A70F
P 3200 5500
F 0 "R107" V 3280 5500 50  0000 C CNN
F 1 "220" V 3200 5500 50  0000 C CNN
F 2 "" V 3130 5500 30  0000 C CNN
F 3 "" H 3200 5500 30  0000 C CNN
	1    3200 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 5500 3900 5500
Wire Wire Line
	3900 5600 3700 5600
Wire Wire Line
	3700 5600 3700 6000
Wire Wire Line
	2950 5900 2950 6000
Connection ~ 2950 6000
Wire Wire Line
	2850 5500 3050 5500
Wire Wire Line
	2950 5500 2950 5600
Connection ~ 2950 5500
Wire Notes Line
	700  4700 4300 4700
Wire Notes Line
	4300 4700 4300 6400
Wire Notes Line
	4300 6400 700  6400
Wire Notes Line
	700  6400 700  4700
$Comp
L CONN_01X02 P106
U 1 1 55588E9B
P 5100 2550
F 0 "P106" H 5100 2700 50  0000 C CNN
F 1 "CONN_01X02" V 5200 2550 50  0000 C CNN
F 2 "" H 5100 2550 60  0000 C CNN
F 3 "" H 5100 2550 60  0000 C CNN
	1    5100 2550
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR111
U 1 1 55589566
P 5400 2400
F 0 "#PWR111" H 5400 2250 50  0001 C CNN
F 1 "+5V" H 5400 2540 50  0000 C CNN
F 2 "" H 5400 2400 60  0000 C CNN
F 3 "" H 5400 2400 60  0000 C CNN
	1    5400 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2500 5500 2500
Wire Wire Line
	5400 2500 5400 2400
Wire Wire Line
	5300 2600 5400 2600
Wire Wire Line
	5400 2600 5400 3100
$Comp
L GND #PWR112
U 1 1 5558965B
P 5400 3100
F 0 "#PWR112" H 5400 2850 50  0001 C CNN
F 1 "GND" H 5400 2950 50  0000 C CNN
F 2 "" H 5400 3100 60  0000 C CNN
F 3 "" H 5400 3100 60  0000 C CNN
	1    5400 3100
	1    0    0    -1  
$EndComp
$Comp
L R R110
U 1 1 55589691
P 5650 2500
F 0 "R110" V 5730 2500 50  0000 C CNN
F 1 "100" V 5650 2500 50  0000 C CNN
F 2 "" V 5580 2500 30  0000 C CNN
F 3 "" H 5650 2500 30  0000 C CNN
	1    5650 2500
	0    1    1    0   
$EndComp
$Comp
L CP C104
U 1 1 555896D8
P 5900 2750
F 0 "C104" H 5925 2850 50  0000 L CNN
F 1 "100u" H 5925 2650 50  0000 L CNN
F 2 "" H 5938 2600 30  0000 C CNN
F 3 "" H 5900 2750 60  0000 C CNN
	1    5900 2750
	1    0    0    -1  
$EndComp
Connection ~ 5400 2500
Wire Wire Line
	5800 2500 6000 2500
Wire Wire Line
	5900 2500 5900 2600
Wire Wire Line
	5900 2900 5900 3000
Wire Wire Line
	5900 3000 5400 3000
Connection ~ 5400 3000
Connection ~ 5900 2500
Text Label 6100 2500 0    60   ~ 0
Vdd
Wire Notes Line
	4800 2000 4800 3300
Wire Notes Line
	4800 3300 6300 3300
Wire Notes Line
	6300 3300 6300 2000
Wire Notes Line
	6300 2000 4800 2000
Text Notes 4900 2100 0    60   ~ 0
Stabilized Supply Voltage
$Comp
L R R113
U 1 1 55589FF1
P 7050 2300
F 0 "R113" V 7130 2300 50  0000 C CNN
F 1 "6k8" V 7050 2300 50  0000 C CNN
F 2 "" V 6980 2300 30  0000 C CNN
F 3 "" H 7050 2300 30  0000 C CNN
	1    7050 2300
	0    1    1    0   
$EndComp
$Comp
L C C107
U 1 1 5558A10F
P 7300 2550
F 0 "C107" H 7325 2650 50  0000 L CNN
F 1 "470n" H 7325 2450 50  0000 L CNN
F 2 "" H 7338 2400 30  0000 C CNN
F 3 "" H 7300 2550 60  0000 C CNN
	1    7300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2300 7800 2300
Wire Wire Line
	7300 2300 7300 2400
Wire Wire Line
	6900 2300 6800 2300
Text Label 6800 2300 2    60   ~ 0
Vdd
$Comp
L GND #PWR115
U 1 1 5558A340
P 7300 2900
F 0 "#PWR115" H 7300 2650 50  0001 C CNN
F 1 "GND" H 7300 2750 50  0000 C CNN
F 2 "" H 7300 2900 60  0000 C CNN
F 3 "" H 7300 2900 60  0000 C CNN
	1    7300 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2700 7300 2900
Wire Wire Line
	7700 2300 7700 2600
Connection ~ 7300 2300
Wire Wire Line
	7700 2800 7300 2800
Connection ~ 7300 2800
Connection ~ 7700 2300
$Comp
L C C108
U 1 1 5558A7EE
P 7950 2300
F 0 "C108" H 7975 2400 50  0000 L CNN
F 1 "100n" H 7975 2200 50  0000 L CNN
F 2 "" H 7988 2150 30  0000 C CNN
F 3 "" H 7950 2300 60  0000 C CNN
	1    7950 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	8200 2400 8200 2300
Wire Wire Line
	8100 2300 8400 2300
$Comp
L R R115
U 1 1 5558A95D
P 8200 2550
F 0 "R115" V 8280 2550 50  0000 C CNN
F 1 "100k" V 8200 2550 50  0000 C CNN
F 2 "" V 8130 2550 30  0000 C CNN
F 3 "" H 8200 2550 30  0000 C CNN
	1    8200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2700 8200 2800
Text Label 8200 2800 3    60   ~ 0
Vgnd
Connection ~ 8200 2300
$Comp
L R R108
U 1 1 5558AC33
P 5400 4150
F 0 "R108" V 5480 4150 50  0000 C CNN
F 1 "10k" V 5400 4150 50  0000 C CNN
F 2 "" V 5330 4150 30  0000 C CNN
F 3 "" H 5400 4150 30  0000 C CNN
	1    5400 4150
	1    0    0    -1  
$EndComp
$Comp
L R R109
U 1 1 5558AC90
P 5400 4650
F 0 "R109" V 5480 4650 50  0000 C CNN
F 1 "10k" V 5400 4650 50  0000 C CNN
F 2 "" V 5330 4650 30  0000 C CNN
F 3 "" H 5400 4650 30  0000 C CNN
	1    5400 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR113
U 1 1 5558ACE9
P 5400 4900
F 0 "#PWR113" H 5400 4650 50  0001 C CNN
F 1 "GND" H 5400 4750 50  0000 C CNN
F 2 "" H 5400 4900 60  0000 C CNN
F 3 "" H 5400 4900 60  0000 C CNN
	1    5400 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3900 5400 4000
Wire Wire Line
	5400 4300 5400 4500
Wire Wire Line
	5400 4800 5400 4900
Connection ~ 5400 4400
Text Label 6000 4400 0    60   ~ 0
Vgnd
Text Label 5400 3900 1    60   ~ 0
Vdd
Wire Notes Line
	6300 3500 6300 5100
Wire Notes Line
	4800 5100 4800 3500
Text Notes 4900 3650 0    60   ~ 0
Virtual GND for OpAmps
$Comp
L CP C105
U 1 1 5558B0D7
P 5900 4650
F 0 "C105" H 5925 4750 50  0000 L CNN
F 1 "CP" H 5925 4550 50  0000 L CNN
F 2 "" H 5938 4500 30  0000 C CNN
F 3 "" H 5900 4650 60  0000 C CNN
	1    5900 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4900 5900 4800
Wire Wire Line
	5900 4400 5900 4500
Connection ~ 5900 4400
NoConn ~ 7700 2600
NoConn ~ 7700 2800
Text Label 8400 2300 0    60   ~ 0
Vmic
Wire Notes Line
	6500 2000 6500 3300
Wire Notes Line
	6500 3300 8800 3300
Wire Notes Line
	8800 3300 8800 2000
Wire Notes Line
	8800 2000 6500 2000
Text Notes 6600 2100 0    60   ~ 0
Microphone
$Comp
L LM358 U101
U 1 1 5558B93D
P 9150 4300
F 0 "U101" H 9100 4500 60  0000 L CNN
F 1 "LM358" H 9100 4050 60  0000 L CNN
F 2 "" H 9150 4300 60  0000 C CNN
F 3 "" H 9150 4300 60  0000 C CNN
	1    9150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4800 7350 4900
$Comp
L GND #PWR116
U 1 1 5558BB76
P 7350 4900
F 0 "#PWR116" H 7350 4650 50  0001 C CNN
F 1 "GND" H 7350 4750 50  0000 C CNN
F 2 "" H 7350 4900 60  0000 C CNN
F 3 "" H 7350 4900 60  0000 C CNN
	1    7350 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4000 7350 3900
Text Label 7350 3900 1    60   ~ 0
Vdd
$Comp
L R R114
U 1 1 5558BE0A
P 8050 4750
F 0 "R114" V 8130 4750 50  0000 C CNN
F 1 "22k" V 8050 4750 50  0000 C CNN
F 2 "" V 7980 4750 30  0000 C CNN
F 3 "" H 8050 4750 30  0000 C CNN
	1    8050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 4400 8150 4400
Wire Wire Line
	6850 4300 6950 4300
$Comp
L R R112
U 1 1 5558C1D2
P 6850 5450
F 0 "R112" V 6930 5450 50  0000 C CNN
F 1 "2k2" V 6850 5450 50  0000 C CNN
F 2 "" V 6780 5450 30  0000 C CNN
F 3 "" H 6850 5450 30  0000 C CNN
	1    6850 5450
	1    0    0    -1  
$EndComp
$Comp
L R R111
U 1 1 5558C5FB
P 5650 4400
F 0 "R111" V 5730 4400 50  0000 C CNN
F 1 "100" V 5650 4400 50  0000 C CNN
F 2 "" V 5580 4400 30  0000 C CNN
F 3 "" H 5650 4400 30  0000 C CNN
	1    5650 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 4400 5500 4400
Wire Wire Line
	5800 4400 6000 4400
Wire Wire Line
	5400 4900 5900 4900
Wire Notes Line
	4800 3500 6300 3500
Wire Notes Line
	6300 5100 4800 5100
Wire Wire Line
	6850 5200 7350 5200
Wire Wire Line
	6850 4500 6850 5300
Wire Wire Line
	6850 4500 6950 4500
$Comp
L GND #PWR114
U 1 1 5558D686
P 6850 6100
F 0 "#PWR114" H 6850 5850 50  0001 C CNN
F 1 "GND" H 6850 5950 50  0000 C CNN
F 2 "" H 6850 6100 60  0000 C CNN
F 3 "" H 6850 6100 60  0000 C CNN
	1    6850 6100
	1    0    0    -1  
$EndComp
Connection ~ 6850 5200
Wire Wire Line
	6850 5600 6850 5700
$Comp
L C C106
U 1 1 5558D956
P 6850 5850
F 0 "C106" H 6875 5950 50  0000 L CNN
F 1 "100n" H 6875 5750 50  0000 L CNN
F 2 "" H 6888 5700 30  0000 C CNN
F 3 "" H 6850 5850 60  0000 C CNN
	1    6850 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 6000 6850 6100
Text Label 6850 4300 2    60   ~ 0
Vmic
$Comp
L R R116
U 1 1 5558DF6E
P 8300 4400
F 0 "R116" V 8380 4400 50  0000 C CNN
F 1 "2k2" V 8300 4400 50  0000 C CNN
F 2 "" V 8230 4400 30  0000 C CNN
F 3 "" H 8300 4400 30  0000 C CNN
	1    8300 4400
	0    1    1    0   
$EndComp
Connection ~ 8050 4400
$Comp
L LM358 U101
U 2 1 5558E0C9
P 7450 4400
F 0 "U101" H 7400 4600 60  0000 L CNN
F 1 "LM358" H 7400 4150 60  0000 L CNN
F 2 "" H 7450 4400 60  0000 C CNN
F 3 "" H 7450 4400 60  0000 C CNN
	2    7450 4400
	1    0    0    -1  
$EndComp
Text Label 8450 4200 2    60   ~ 0
Vgnd
Wire Wire Line
	8450 4200 8650 4200
Wire Wire Line
	8650 4400 8450 4400
$Comp
L GND #PWR117
U 1 1 5558E5A3
P 9050 4800
F 0 "#PWR117" H 9050 4550 50  0001 C CNN
F 1 "GND" H 9050 4650 50  0000 C CNN
F 2 "" H 9050 4800 60  0000 C CNN
F 3 "" H 9050 4800 60  0000 C CNN
	1    9050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4700 9050 4800
Wire Wire Line
	9050 3900 9050 3800
Text Label 9050 3800 1    60   ~ 0
Vdd
$Comp
L R R117
U 1 1 5558E879
P 9750 4850
F 0 "R117" V 9830 4850 50  0000 C CNN
F 1 "22k" V 9750 4850 50  0000 C CNN
F 2 "" V 9680 4850 30  0000 C CNN
F 3 "" H 9750 4850 30  0000 C CNN
	1    9750 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4400 8550 5200
Wire Wire Line
	8550 5200 8950 5200
Connection ~ 8550 4400
Wire Wire Line
	9650 4300 10000 4300
Connection ~ 9750 4300
Text Label 9850 4300 0    60   ~ 0
Vout
$Comp
L CONN_01X02 P107
U 1 1 5558EC0E
P 10200 4350
F 0 "P107" H 10200 4500 50  0000 C CNN
F 1 "CONN_01X02" V 10300 4350 50  0000 C CNN
F 2 "" H 10200 4350 60  0000 C CNN
F 3 "" H 10200 4350 60  0000 C CNN
	1    10200 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 4400 9900 4400
Wire Wire Line
	9900 4400 9900 4500
$Comp
L GND #PWR118
U 1 1 5558EDC2
P 9900 4500
F 0 "#PWR118" H 9900 4250 50  0001 C CNN
F 1 "GND" H 9900 4350 50  0000 C CNN
F 2 "" H 9900 4500 60  0000 C CNN
F 3 "" H 9900 4500 60  0000 C CNN
	1    9900 4500
	1    0    0    -1  
$EndComp
Wire Notes Line
	10400 6400 10400 1700
Wire Notes Line
	4700 6400 10400 6400
Text Notes 4800 1850 0    60   ~ 0
Microphone Amplifier
Text Label 7700 2600 0    60   ~ 0
Pin1
Text Label 7700 2800 0    60   ~ 0
Pin2
Wire Notes Line
	4700 6400 4700 1700
Wire Notes Line
	4700 1700 10400 1700
$Comp
L JUMPER JP?
U 1 1 5577295E
P 7650 5200
F 0 "JP?" H 7650 5350 60  0000 C CNN
F 1 "JUMPER" H 7650 5120 40  0000 C CNN
F 2 "~" H 7650 5200 60  0000 C CNN
F 3 "~" H 7650 5200 60  0000 C CNN
	1    7650 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4400 8050 4500
Wire Wire Line
	8050 5000 8050 5200
$Comp
L JUMPER JP?
U 1 1 55772A78
P 9250 5200
F 0 "JP?" H 9250 5350 60  0000 C CNN
F 1 "JUMPER" H 9250 5120 40  0000 C CNN
F 2 "~" H 9250 5200 60  0000 C CNN
F 3 "~" H 9250 5200 60  0000 C CNN
	1    9250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4300 9750 4600
Wire Wire Line
	8050 5200 7950 5200
Wire Wire Line
	9750 5200 9550 5200
Wire Wire Line
	9750 5100 9750 5200
$EndSCHEMATC
