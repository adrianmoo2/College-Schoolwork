`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   03:31:24 02/07/2019
// Design Name:   control_unit
// Module Name:   /home/ise/Desktop/CS161L_LABS/CS161L_LAB03_Redo/control_unit_tb.v
// Project Name:  CS161L_LAB03_Redo
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: control_unit
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module control_unit_tb;

	// Inputs
	reg clk;
	reg reset;
	reg [5:0] instr_op;

	// Outputs
	wire reg_dst;
	wire branch;
	wire mem_read;
	wire mem_to_reg;
	wire [1:0] alu_op;
	wire mem_write;
	wire alu_src;
	wire reg_write;

	// Instantiate the Unit Under Test (UUT)
	control_unit uut (
		.clk(clk), 
		.reset(reset), 
		.instr_op(instr_op), 
		.reg_dst(reg_dst), 
		.branch(branch), 
		.mem_read(mem_read), 
		.mem_to_reg(mem_to_reg), 
		.alu_op(alu_op), 
		.mem_write(mem_write), 
		.alu_src(alu_src), 
		.reg_write(reg_write)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 0;
		instr_op = 0;
	end
	
	initial begin 
		/*instr_op = 6'b000000;
		#10;
		
		instr_op = 6'b100011;
		#10;
		
		instr_op = 6'b101011;
		#10;
		
		instr_op = 6'b000100;
		#10;
		
		instr_op = 6'b001000;
		#10;*/
		
		for (instr_op = 0; instr_op <= 63; instr_op = instr_op + 1)
		#5;
		
		$finish;
	end
	
	always
		#1 clk = !clk;
	
	
      
endmodule

