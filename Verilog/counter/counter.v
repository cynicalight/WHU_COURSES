module counter (clk, rst, en, count);
   input clk, rst, en;
   output reg [4:0] count;
   always @(posedge clk) begin
      if (rst)      //复位信号
         count <= 2'b0;
      else if (en) begin //使能信号
         count <= count + 2'b1;

      // 在每个时钟上升沿打印 count 的值
         $display("count = %b", count);
      end
   end
endmodule
