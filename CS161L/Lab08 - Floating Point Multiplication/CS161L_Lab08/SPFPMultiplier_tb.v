`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   05:51:09 03/13/2019
// Design Name:   SPFPMultipier
// Module Name:   /home/ise/virtualshare/Lab06/CS161L_Lab08/SPFPMultiplier_tb.v
// Project Name:  CS161L_Lab08
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: SPFPMultipier
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module SPFPMultiplier_tb;

	// Inputs
	reg clk;
	reg rst;
	reg enable;
	reg [31:0] A;
	reg [31:0] B;

	// Outputs
	wire valid;
	wire [31:0] result;

	// Instantiate the Unit Under Test (UUT)
	SPFPMultipier uut (
		.clk(clk), 
		.rst(rst), 
		.enable(enable), 
		.valid(valid), 
		.A(A), 
		.B(B), 
		.result(result)
	);

	initial begin 
	 clk = 0; 	
	 rst = 0;
	 
	 #100;
	 
	 rst = 1;
	 clk = 0;
	 
	 #5;
	 
	 rst = 1;
	 clk = 1;
	 
	 #5;
	 
	 rst = 0;
	 clk = 0;
	 
	 enable = 1;
		
	 forever begin 
		#5 clk = ~clk;
	 end 
	 
	end
	
	initial begin
	    
// **************************************************
// We have to write values 
// **************************************************
		
		A = 0;
		B = 0;
		enable = 0;
		
		#100;
		
		#10;
		
		A = 32'h41740000; //15.25
		B = 32'h40300000; //2.75
		//Expect: 32'h4227C000 (41.9375)
		#10;
		
		A = 32'h42C90000; //100.5
		B = 32'h43962000; //300.25
		//Expect: 32'h46EBBE40 (30,175.125)
		#10;
		
		A = 32'hC1800000; //-16
		B = 32'h41800000; //16
		//Expect: 32'hC3800000 (-256)
		#10;
		
		A = 32'hC2488000; //-50.125
		B = 32'hBFC00000; //-1.5
		//Expect: 32'h42966000 (75.1875)
		 #10;
		 
		A = 32'hC2FA4000; //-125.125
		B = 32'hC2FA4000; //-125.125
		//Expect: 32'h4674A110 (15,656.265265)
		#10;
		
		$stop;
		 
		 
	end
      
endmodule


