module FullAdder (A, B, Cin, C, S);
    input wire A;
    input wire B;
    input wire Cin;
    output wire C;
    output wire S;

    wire C_0;
    wire S_0;
    wire C_1;

    HalfAdder ha_0 (.A(A), .B(B), .C(C_0), .S(S_0)); 
    HalfAdder ha_1 (.A(S_0), .B(Cin), .C(C_1) , .S(S)); 

    assign C = C_0 | C_1;

endmodule

module HalfAdder (A, B, C, S);
    input wire A;
    input wire B;
    output wire C;
    output wire S;

    assign C = A & B;
    assign S = A ^ B;

endmodule
