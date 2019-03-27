`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   01:17:26 02/08/2019
// Design Name:   alu_control
// Module Name:   /home/ise/Desktop/CS161L_LABS/CS161L_LAB03_Redo/alu_control_tb.v
// Project Name:  CS161L_LAB03_Redo
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: alu_control
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module alu_control_tb;

	// Inputs
	reg clk;
	reg reset;
	reg [1:0] alu_op;
	reg [5:0] instruction_5_0;

	// Outputs
	wire [3:0] alu_out;

	// Instantiate the Unit Under Test (UUT)
	alu_control uut (
		.clk(clk), 
		.reset(reset), 
		.alu_op(alu_op), 
		.instruction_5_0(instruction_5_0), 
		.alu_out(alu_out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 0;
		alu_op = 0;
		instruction_5_0 = 0;

	end
	
	initial begin 
		alu_op = 2'b00;
		instruction_5_0 = 6'bxxxxxx; #5;
		
		alu_op = 2'b01;
		instruction_5_0 = 6'bxxxxxx; #5;
		
		alu_op = 2'b10;
		instruction_5_0 = 6'bxxxxxx; #5;
		
		alu_op = 2'b11;
		instruction_5_0 = 6'bxxxxxx; #5;
		
		
		for (instruction_5_0 = 0; instruction_5_0 <= 63; instruction_5_0 = instruction_5_0 + 1)
		begin	
			alu_op = 2'b00;
			#5;
			alu_op = 2'b01;
			#5;
			alu_op = 2'b10;
			#5;
			alu_op = 2'b11;
		end
		
		
		$finish;
	end
	
	always
		#1 clk = !clk;
      
endmodule

