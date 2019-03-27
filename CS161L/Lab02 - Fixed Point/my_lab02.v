`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:49:53 01/31/2019 
// Design Name: 
// Module Name:    my_lab02 
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
module my_lab02(
	clk,
	reset,
	partSelector,
	numRadixBits,
	FPInput,
	IEEEInput,
	FPOutput,
	IEEEOutput
    );
	 
//-----Input Ports-----
	input clk;
	input reset;
	input partSelector;
	input [5:0] numRadixBits;
	input [31:0] FPInput;
	input [31:0] IEEEInput;

//-----Output Ports-----
	output [31:0] FPOutput;
	output [31:0] IEEEOutput;

//------Input Ports Data Type-----
	wire clk;
	wire reset;
	wire partSelector;
	wire [5:0] numRadixBits;
	wire [31:0] FPInput;
	wire [31:0] IEEEInput;

//-----Output Ports Data Type-----
	reg [31:0] FPOutput;
	reg [31:0] IEEEOutput;
//------Signed temporary wires-----
	reg signed [31:0] Signed_FPInput;
//------Unsigned temporary wires----
	reg [31:0] temp_FPInput;
	//reg [5:0] temp_numRadixBits;
	reg [7:0] exponent;
	reg [7:0] numShifts;
	reg [22:0] mantissa;
//-----Variables------
	
always @(posedge clk)
begin: mylab02
	numShifts = 8'b01111111;
	case(partSelector)
		1'b0: //Part 1
			begin
				FPOutput = 0;
				Signed_FPInput = FPInput;
				//temp_numRadixBits = numRadixBits;
				
				temp_FPInput = temp_FPInput >> numRadixBits;
				
				if (FPInput == 0) begin
					FPOutput = 0;
				end
				else if (temp_FPInput == 1'b1) begin
						numShifts = 8'b01111111; //Not necessary, but just good to have
				end
				else if (temp_FPInput >= 2'b10) begin
					while (temp_FPInput >= 2'b10) begin
						temp_FPInput = temp_FPInput >> 1;
						numShifts = numShifts + 1;
					end
				end
				else if (temp_FPInput == 0) begin
					temp_FPInput = FPInput;
					while (temp_FPInput >= 2'b10) begin
							temp_FPInput = temp_FPInput >> 1;
							numShifts = numShifts - 1;
					end
				end
				
				exponent = numShifts;
				
				//Sign bit portion
				
				if (Signed_FPInput < 0)
					FPOutput = FPOutput | 32'b10000000000000000000000000000000;
				
				
			end
		1'b1: //Part 2
			begin
			end
		default: $display("default");
	endcase
end


endmodule



