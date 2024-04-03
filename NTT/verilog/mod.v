module mod
    (
     input wire [7:0] x,
     input wire [7:0] modulus,
     output wire [7:0] x_,
     output wire [4:0] x_mod
    );

    // Two's comp
    assign x_ = (x[7] == 1) ? modulus + x : x;

    assign x_mod = x_ % modulus;
endmodule
