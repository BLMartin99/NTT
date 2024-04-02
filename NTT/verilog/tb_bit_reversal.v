module tb_bit_reversal();
    reg [2:0] num;
    wire [2:0] reverse;

    integer i;

bit_reversal uut
    (
     .num(num),
     .reverse(reverse)
    );

    initial begin
        for(i = 0; i <= 7; i = i + 1) begin
            num = i;
            #1; $display("num: %b reverse: %b", num, reverse); #1;
        end
    end

endmodule
