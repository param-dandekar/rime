module testbench;

  localparam WIDTH = 8;

  wire clk;
  clock #(2) clk_inst(clk);

  reg [WIDTH-1:0] A, B;
  reg EA, WEA, OEA;
  reg WER, OER;
  wire [WIDTH-1:0] data_bus;
  wire [WIDTH-1:0] addr_bus;

  tristate #(WIDTH) A_buf(A, EA, data_bus);

  reg_buf #(WIDTH) A_reg(clk, WEA, OEA, data_bus);

  RAM #(8, 8) RAM_inst(clk, WER, OER, addr_bus, data_bus);

  initial begin
    $display("Time\t: Ar Mr DB");
    $monitor("%0t\t: %02h %02h %02h",
      $time,
      A_reg.reg_inst.data,
      RAM_inst.mem,
      data_bus);
    EA = 0; WEA = 0; OEA = 0;
    WER = 0; OER = 0;
    #2

    A = 'h0F;
    EA = 1; WEA = 1;
    #2
    WEA = 0;
    OEA = 1;
    WER = 1;
    #2
    WER = 0;

    $finish;
  end

endmodule
