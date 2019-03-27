`timescale 1ns / 1ps

module CAM_Array(
    clk,
    rst,
    we_decoded_row_address,
    search_word,
    dont_care_mask,
    decoded_match_address
    );

   parameter CAM_WIDTH = 8;
   parameter CAM_DEPTH = 8;

   input wire clk, rst;
   input wire [CAM_DEPTH-1:0] we_decoded_row_address;
   input wire [CAM_WIDTH-1:0] search_word, dont_care_mask;
   output wire [CAM_DEPTH-1:0] decoded_match_address;

genvar index;
generate for (index = 0; index < CAM_DEPTH-1; index = index + 1)
	begin
		CAM_Row CAM_ROW_inst( .clk(clk),
		 .rst(rst),
		 .we(we_decoded_row_address[index]),
		 .search_word(search_word),
		 .dont_care_mask(dont_care_mask),
		 .row_match(decoded_match_address[index]));
	end
endgenerate	

endmodule
