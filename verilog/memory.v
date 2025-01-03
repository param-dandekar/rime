module RAM #(
    parameter DATA_WIDTH = 8,
    parameter ADDR_WIDTH = 8
  ) (
    input clk,
    input WE, // enable writing to memory
    input OE, // enable output
    input [ADDR_WIDTH-1:0] addr_bus,
    inout [DATA_WIDTH-1:0] data_bus
  );

  reg [DATA_WIDTH-1:0] data;
  reg [DATA_WIDTH-1:0] mem;

  initial begin
    mem <= 'b0;
  end

  always @(posedge clk) begin
    data <= data_bus;
    if (WE & ~OE)
      mem <= data;
    if (OE & !WE)
      data = mem;
  end

endmodule

