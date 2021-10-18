//R0 = 2

0: LDR R2, #1 			//R2 = 1
1: LDR R1, #1 			//R1 = 1 
2: MUL R2, R2, R0 		//R2 = R2 * R0 = 1 * 2 = 2
3: SUB R0, R0, R1		//R0 = R0 - R1 = 2 - 1 = 1
4: CMP R3, R0, R1		//R3 = 100(Binary) = 4
5: JGT R3, -16			//Ingenting skjer

R2 = 2 = 00000000000000000000000000000010

//R0 = 3

0: LDR R2, #1 			//R2 = 1
1: LDR R1, #1 			//R1 = 1 
2: MUL R2, R2, R0 		//R2 = R2 * R0 = 1 * 3 = 3
3: SUB R0, R0, R1		//R0 = R0 - R1 = 3 - 1 = 2
4: CMP R3, R0, R1		//R3 = 010(Binary) = 2
5: JGT R3, -16			//Brancher til 0x04
6: LDR R1, #1
7: MUL R2, R2, R0		//R2 = R2 * R0 = 3 * 2 = 6
8: SUB R0, R0, R1		//R0 = R0 - R1 = 2 - 1 = 1
9: CMP R3, R0, R1		//R3 = 100(Binary) = 4
10: JGT R3, -16			//Ingenting skjer

R2 = 6 = 00000000000000000000000000000110

//R0 = 4

0: LDR R2, #1 			//R2 = 1
1: LDR R1, #1 			//R1 = 1 
2: MUL R2, R2, R0 		//R2 = R2 * R0 = 1 * 4 = 4
3: SUB R0, R0, R1		//R0 = R0 - R1 = 4 - 1 = 3
4: CMP R3, R0, R1		//R3 = 010(Binary) = 2
5: JGT R3, -16			//Brancher til 0x04
6: LDR R1, #1
7: MUL R2, R2, R0		//R2 = R2 * R0 = 4 * 3 = 12
8: SUB R0, R0, R1		//R0 = R0 - R1 = 3 - 1 = 2
9: CMP R3, R0, R1		//R3 = 010(Binary) = 2
10: JGT R3, -16			//Brancher til 0x04
11: LDR R1, #1
12: MUL R2, R2, R0		//R2 = R2 * R0 = 12 * 2 = 24
13: SUB R0, R0, R1		//R0 = R0 - R1 = 2 - 1 = 1
14: CMP R3, R0, R1		//R3 = 100(Binary) = 4
15: JGT R3, -16			//Ingenting skjer

R2 = 24 = 00000000000000000000000000011000

//R0 = 9

0: LDR R2, #1 			//R2 = 1
1: LDR R1, #1 			//R1 = 1 
2: MUL R2, R2, R0 		//R2 = R2 * R0 = 1 * 9 = 9
3: SUB R0, R0, R1		//R0 = R0 - R1 = 9 - 1 = 8
4: CMP R3, R0, R1		//R3 = 010(Binary) = 2
5: JGT R3, -16			//Brancher til 0x04
6: LDR R1, #1
7: MUL R2, R2, R0		//R2 = R2 * R0 = 9 * 8 = 12
8: SUB R0, R0, R1		//R0 = R0 - R1 = 3 - 1 = 2
9: CMP R3, R0, R1		//R3 = 010(Binary) = 2
10: JGT R3, -16			//Brancher til 0x04
11: LDR R1, #1
12: MUL R2, R2, R0		//R2 = R2 * R0 = 12 * 2 = 24
13: SUB R0, R0, R1		//R0 = R0 - R1 = 2 - 1 = 1
14: CMP R3, R0, R1		//R3 = 100(Binary) = 4
15: JGT R3, -16			//Ingenting skjer

//General formula: R2 = R0! = 9! = 362880 = 00000000000001011000100110000000

362880 % 2 = 0
181440 % 2 = 0
90720 % 2 = 0
45360 % 2 = 0
22680 % 2 = 0
11340 % 2 = 0
5670 % 2 = 0
2835 % 2 = 1
1417 % 2 = 1
708 % 2 = 0
354 % 2 = 0
177 % 2 = 1
88 % 2 = 0
44 % 2 = 0
22 % 2 = 0
11 % 2 = 1
5 % 2 = 1
2 % 2 = 0
1 % 2 = 1

1011000100110000000