`include "ctrl_encode_def.v"
// data memory
module dm(clk, DMWr, addr, din, dout, DMOp);
    input          clk;
    input          DMWr;
    input  [8:0]   addr;

    input  [31:0]  din;
    input  [2:0]   DMOp;    
    output reg [31:0]  dout;
        
    reg [31:0] dmem[127:0];
    wire [31:0] addrByte_b;
    wire [31:0] addrByte_h;
    wire [31:0] addrByte_w;
    wire  [1:0]Byte_b;
    wire  Byte_h;
    assign Byte_h=addr[1];
    assign Byte_b=addr[1:0];
    assign addrByte_w = addr[8:2]<<2;
    assign addrByte_h = addr[8:1]<<1;
    assign addrByte_b = addr;
    always @( * ) begin
        case(DMOp)
            `DM_LB:  begin 
                if (Byte_b==2'b00) begin
                    dout = {{24{dmem[addrByte_b[8:2]][7]}}, dmem[addrByte_b[8:2]][7:0]};  // {24{dmem[addrByte_b[8:2]][7]}} is used to sign extend
                end else if (Byte_b==2'b01) begin
                    dout = {{24{dmem[addrByte_b[8:2]][15]}}, dmem[addrByte_b[8:2]][15:8]}; 
                end else if(Byte_b==2'b10) begin
                    dout = {{24{dmem[addrByte_b[8:2]][23]}}, dmem[addrByte_b[8:2]][23:16]};
                end else begin
                    dout = {{24{dmem[addrByte_b[8:2]][31]}}, dmem[addrByte_b[8:2]][31:24]}; 
                end
                
                //$display("dmem[0x%8X] = 0x%2X,", addrByte_b[8:2], din[7:0]);
            end   // LB
            `DM_LBU: 
            begin 
                if (Byte_b==2'b00) begin
                    dout = {24'b0, dmem[addrByte_b[8:2]][7:0]}; 
                end else if (Byte_b==2'b01) begin
                    dout = {24'b0, dmem[addrByte_b[8:2]][15:8]}; 
                end else if(Byte_b==2'b10) begin
                    dout = {24'b0, dmem[addrByte_b[8:2]][23:16]};
                end else begin
                    dout = {24'b0, dmem[addrByte_b[8:2]][31:24]}; 
                end
                
                //$display("dmem[0x%8X] = 0x%2X,", addrByte_b[8:2], din[7:0]);
            end
                                    // LBU
            `DM_LH: begin // LH means load halfword
                if(Byte_h==0)begin
                    dout = {{16{dmem[addrByte_h[8:2]][15]}}, dmem[addrByte_h[8:2]][15:0]}; // LH
                end else begin
                    dout = {{16{dmem[addrByte_h[8:2]][31]}}, dmem[addrByte_h[8:2]][31:16]}; // LH
                end
                    
                //$display("dmem[0x%8X] = 0x%4X,", addrByte_h[8:2], din[15:0]); 
            end  
            `DM_LHU: if(Byte_h==0)begin
                    dout = {16'b0, dmem[addrByte_h[8:2]][15:0]}; // LH
                end else begin
                    dout = {16'b0, dmem[addrByte_h[8:2]][31:16]}; // LH
                end
                                     // LHU
            `DM_LW:  dout = dmem[addrByte_w[8:2]];                                        // LW
            default: dout = dmem[addrByte_w[8:2]];                                     // undefined
        endcase
   end
   always @(posedge clk)
      if (DMWr) begin
        case(DMOp)
            `DM_SB: 
            begin 
                if (Byte_b==2'b00) begin
                    dmem[addrByte_b[8:2]][7:0] <= din[7:0]; 
                end else if (Byte_b==2'b01) begin
                    dmem[addrByte_b[8:2]][15:8] <= din[7:0]; 
                end else if(Byte_b==2'b10) begin
                    dmem[addrByte_b[8:2]][23:16] <= din[7:0]; 
                end else begin
                    dmem[addrByte_b[8:2]][31:24] <= din[7:0]; 
                end
                
                //$display("dmem[0x%8X] = 0x%2X,", addrByte_b[8:2], din[7:0]);
            end 
            `DM_SH: 
            begin 
                if(Byte_h==0)begin
                    dmem[addrByte_h[8:2]][15:0] <= din[15:0];
                end else begin
                    dmem[addrByte_h[8:2]][31:16] <= din[15:0];
                end
                    
                //$display("dmem[0x%8X] = 0x%4X,", addrByte_h[8:2], din[15:0]); 
            end 
            `DM_SW: 
            begin 
                dmem[addrByte_w[8:2]] <= din;
                //$display("dmem[0x%8X] = 0x%8X,", addrByte_w[8:2], din);
            end 
            default: begin dmem[addrByte_w[8:2]] <= din;end 
        endcase
        $display("dmem[0x%8X] = 0x%8X,", addrByte_w[8:2], din);
      end
   
endmodule  
