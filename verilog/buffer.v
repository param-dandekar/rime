module tristate #(parameter WIDTH = 8)( 
    input [WIDTH-1:0] X,
    input E,
    output [WIDTH-1:0] Y
  );

  assign Y = E ? X : 'bz;

endmodule
