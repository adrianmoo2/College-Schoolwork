`timescale 1ns / 1ps

`define MAX_REG 256
`define WORD_SIZE 32 

module cs161_processor_testbench( );

  // Inputs
  
  reg clk ;
  reg rst ;

  // Outputs
  
  wire [31:0] prog_count  ;
  wire [5:0] instr_opcode ;
  wire [4:0] reg1_addr    ;
  wire [31:0] reg1_data   ;
  wire [4:0] reg2_addr  ;
  wire [31:0] reg2_data ;
  wire [4:0] write_reg_addr ;
  wire [31:0] write_reg_data ;
  wire reg_dst, mem_to_reg, branch, mem_read, mem_write, alu_src, reg_write;
  wire [3:0] ALU_Control ;
  wire [31:0] PC4 ;
  wire beq_control ;
  wire pc_next ;
  wire [31:0] ALU_out ;
  
 cs161_processor uut (
    .clk                 ( clk ),
    .rst                 ( rst ),
    .prog_count          ( prog_count ),
    .instr_opcode        ( instr_opcode ),
    .reg1_addr           ( reg1_addr ),
    .reg1_data           ( reg1_data ),
    .reg2_addr           ( reg2_addr ),
    .reg2_data           ( reg2_data ) ,
    .write_reg_addr      ( write_reg_addr ),
    .write_reg_data      ( write_reg_data ),
	 .reg_dst 				( reg_dst ) ,
	 .mem_to_reg 			( mem_to_reg) ,
	 .branch 				( branch) ,
	 .mem_read 				( mem_read ) ,
	 .mem_write 			( mem_write ),
	 .alu_src 				( alu_src ) ,
	 .reg_write				( reg_write ),
	 .ALU_Control			( ALU_Control) ,
	 .PC4						( PC4 )	,
	 .beq_control			( beq_control ) ,
	 .pc_next				( pc_next ) ,
	 .ALU_out				( ALU_out )
    );
  
  
	/*initial begin
		clk = 0;
		rst = 1;
		#100;
		
		rst = 0;
	 
	 end
	 
	  always
		#10 clk = ~clk;
	*/
	
	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	
	 initial begin 
	 
	 rst = 1 ; 
	 #20 ; 
	 
	 rst = 0;

	end
	
	
endmodule
