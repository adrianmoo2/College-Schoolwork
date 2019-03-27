`timescale 1ns / 1ps

module CAM_Row(
    clk,
    rst,
    we,
    search_word,
    dont_care_mask,
	 row_match
    );

    parameter CAM_WIDTH = 8;

    input wire clk, rst, we;
    input wire [CAM_WIDTH-1:0] search_word, dont_care_mask;
    output reg row_match;
	 
//-----Added functionality-----
	wire [CAM_WIDTH-1:0] rowChecker;

STCAM_Cell temp_STCAM ( .clk(clk),
    .rst (rst),
    .we (we),
    .cell_search_bit(),
    .cell_dont_care_bit(),
    .cell_match_bit_in(),
    .cell_match_bit_out());
	 
/*BCAM_Cell temp_BCAM ( .clk(clk),
    .rst (rst),
    .we (we),
    .cell_search_bit(),
    .cell_dont_care_bit(),
    .cell_match_bit_in(),
    .cell_match_bit_out());*/
	
TCAM_Cell temp_TCAM ( .clk(clk),
    .rst (rst),
    .we (we),
    .cell_search_bit(),
    .cell_dont_care_bit(),
    .cell_match_bit_in(),
    .cell_match_bit_out());

genvar index;
generate for (index = 0; index < CAM_WIDTH-1; index = index + 1)
	begin
		if (index > 0) begin
			 BCAM_Cell BCAM_inst( .clk(clk),
			 .rst (rst),
			 .we (we),
			 .cell_search_bit((search_word[index])),
			 .cell_dont_care_bit((dont_care_mask[index])),
			 .cell_match_bit_in(rowChecker[index-1]),
			 .cell_match_bit_out(rowChecker[index]));
		end else begin
			 BCAM_Cell BCAM_inst( .clk(clk),
			 .rst (rst),
			 .we (we),
			 .cell_search_bit((search_word[index])),
			 .cell_dont_care_bit((dont_care_mask[index])),
			 .cell_match_bit_in(1'b1),
			 .cell_match_bit_out(rowChecker[index]));		
		end
	end
endgenerate

always @(posedge clk) begin
row_match <= (rowChecker == 8'b11111111) ? 1'b1: 1'b0;
end

endmodule
