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
    HalfAdder ha_1 (.C(C_1) , .S(S), .A(S_0), .Cin(Cin)); 

    or or_0 (C, C_0, C_1);

endmodule

module HalfAdder (A, B, C, S);
    input wire A;
    input wire B;
    output wire C;
    output wire S;

    and and_0 (C, A, B); 
    xor xor_0 (S, A, B); 

endmodule
