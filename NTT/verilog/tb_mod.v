module tb_mod();
    reg [7:0] x;
    reg [7:0] modulus;
    wire [7:0] x_;
    wire [4:0] x_mod;

mod uut
    (
     .x(x),
     .modulus(modulus),
     .x_(x_),
     .x_mod(x_mod)
    );

    initial begin
        x = -1;
        modulus = 17;
        #1; $display("x: %d modulus: %d x_: %d x_mod: %d", x, modulus, x_, x_mod); #1;
        x = -2;
        modulus = 17;
        #1; $display("x: %d modulus: %d x_: %d x_mod: %d", x, modulus, x_, x_mod); #1;
        x = -3;
        modulus = 17;
        #1; $display("x: %d modulus: %d x_: %d x_mod: %d", x, modulus, x_, x_mod); #1;
        x = 3;
        modulus = 17;
        #1; $display("x: %d modulus: %d x_: %d x_mod: %d", x, modulus, x_, x_mod); #1;
        x = 30;
        modulus = 17;
        #1; $display("x: %d modulus: %d x_: %d x_mod: %d", x, modulus, x_, x_mod); #1;
    end

endmodule
