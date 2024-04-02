`include "cadence.genlib"

module tb_FullAdder ();
    reg A;
    reg B;
    reg Cin;
    wire C;
    wire S;

    integer i;
    integer l;
    integer k;

FullAdder uut 
    (
    .A(A),
    .B(B),
    .Cin(Cin),
    .C(C),
    .S(S)
    );

    initial begin
        for(i = 0; i < 2; i = i + 1) begin
            for(l = 0; l < 2; l = l + 1) begin
                for(k = 0; k < 2; k = k + 1) begin
                    A = i; B = l; Cin = k;
                    #1; $display("A: %b B: $b Cin: %b C: %b S: %b", A, B, Cin, C, S);
                end
            end
        end
    end

endmodule
