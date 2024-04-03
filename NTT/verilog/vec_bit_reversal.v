module vec_bit_reversal
    (
     input wire [63:0] vec_in,
     output wire [63:0] vec_out
    );

    // 3'b000 --bit reversal--> 3'b000
    assign vec_out[0] = vec_in[0];
    assign vec_out[1] = vec_in[1];
    assign vec_out[2] = vec_in[2];
    assign vec_out[3] = vec_in[3];
    assign vec_out[4] = vec_in[4];
    assign vec_out[5] = vec_in[5];
    assign vec_out[6] = vec_in[6];
    assign vec_out[7] = vec_in[7];

    // 3'b001 --bit reversal--> 3'b100
    assign vec_out[32] = vec_in[8];
    assign vec_out[33] = vec_in[9];
    assign vec_out[34] = vec_in[10];
    assign vec_out[35] = vec_in[11];
    assign vec_out[36] = vec_in[12];
    assign vec_out[37] = vec_in[13];
    assign vec_out[38] = vec_in[14];
    assign vec_out[39] = vec_in[15];

    // 3'b010 --bit reversal--> 3'b010
    assign vec_out[16] = vec_in[16];
    assign vec_out[17] = vec_in[17];
    assign vec_out[18] = vec_in[18];
    assign vec_out[19] = vec_in[19];
    assign vec_out[20] = vec_in[20];
    assign vec_out[21] = vec_in[21];
    assign vec_out[22] = vec_in[22];
    assign vec_out[23] = vec_in[23];

    // 3'b011 --bit reversal--> 3'b110
    assign vec_out[48] = vec_in[24];
    assign vec_out[49] = vec_in[25];
    assign vec_out[50] = vec_in[26];
    assign vec_out[51] = vec_in[27];
    assign vec_out[52] = vec_in[28];
    assign vec_out[53] = vec_in[29];
    assign vec_out[54] = vec_in[30];
    assign vec_out[55] = vec_in[31];

    // 3'b100 --bit reversal--> 3'b001
    assign vec_out[8] = vec_in[32];
    assign vec_out[9] = vec_in[33];
    assign vec_out[10] = vec_in[34];
    assign vec_out[11] = vec_in[35];
    assign vec_out[12] = vec_in[36];
    assign vec_out[13] = vec_in[37];
    assign vec_out[14] = vec_in[38];
    assign vec_out[15] = vec_in[39];

    // 3'b101 --bit reversal--> 3'b101
    assign vec_out[40] = vec_in[40];
    assign vec_out[41] = vec_in[41];
    assign vec_out[42] = vec_in[42];
    assign vec_out[43] = vec_in[43];
    assign vec_out[44] = vec_in[44];
    assign vec_out[45] = vec_in[45];
    assign vec_out[46] = vec_in[46];
    assign vec_out[47] = vec_in[47];

    // 3'b110 --bit reversal--> 3'b011
    assign vec_out[24] = vec_in[48];
    assign vec_out[25] = vec_in[49];
    assign vec_out[26] = vec_in[50];
    assign vec_out[27] = vec_in[51];
    assign vec_out[28] = vec_in[52];
    assign vec_out[29] = vec_in[53];
    assign vec_out[30] = vec_in[54];
    assign vec_out[31] = vec_in[55];

    // 3'b111 --bit reversal--> 3'b111
    assign vec_out[56] = vec_in[56];
    assign vec_out[57] = vec_in[57];
    assign vec_out[58] = vec_in[58];
    assign vec_out[59] = vec_in[59];
    assign vec_out[60] = vec_in[60];
    assign vec_out[61] = vec_in[61];
    assign vec_out[62] = vec_in[62];
    assign vec_out[63] = vec_in[63];

endmodule
