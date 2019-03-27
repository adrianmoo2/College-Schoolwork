`timescale 1ns / 1ps

module CAM_Wrapper (

      input wire clk , 
      input wire rst , 
      input wire [CAM_DEPTH-1 : 0]  we_decoded_row_address , 
      input wire [CAM_WIDTH-1 : 0]  search_word , 
      input wire [CAM_WIDTH-1 : 0]  dont_care_mask , 
      output wire [CAM_WIDTH-1 : 0] decoded_match_address 
		
    );

parameter CAM_DEPTH = 8 ;
parameter CAM_WIDTH = 8 ;

reg rst_buffered ; 
reg[CAM_DEPTH-1 : 0] we_decoded_row_address_buffered ;

reg[CAM_WIDTH-1 : 0] search_word_buffered ;
reg[CAM_WIDTH-1 : 0] dont_care_mask_buffered ; 

wire[CAM_DEPTH-1 : 0] decoded_match_address_sig ;  
reg [CAM_DEPTH-1 : 0] decoded_match_address_buffered ;  

CAM_Array CAM_Array_inst(
    .clk(clk),
    .rst(rst),
    .we_decoded_row_address(we_decoded_row_address),
    .search_word(search_word),
    .dont_care_mask(dont_care_mask),
    .decoded_match_address(decoded_match_address));

endmodule
