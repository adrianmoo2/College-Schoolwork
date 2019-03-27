`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    05:10:23 03/13/2019 
// Design Name: 
// Module Name:    SPFPMult 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
`define FP_SIZE 32

module SPFPMultipier (
		input clk,
		input rst,
		input enable,
		output reg valid,
		input[31:0]  A,
		input[31:0]  B,
		output reg[`FP_SIZE-1:0] result
	);

//-----Added functionalities----
reg [31:0] yourresult;
reg [31:0] Temp_Result;

reg A_Sign, B_Sign, Temp_Sign, C_Sign;
reg A_Sign_Temp, B_Sign_Temp;

reg [22:0] A_Mantissa, B_Mantissa;
reg [23:0] A_Mantissa_Ext, B_Mantissa_Ext, Temp_Mantissa, C_Mantissa;

reg [7:0] A_Exponent, B_Exponent, C_Exponent, Temp_Exponent, Exp_Shift;

reg carryout = 0;

reg [47:0] Mult_Result;

integer Exp_Diff;

integer index = 0;

always @(*) begin
	//Sign Step
	A_Sign = A[31];
	B_Sign = B[31];
	
	C_Sign = A_Sign ^ B_Sign;
	
	//Mantissa Step
	A_Mantissa = A[22:0];
	B_Mantissa = B[22:0];
	
	A_Mantissa_Ext = {{1'b1}, {A_Mantissa}};
	B_Mantissa_Ext = {{1'b1}, {B_Mantissa}};
	
	Mult_Result = A_Mantissa_Ext * B_Mantissa_Ext;
	
	//NOrmalizatino unit
	Exp_Shift = 0;
	for (index=0; index<48; index=index+1) begin
		if (Mult_Result[47] == 1'b0) begin
			Exp_Shift = Exp_Shift + 1;
			Mult_Result = Mult_Result << 1;
		end
	end
	
	C_Mantissa = Mult_Result[46:23];
	
	//Exponent Step
	A_Exponent = A[30:23];
	B_Exponent = B[30:23];
	
	C_Exponent = A_Exponent + B_Exponent - 127;
	
	if (Exp_Shift == 1'b0) begin
		C_Exponent = C_Exponent + 1;
	end
	
	Temp_Result = {{C_Sign}, {C_Exponent}, {C_Mantissa[23:1]}};
	yourresult = Temp_Result;
	
end

// Sequential Part 
always @(posedge clk) begin

	if (rst) begin
		result <= 0;
		valid  <= 0;
	end
	else begin
		result <= yourresult; 
		valid <= enable;
	end
end


endmodule
