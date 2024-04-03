module bit_reversal (num, reverse);
    input wire [2:0] num;
    output wire [2:0] reverse;

    assign reverse = {num[0], num[1], num[2]}; 

endmodule
