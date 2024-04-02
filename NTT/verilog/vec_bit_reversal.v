module vec_bit_reversal(vec_in, vec_out);
    input wire [7:0] vec_in [7:0];
    output wire [7:0] vec_out [7:0];

    wire [2:0] num_0;
    wire [2:0] num_1;
    wire [2:0] num_2;
    wire [2:0] num_3;
    wire [2:0] num_4;
    wire [2:0] num_5;
    wire [2:0] num_6;
    wire [2:0] num_7;

    wire [2:0] reverse_0;
    wire [2:0] reverse_1;
    wire [2:0] reverse_2;
    wire [2:0] reverse_3;
    wire [2:0] reverse_4;
    wire [2:0] reverse_5;
    wire [2:0] reverse_6;
    wire [2:0] reverse_7;

    assign num_0 = 3'b000;
    assign num_1 = 3'b001;
    assign num_2 = 3'b010;
    assign num_3 = 3'b011;
    assign num_4 = 3'b100;
    assign num_5 = 3'b101;
    assign num_6 = 3'b110;
    assign num_7 = 3'b111;

    bit_reversal br_0 (.num(num_0), .reverse(reverse_0));
    bit_reversal br_1 (.num(num_1), .reverse(reverse_1));
    bit_reversal br_2 (.num(num_2), .reverse(reverse_2));
    bit_reversal br_3 (.num(num_3), .reverse(reverse_3));
    bit_reversal br_4 (.num(num_4), .reverse(reverse_4));
    bit_reversal br_5 (.num(num_5), .reverse(reverse_5));
    bit_reversal br_6 (.num(num_6), .reverse(reverse_6));
    bit_reversal br_7 (.num(num_7), .reverse(reverse_7));

    assign vec_out[reverse_0] = vec_in[num_0];
    assign vec_out[reverse_1] = vec_in[num_1];
    assign vec_out[reverse_2] = vec_in[num_2];
    assign vec_out[reverse_3] = vec_in[num_3];
    assign vec_out[reverse_4] = vec_in[num_4];
    assign vec_out[reverse_5] = vec_in[num_5];
    assign vec_out[reverse_6] = vec_in[num_6];
    assign vec_out[reverse_7] = vec_in[num_7];

endmodule
