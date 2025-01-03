module register #(parameter WIDTH = 8) (
    input  clk,
    input  E, // enable writing to register
    input  [WIDTH-1:0] in,
    output reg [WIDTH-1:0] data
  );

  initial begin
    data <= 'b0;
  end

  always @(posedge clk) begin
    if (E)
      data <= in;
  end

endmodule

module reg_buf #(parameter WIDTH = 8) (
    input  clk,
    input  WE,
    input  OE, // enable register output
    inout  [WIDTH-1:0] bus
  );

  wire [WIDTH-1:0] internal;
  register #(WIDTH) reg_inst(clk, WE, bus, internal);
  tristate #(WIDTH) buf_inst(internal, OE, bus);

endmodule


