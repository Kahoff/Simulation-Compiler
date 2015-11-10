# Simulation-Compiler

A Compiler for a Simulated Motherboard

Version 1.0



Kyle Hoffmann - March 20/15



A compiler that coverts a custom assembly language to a bytecode used in a simulated Motherboard. 

Unfortunately I am presently unable to post the finished Motherboard.

Special Thanks to https://github.com/binexec for creating the design document.


Running the code requires specifying a file to compile.
compiler [filename]

or if the user wishes to name the outputfile they must include -o and the new filename
compiler [filename] -o [outputname]

--------------------------------------------------------------------------------



Insturctions work as follows:

Instruction Format
Rs, Rt, and Rd are register numbers in binary. 
Any field with “X” in them means it doesn’t matter what value it is. Assume they are zero for safety. 

Calculations:
	5-bit Opcode, 3-bit Rs (Operand1), 3-bit Rt (Operand2), 3-bit Rd (Destination), XX

Calculations with Immediate:
	5-bit Opcode, 3-bit Rs (Destination), 3-bit Rt (Operand1),X, 4-bit Immediate Data

Compare:
	5-bit Opcode, 3-bit Rs (Operand1), 3-bit Rt (Operand2), XXXXX

Load/Store:
	5-bit Opcode, 3-bit Rs (Destination/Source), 8-bit Memory Address

Load/Compare Immediate:
	5-bit Opcode, 3-bit Rs (Destination/Operand1),XXXX, 4-bit Immediate Data

Branch:
	5-bit Opcode, 11-bit ROM address
	
External I/O:
	5-bit Opcode, 3-bit Rs (Source/Destination), XXXXXXXX

Instructions
NO-OP
NOP

OPCODE: 00000
Descriptions:
	The CPU does nothing productive during this clock cycle. 

Load Register
LDR Rs Addr	
Rs = Destination Register
	Addr = 8-bit Address in binary

OPCODE = 00001
Instruction Format: Load/Store
Descriptions:
	Loads the word at Addr into Rs register.
Usage Example:
	Loads the content at memory address 100001 into R0.
LDR R0 M33		

Store Register
STR Rs Addr
Rs = Source Register
	Addr = 8-bit Address in binary

OPCODE = 00010
Instruction Format: Load/Store
Descriptions:
	Stores the word at Rs into Addr register.
Usage Example:
	Stores the value at R0 into the memory at address 100001.
STR R0 M33		

Move Register
MOV Rd Rs
Rd = Destination Register
	Rs= Source Register

OPCODE = 00011
Instruction Format: Calculations
Descriptions:
	Copies the value in Rs into Rd.
Usage Example:
	Copies the content of R1 into R0.
MOV R0 R1		

Load Immediate
LDI Rs VALUE
	Rs = Destination Register
	VALUE = 4-bit Immediate Value

OPCODE = 00100
Instruction Format: Load/Compare Immediate
Descriptions:
	Load an immediate value into Rs. Immediate values must be between -8 and 7.
Usage Example:
	Loads the immediate value of 4 into R0.
LDR R0 4		

Load From External
LDE Rs
	Rs = Destination Register
	
OPCODE = 00101
Instruction Format: External I/O
Descriptions:
	Loads data from EXT_DATA_IN into Rs.
Usage Example:
Suppose the value “1010” is currently being inputted at EXT_DATA_IN. By running the following instruction:
LDE R0
...the content of R0 will be 1010.

Output External
OUT Rs
Rs = Source Register
	
OPCODE = 00110
Instruction Format: External I/O
Descriptions:
Copies the data in Rs into the output buffer and outputs it to DATA_OUTPUT. The output data will not change unless the OUT 

instruction is used again.
Usage Example:
	Send the content of R0 into DATA_OUTPUT
OUT R0

Addition
ADD Rd Rs Rt
	Rd = Destination Register
	Rs = Source Register 1
	Rt = Source Register 2

OPCODE = 00111
Instruction Format: Calculations
Descriptions:
	Adds Rs and Rt and returns the value into Rd.
Usage Example:
	Add the content of R0 with R1 and then store the result back into R0
ADD R0 R0 R1

Addition with Immediate
ADDI Rs Rt VALUE
	Rs = Destination Register
	Rt = Source Register 1
	VALUE = 4-bit Immediate Value

OPCODE = 01000
Instruction Format: Calculations with Immediate
Descriptions:
	Adds Rt and VALUE and returns the value into Rs. Immediate values must be between -8 and 7.
Usage Example:
	Add the content of R0 with 4 and then store the result back into R1
ADDI R1 R0 4

Subtraction
SUB Rd Rs Rt
	Rd = Destination Register
	Rs = Source Register 1
	Rt = Source Register 2

OPCODE = 01001
Instruction Format: Calculations
Descriptions:
	Subtracts Rs with Rt and returns the value into Rd.
Usage Example:
	Subtracts the content of R0 with R1 and then store the result back into R0
SUB R0 R0 R1

Subtraction with Immediate
SUBI Rs Rt VALUE
Rs = Destination Register
	Rt = Source Register 1
	VALUE = 4-bit Immediate Value

OPCODE = 01010
Instruction Format: Calculations with Immediate
Descriptions:
	Subtracts Rt with VALUE  and returns the value into Rs. Immediate values must be between -8 and 7.
Usage Example:
	Subtracts the content of R0 with 4 and then store the result back into R1
SUBI R1 R0 4

AND
AND Rd Rs Rt
	Rd = Destination Register
	Rs = Source Register 1
	Rt = Source Register 2

OPCODE = 01011
Instruction Format: Calculations
Descriptions:
Ands Rs and Rt and returns the value into Rd. 
Usage Example:
	AND the content of R0 with R1 and then store the result back into R0
AND R0 R0 R1

AND Immediate
ANDI Rs Rt VALUE
Rs = Destination Register
	Rt = Source Register 1
	VALUE = 4-bit Immediate Value

OPCODE = 01100
Instruction Format: Calculations with Immediate
Descriptions:
	Ands Rt and VALUE and returns the value into Rs. Immediate values must be between -8 and 7 and expressed as an integer.

Usage Example:
	AND the content of R0 with 4 and then store the result back into R1
ANDI R1 R0 4

OR
OR Rd Rs Rt
	Rd = Destination Register
	Rs = Source Register 1
	Rt = Source Register 2

OPCODE = 01101
Instruction Format: Calculations
Descriptions:
	ORs Rs and Rt and returns the value into Rd.
Usage Example:
	OR the content of R0 with R1 and then store the result back into R0
OR R0 R0 R1

OR Immediate
ORI Rs Rt VALUE
Rs = Destination Register
	Rt = Source Register 1
	VALUE = 4-bit Immediate Value

OPCODE = 01110
Instruction Format: Calculations with Immediate
Descriptions:
	ORs Rt and VALUE and returns the value into Rs. Immediate values must be between -8 and 7 and expressed as an integer.

Usage Example:
	OR the content of R0 with 4 and then store the result back into R1
ORI R1 R0 4

XOR
XOR Rd Rs Rt
	Rd = Destination Register
	Rs = Source Register 1
	Rt = Source Register 2

OPCODE = 01111
Instruction Format: Calculations
Descriptions:
	XORs Rs and Rt and returns the value into Rd.
Usage Example:
	XOR the content of R0 with R1 and then store the result back into R0
XOR R0 R0 R1

NOT
NOT Rd Rs
	Rd = Destination Register
	Rs = Source Register 

OPCODE = 10001
Instruction Format: Calculations
Descriptions:
	Returns the value of NOT Rs into Rd.
Usage Example:
	NOT the content of R0 and then store the result back into R1
NOT R1 R0
Compare Greater Than
CGT Rs Rt
	Rs = Source Register 1
	Rt = Source Register 2
	
OPCODE = 10010
Instruction Format: Move/Compare
Descriptions:
	Compares Rs against Rt. Set COND BIT to 1 if RS > Rt, otherwise 0.
	NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions.

Usage Example:
	Check if the content of R0 is greater than the content of R1
CGT R0 R1

Compare Greater Than Immediate
CGTI Rs VALUE
	Rs = Source Register 1
	VALUE = 4-bit Immediate Value
	
OPCODE = 10011
Instruction Format: Load/Compare Immediate
Descriptions:
	Compares Rs against VALUE. Set COND BIT to 1 if RS > VALUE, otherwise 0. Immediate values must be between -8 and 7 and 

expressed as an integer.

	NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions. 

Usage Example:
	Check if the content of R0 is greater than 4
CGTI R0 4

Compare Equality
CEQ Rs Rt
	Rs = Source Register 1
	Rt = Source Register 2
	
OPCODE =10100
Instruction Format: Move/Compare
Descriptions:
	Compares Rs against Rt. Set COND BIT to 1 if RS = Rt, otherwise 0. 
	NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions.

Usage Example:
	Check if the content of R0 is equal to the content of R1
CEQ R0 R1

Compare Equality Immediate
CEQI Rs VALUE
	Rs = Source Register 1
	VALUE = 4-bit Immediate Value
	
OPCODE = 10101
Instruction Format: Load/Compare Immediate
Descriptions:
	Compares Rs against VALUE. Set COND BIT to 1 if RS = VALUE, otherwise 0. Immediate values must be between -8 and 7 and 

expressed as an integer.

NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions. 

Usage Example:
	Check if the content of R0 is equal to 4
CEQI R0 4

Compare Lesser Than
CLT Rs Rt
	Rs = Source Register 1
	Rt = Source Register 2
	
OPCODE =10110
Instruction Format: Move/Compare
Descriptions:
	Compares Rs against Rt. Set COND BIT to 1 if RS < Rt, otherwise 0.
	NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions. 

Usage Example:
	Check if the content of R0 is lesser than the content of R1
CLT R0 R1

Compare Lesser Than Immediate
CLTI Rs VALUE
	Rs = Source Register 1
	VALUE = 4-bit Immediate Value
	
OPCODE = 10111
Instruction Format: Load/Compare Immediate
Descriptions:
	Compares Rs against VALUE. Set COND BIT to 1 if RS < VALUE, otherwise 0. Immediate values must be between -8 and 7 and 

expressed as an integer.

	NOTE: Result in COND BIT is only valid for the next clock cycle to be used by branch instructions. 

Usage Example:
	Check if the content of R0 is less than 4
CLTI R0 4

Branch Unconditional
B ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11000
Instruction Format: Branch
Descriptions:
Changes PC to ADDR and executes the instructions from that point. The current PC address is not saved in the Jump Register.

Usage Example:
	Jump to the instruction at line 193
		B 193

Branch on True
BT ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11001
Instruction Format: Branch
Descriptions:
Changes PC to ADDR if COND BIT is 1, and executes the instructions from that point. If COND BIT is 0, the branch does not happen and 

execution continues at PC + 1. The current PC address is not saved in the Jump Register if jump occurs.

WARNING: Before calling a conditional branch instruction, the previous instruction executed must be a comparison instruction. 

Otherwise, the branch instruction may not execute correctly. 

Usage Example:
	Jump to the instruction at line 193 if R0 is equal to 0.
		CEQI R0 0
BT 193

Branch on False
BF ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11010
Instruction Format: Branch
Descriptions:
Changes PC to ADDR if COND BIT is 0, and executes the instructions from that point. If COND BIT is 1, the branch does not happen and 

execution continues at PC + 1. The current PC address is not saved in the Jump Register if jump occurs.

WARNING: Before calling a conditional branch instruction, the previous instruction executed must be a  comparison instruction. 

Otherwise,  the branch instruction may not execute correctly. 

Usage Example:
	Jump to the instruction at line 193 if R0 is not 0.
		CEQI R0 0
BF 193

Branch with Link Unconditional
BL ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11011
Instruction Format: Branch
Descriptions:
	Changes PC to ADDR and executes the instructions from that point. 
The current PC address is saved in the Jump Register.

WARNING: Avoid nesting multiple linked branch instructions. The jump register can only save one return address, and any prior nested 

linked branches are unable to return to its original calling point.

Usage Example:
	Jump to the instruction at line 19 with the intention to return later.
BL 193

Branch with Link on True
BTL ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11100
Instruction Format: Branch
Descriptions:
Changes PC to ADDR if COND BIT is 1, and executes the instructions from that point. If COND BIT is 0, the branch does not happen and 

execution continues at PC + 1. The current PC address is saved in the Jump Register if jump occurs.

WARNING: Before calling a conditional branch instruction, the previous instruction executed must be a  comparison instruction. 

Otherwise,  the branch instruction may not execute correctly. 

WARNING: Avoid nesting multiple linked branch instructions. The jump register can only save one return address, and any prior nested 

linked branches are unable to return to its original calling point.

Usage Example:
	Jump to the instruction at line 19  if R0 is not 0, with the intention to return later.
CEQI R0 0
BLT 193

Branch with Link on False
BFL ADDR
	ADDR = 11-bit target branching address
	
OPCODE = 11101
Instruction Format: Branch
Descriptions:
Changes PC to ADDR if COND BIT is 0, and executes the instructions from that point. If COND BIT is 1, the branch does not happen and 

execution continues at PC + 1. The current PC address is saved in the Jump Register if jump occurs.

WARNING: Before calling a conditional branch instruction, the previous instruction executed must be a  comparison instruction. 

Otherwise,  the branch instruction may not execute correctly. 

WARNING: Avoid nesting multiple linked branch instructions. The jump register can only save one return address, and any prior nested 

linked branches are unable to return to its original calling point.

Usage Example:
	Jump to the instruction at line 19  if R0 is not 0, with the intention to return later.
CEQI R0 0
BLF 193

Return From Subroutine
RTN
	OPCODE = 11110
Descriptions:
	Loads the value in the Jump Register back into PC and continues execution at that address.

Usage Example:
	Jump to the instruction at line 19, with the intention to return later.
BLF 193
...
Return from subroutine
	RTN

Halt System
HCF
	OPCODE = 11111
Descriptions:
The infamous “Half and Catch Fire” instruction, which stops the system from executing further instructions by forcing the clock as 1 

constantly. 

WARNING: A hard reset is the only way to get the system out of this state. Only use this instruction at the very end of your program.

Reserved
???
	OPCODE = 10000
Description:
This OPCODE is currently not in use and is treated as a NOP instruction. This instruction being reserved for future implementations. 
One potential application in a future CPU is to use this OPCODE to switch between different instruction sets for compatibility and 

additional functions. 
