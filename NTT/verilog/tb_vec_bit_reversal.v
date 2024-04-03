module vec_bit_reversal();
    wire [7:0] vec_in [7:0];
    wire [7:0] vec_out [7:0];

vec_bit_reversal uut
    (
     .vec_in(vec_in),
     .vec_out(vec_out)
    );

    initial begin
        vec_in[0] = 1;
        vec_in[1] = 2;
        vec_in[2] = 3;
        vec_in[3] = 4;
        vec_in[4] = 5;
        vec_in[5] = 6;
        vec_in[6] = 7;
        vec_in[7] = 8;
        #1; $display("vec_in: %d %d %d %d %d %d %d %d vec_out: %d %d %d %d %d %d %d %d", vec_in[0], vec_in[1], vec_in[2], vec_in[3], vec_in[4], vec_in[5], vec_in[6], vec_in[7], vec_out[0], vec_out[1], vec_out[2], vec_out[3], vec_out[4], vec_out[5], vec_out[6], vec_out[7]); #1;
    end

endmodule
