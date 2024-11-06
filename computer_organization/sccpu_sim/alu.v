`include "ctrl_encode_def.v"

module alu(A, B, ALUOp, C, Zero);
           
   input  signed [31:0] A, B;
   input         [3:0]  ALUOp;
   output signed [31:0] C;
   output Zero;
   
   reg [31:0] C;
   integer    i;
       
   always @( * ) begin
      case ( ALUOp )
          `ALU_NOP:  C = A;                          // NOP 0000
          `ALU_ADD:  C = A + B;                      // ADD 0001
          `ALU_SUB:  C = A - B;                      // SUB 0010
          `ALU_AND:  C = A & B;                      // AND/ANDI 0011
          `ALU_OR:   C = A | B;                      // OR/ORI 0100
          `ALU_SLT:  C = (A < B) ? 32'd1 : 32'd0;    // SLT/SLTI 0101
          `ALU_SLTU: C = ({1'b0, A} < {1'b0, B}) ? 32'd1 : 32'd0; //0110
          `ALU_NOR:  C = ~(A | B);                   // NOR 0111
          `ALU_SLL:  C = B << A;                     // SLL 1000
          `ALU_SRL:  C = B >> A;                     // SRL 1001
          `ALU_LUI:  C = B << 16;                    // LUI 1010
          `ALU_XOR:  C = A ^ B;                      // XOR 1011
          `ALU_SRA:  C = B >>> A;                    // SRA 1100
          `ALU_SLLV: C = B << A[4:0];                // SLLV 1101
          `ALU_SRLV: C = B >> A[4:0];                // SRLV 1110
          `ALU_SRAV: C = B >>> A[4:0];               // SRAV 1111
          default:   C = A;                          // Undefined
      endcase
   end // end always
   
   assign Zero = (C == 32'b0);

endmodule
    
