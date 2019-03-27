`timescale 1ns / 1ps

include "cpu_constant_library.v";
`define MAX_REG 256
`define WORD_SIZE 32 

module cs161_processor(
    clk ,
    rst ,   
	 // Debug signals 
    prog_count     , 
    instr_opcode   ,
    reg1_addr      ,
    reg1_data      ,
    reg2_addr      ,
    reg2_data      ,
    write_reg_addr ,
    write_reg_data ,
	 reg_dst ,
	 mem_to_reg ,
	 branch ,
	 mem_read ,
	 mem_write ,
	 alu_src ,
	 reg_write,
	 ALU_Control,
	 PC4,
	 beq_control,
	 pc_next,
	 ALU_out
    );

input wire clk ;
input wire rst ;
    
// Debug Signals

output wire[31:0] prog_count     ; 
output wire[5:0]  instr_opcode   ;
output wire[4:0]  reg1_addr      ;
output wire[31:0] reg1_data      ;
output wire[4:0]  reg2_addr      ;
output wire[31:0] reg2_data      ;
output wire[4:0]  write_reg_addr ;
output wire[31:0] write_reg_data ;
output wire reg_dst, mem_to_reg, branch, mem_read, mem_write, alu_src, reg_write;
output wire [3:0] ALU_Control;
output wire signed [31:0] PC4;
output wire beq_control;
output wire signed [31:0] pc_next;
output wire [31:0] ALU_out;

//-----Added functionalities-----
wire [31:0] instruction;
//
wire [1:0] alu_op, alu_op_EX;
wire [31:0] sign_ext_im, read_data2;
wire [31:0] imm_ext, imm_ext_EX;
wire signed [31:0] im_shift_2;
wire zero_flag, zero_flag_MEM;
wire [31:0] mem_read_data, mem_read_data_WB;
wire signed [31:0] ALU_out_PC, ALU_out_PC_MEM;

wire signed [31:0] pc_next_ID, pc_next_EX;
wire [31:0] instruction_ID;
wire [4:0] instr_15_11, instr_15_11_EX;

wire mem_to_reg_EX, reg_write_EX, mem_write_EX, mem_read_EX,  branch_EX, reg_dst_EX, alu_src_EX;
wire [4:0] reg2_addr_EX;
wire [31:0] reg1_data_EX;
wire [31:0] reg2_data_EX, reg2_data_MEM;

wire mem_to_reg_MEM, reg_write_MEM, mem_write_MEM, mem_read_MEM, branch_MEM;

wire [4:0] write_reg_addr_MEM, write_reg_addr_WB;
wire [31:0] ALU_out_MEM, ALU_out_WB;

wire mem_to_reg_WB, reg_write_WB;


/*
always @ (posedge clk or posedge rst)
begin: CS161_PROCESSOR
	if (rst)
		prog_count <= pc_next;
	else
		prog_count <= pc2;
end
*/

//-----Start of first pipe (IF /ID)-----

mux_2_1 pc_next_mux (.select_in(beq_control), 
.datain1 (PC4), 
.datain2 (ALU_out_PC_MEM), 
.data_out (pc_next));

//PC Reg
gen_register pc_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(pc_next), 
.data_out(prog_count) );

//PC = PC + 4
assign PC4 = prog_count + 32'd4;

//PC Reg
gen_register gen_register_pc_next(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(PC4), 
.data_out(pc_next_ID) );

//Instruction memory (fetch instruction)
cpumemory cpumemory_inst(.clk(clk), 
.rst(rst), 
.instr_read_address(prog_count[9:2]), 
.instr_instruction(instruction));

//Instruction Reg
gen_register gen_register_instruction(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(instruction), 
.data_out(instruction_ID) );


//-----End of first pipe (IF / ID)-----

//-----Start of second pipe (ID / EX)-----
assign instr_opcode = instruction_ID[31:26];

//registers
assign reg1_addr = instruction_ID[25:21];
assign reg2_addr = instruction_ID[20:16];
assign instr_15_11 = instruction_ID[15:11];

//sign extend
assign sign_ext_im = {{16{instruction_ID[15]}}, instruction_ID[15:0]};
assign imm_ext = sign_ext_im;

//control unit
control_unit control_unit_inst(.clk(clk), 
.reset(rst), 
.instr_op(instr_opcode), 
.reg_dst(reg_dst),
.mem_to_reg(mem_to_reg), 
.alu_op(alu_op), 
.branch(branch), 
.mem_read(mem_read), 
.mem_write(mem_write), 
.alu_src(alu_src), 
.reg_write(reg_write));

cpu_registers cpu_registers_inst(.clk(clk), 
.rst(rst),
.write_register(write_reg_addr_WB),
.write_data(write_reg_data),
.reg_write(reg_write_WB),
.read_register_1(reg1_addr),
.read_data_1(reg1_data),
.read_register_2(reg2_addr),
.read_data_2(reg2_data));

gen_register imm_ext_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(imm_ext), 
.data_out(imm_ext_EX) );

gen_register reg1_data_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg1_data), 
.data_out(reg1_data_EX) );

gen_register reg2_data_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg2_data), 
.data_out(reg2_data_EX) );

gen_register reg2_addr_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg2_addr), 
.data_out(reg2_addr_EX) );
 
gen_register instr_15_11_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(instr_15_11), 
.data_out(instr_15_11_EX) );

gen_register pc_next_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(pc_next_ID), 
.data_out(pc_next_EX) );


//-----Start of control signal registers (ID / EX)-----

//WB
gen_register mem_to_reg_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_to_reg), 
.data_out(mem_to_reg_EX) );

gen_register reg_write_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg_write), 
.data_out(reg_write_EX) );

//M
gen_register mem_write_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_write), 
.data_out(mem_write_EX) );

gen_register mem_read_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_read), 
.data_out(mem_read_EX) );

//EX
gen_register reg_dst_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg_dst), 
.data_out(reg_dst_EX) );

gen_register alu_src_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(alu_src), 
.data_out(alu_src_EX) );

gen_register alu_op_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(alu_op), 
.data_out(alu_op_EX) );

gen_register branch_EX_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(branch), 
.data_out(branch_EX) );

//-----End Control Signals registers (ID / EX)-----


//-----ENd of second pipe (ID / EX)-----
//-----Start of third pipe (EX / MEM)-----
 
mux_2_1 write_reg_mux (.select_in(reg_dst_EX), 
.datain1 (reg2_addr_EX), 
.datain2 (instr_15_11_EX), 
.data_out (write_reg_addr));
 
 //alu_control
alu_control alu_control_inst(.clk (clk), 
.reset(rst),
.alu_op(alu_op_EX), 
.instruction_5_0(imm_ext_EX[5:0]), 
.alu_out(ALU_Control));

//mux alu_src
mux_2_1 mux_2_1_inst( .select_in(alu_src_EX), 
.datain1 (reg2_data_EX), 
.datain2 (imm_ext_EX), 
.data_out (read_data2));

//ALU
alu alu_inst( .alu_control_in (ALU_Control),  
.channel_a_in (reg1_data_EX), 
.channel_b_in (read_data2), 
.zero_out (zero_flag) , 
.alu_result_out (ALU_out));

gen_register zero_flag_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(zero_flag), 
.data_out(zero_flag_MEM) );

gen_register alu_out_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(ALU_out), 
.data_out(ALU_out_MEM) );

//immediate shift 2
assign im_shift_2 = imm_ext_EX << 2;

//ALU_PC
assign ALU_out_PC = im_shift_2 + (pc_next_EX);

gen_register reg2_data_MEM_reg(.clk(clk),
.rst(rst),
.write_en(1'b1),
.data_in(reg2_data_EX),
.data_out(reg2_data_MEM));

gen_register ALU_out_PC_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(ALU_out_PC), 
.data_out(ALU_out_PC_MEM) );

gen_register write_reg_addr_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(write_reg_addr), 
.data_out(write_reg_addr_MEM) ); 
 

//Start of control signal registers (EX / MEM)

gen_register mem_to_reg_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_to_reg_EX), 
.data_out(mem_to_reg_MEM) );

gen_register reg_write_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg_write_EX), 
.data_out(reg_write_MEM) );

gen_register mem_write_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_write_EX), 
.data_out(mem_write_MEM) );

gen_register mem_read_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_read_EX), 
.data_out(mem_read_MEM) );

gen_register branch_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(branch_EX), 
.data_out(branch_MEM) );

//End of control signal registers (EX / MEM)

//-----End of third pipe (EX / MEM)-----
//-----Start of fourth pipe (MEM / WB)-----

//Beq control
assign beq_control = branch_MEM & zero_flag_MEM;

cpumemory cpumemory_inst_datamem(
.clk(clk),
.rst(rst),
.data_mem_write (mem_write_MEM), 
.data_address (ALU_out_MEM), 
.data_write_data(reg2_data_MEM), 
.data_read_data (mem_read_data));

gen_register ALU_out_MEM_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(ALU_out_MEM), 
.data_out(ALU_out_WB) );

gen_register mem_read_data_WB_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_read_data), 
.data_out(mem_read_data_WB) );

gen_register write_reg_addr_WB_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(write_reg_addr_MEM), 
.data_out(write_reg_addr_WB) );

//Start of control signals (MEM / WB)

gen_register mem_to_reg_WB_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(mem_to_reg_MEM), 
.data_out(mem_to_reg_WB) );

gen_register reg_write_WB_reg(.clk(clk), 
.rst(rst), 
.write_en(1'b1), 	
.data_in(reg_write_MEM), 
.data_out(reg_write_WB) );

//End of control signals (MEM / WB)

//-----End of fourth pipe (MEM / WB)-----
//Start of fifth pipe

//writeback mux
mux_2_1 mux_2_1_writeback( .select_in(mem_to_reg_WB), 
.datain1 (mem_read_data_WB), 
.datain2 (ALU_out_WB), 
.data_out (write_reg_data));


//End of fifth pipe


endmodule