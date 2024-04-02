`include "cadence.genlib"

module FullAdder (A, B, Cin, C, S);
    input wire A;
    input wire B;
    input wire Cin;
    output wire C;
    output wire S;

    wire C_0;
    wire S_0;
    wire C_1;

    HalfAdder ha_0 (.C(C_0), .S(S_0), .A(A), .B(B)); 
    HalfAdder ha_1 (.C(C_1) , .S(S), .A(S_0), .B(Cin)); 

    OR2X1 or_0 (.Y(C), .A(C_0), .B(C_1));

endmodule

module HalfAdder (C, S, A, B);
    input wire A;
    input wire B;
    output wire C;
    output wire S;

    AND2X1 and_0 (.Y(C), .A(A), .B(B)); 
    XOR2X1 xor_0 (.Y(S), .A(A), .B(B)); 

endmodule
