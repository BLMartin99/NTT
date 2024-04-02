module bit_reversal(num, reverse);
    input wire [2:0] num;
    output wire [2:0] reverse;

    assign reverse[0] = num[2]; 
    assign reverse[1] = num[1]; 
    assign reverse[2] = num[0]; 

endmodule
