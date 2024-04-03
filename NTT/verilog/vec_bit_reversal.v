module vec_bit_reversal
    (
     input wire [63:0] vec_in,
     output wire [63:0] vec_out
    );

    wire [2:0] num_0;

    assign num_0 = 3'b001;

    wire [2:0] rev_0;


    assign vec_out[32] = vec_in[8];
    assign vec_out[33] = vec_in[9];
    assign vec_out[34] = vec_in[10];
    assign vec_out[35] = vec_in[11];
    assign vec_out[36] = vec_in[12];
    assign vec_out[37] = vec_in[13];
    assign vec_out[38] = vec_in[14];
    assign vec_out[39] = vec_in[15];

endmodule
