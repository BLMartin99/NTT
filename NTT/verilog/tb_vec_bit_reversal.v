module tb_vec_bit_reversal();
    reg [63:0] vec_in;
    wire [63:0] vec_out;

vec_bit_reversal uut
    (
     .vec_in(vec_in),
     .vec_out(vec_out)
    );

    initial begin
        vec_in[7:0] = 1;
        vec_in[15:8] = 2;
        vec_in[23:16] = 3;
        vec_in[31:24] = 4;
        vec_in[39:32] = 5;
        vec_in[47:40] = 6;
        vec_in[55:48] = 7;
        vec_in[63:56] = 8;
        #1; $display("vec_out: %d %d %d %d %d %d %d %d | vec_in: %d %d %d %d %d %d %d %d", vec_out[63:56], vec_out[55:48], vec_out[47:40], vec_out[39:32], vec_out[31:24], vec_out[23:16], vec_out[15:8], vec_out[7:0], vec_in[63:56], vec_in[55:48], vec_in[47:40], vec_in[39:32], vec_in[31:24], vec_in[23:16], vec_in[15:8], vec_in[7:0]); #1;   
    end

endmodule
