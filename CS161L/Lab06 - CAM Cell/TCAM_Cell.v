`timescale 1ns / 1ps

module TCAM_Cell(
    input wire clk,
    input wire rst,
    input wire we,
    input wire cell_search_bit,
    input wire cell_dont_care_bit,
    input wire cell_match_bit_in,
    output reg cell_match_bit_out
    );

	 reg stored_bit;
	 
always @(posedge clk or posedge rst)
begin
	if (rst) begin
		if (we)
			stored_bit = cell_search_bit;
	end else begin
		if (((stored_bit == cell_search_bit) || (cell_dont_care_bit)) && (cell_match_bit_in)) begin
			cell_match_bit_out <= 1'b1;
		end else begin
			cell_match_bit_out <= 1'b0;
		end
	end
end

endmodule
