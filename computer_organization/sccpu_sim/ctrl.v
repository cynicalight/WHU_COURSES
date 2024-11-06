module ctrl(Op, Funct, Zero, 
            RegWrite, MemWrite,
            EXTOp, ALUOp, NPCOp, 
            ALUSrc, GPRSel, WDSel,
            AregSel, DMOp
            );
            
   input  [5:0] Op;       // opcode
   input  [5:0] Funct;    // funct
   input        Zero;
   
   output       RegWrite; // control signal for register write
   output       MemWrite; // control signal for memory write
   output       EXTOp;    // control signal to signed extension
   output [3:0] ALUOp;    // ALU opertion
   output [1:0] NPCOp;    // next pc operation
   output       AregSel;  // ALU source for A
   output       ALUSrc;   // ALU source for B

   output [1:0] GPRSel;   // general purpose register selection
   output [1:0] WDSel;    // (register) write data selection

   output [2:0] DMOp; 
   
  // r format
   wire rtype  = ~|Op;
   wire i_add  = rtype& Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]&~Funct[1]&~Funct[0]; // add
   wire i_sub  = rtype& Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]& Funct[1]&~Funct[0]; // sub
   wire i_and  = rtype& Funct[5]&~Funct[4]&~Funct[3]& Funct[2]&~Funct[1]&~Funct[0]; // and
   wire i_or   = rtype& Funct[5]&~Funct[4]&~Funct[3]& Funct[2]&~Funct[1]& Funct[0]; // or
   wire i_slt  = rtype& Funct[5]&~Funct[4]& Funct[3]&~Funct[2]& Funct[1]&~Funct[0]; // slt
   wire i_sltu = rtype& Funct[5]&~Funct[4]& Funct[3]&~Funct[2]& Funct[1]& Funct[0]; // sltu
   wire i_addu = rtype& Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]&~Funct[1]& Funct[0]; // addu
   wire i_subu = rtype& Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]& Funct[1]& Funct[0]; // subu
   
   // newly added
   wire i_sll  = rtype&~Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]&~Funct[1]&~Funct[0]; // sll 000000
   wire i_nor  = rtype& Funct[5]&~Funct[4]&~Funct[3]& Funct[2]& Funct[1]& Funct[0]; // nor 100111
   wire i_srl  = rtype&~Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]& Funct[1]&~Funct[0]; // srl 000010
   wire i_sllv = rtype&~Funct[5]&~Funct[4]&~Funct[3]& Funct[2]&~Funct[1]&~Funct[0]; // sllv 000100
   wire i_srlv = rtype&~Funct[5]&~Funct[4]&~Funct[3]& Funct[2]& Funct[1]&~Funct[0]; // srlv 000110
   wire i_xor  = rtype& Funct[5]&~Funct[4]&~Funct[3]& Funct[2]& Funct[1]&~Funct[0]; // xor 100110
   wire i_sra  = rtype&~Funct[5]&~Funct[4]&~Funct[3]&~Funct[2]& Funct[1]& Funct[0]; // sra 000011
   wire i_srav = rtype&~Funct[5]&~Funct[4]&~Funct[3]& Funct[2]& Funct[1]& Funct[0]; // srav 000111
   wire jr     = rtype&~Funct[5]&~Funct[4]& Funct[3]&~Funct[2]&~Funct[1]&~Funct[0]; // jr 001000
   wire jalr   = rtype&~Funct[5]&~Funct[4]& Funct[3]&~Funct[2]&~Funct[1]& Funct[0]; // jalr 001001

  // i format
   wire i_addi = ~Op[5]&~Op[4]& Op[3]&~Op[2]&~Op[1]&~Op[0]; // addi
   wire i_ori  = ~Op[5]&~Op[4]& Op[3]& Op[2]&~Op[1]& Op[0]; // ori
   wire i_lw   =  Op[5]&~Op[4]&~Op[3]&~Op[2]& Op[1]& Op[0]; // lw
   wire i_sw   =  Op[5]&~Op[4]& Op[3]&~Op[2]& Op[1]& Op[0]; // sw
   wire i_beq  = ~Op[5]&~Op[4]&~Op[3]& Op[2]&~Op[1]&~Op[0]; // beq

   // newly added
   wire i_lui  = ~Op[5]&~Op[4]& Op[3]& Op[2]& Op[1]& Op[0]; // lui 001111
   wire i_slti = ~Op[5]&~Op[4]& Op[3]&~Op[2]& Op[1]&~Op[0]; // slti 001010
   wire i_bne  = ~Op[5]&~Op[4]&~Op[3]& Op[2]&~Op[1]& Op[0]; // bne 000101
   wire i_andi = ~Op[5]&~Op[4]& Op[3]& Op[2]&~Op[1]&~Op[0]; // andi 001100

   wire i_lb   =  Op[5]&~Op[4]&~Op[3]&~Op[2]&~Op[1]&~Op[0]; // lb  100000
   wire i_lh   =  Op[5]&~Op[4]&~Op[3]&~Op[2]&~Op[1]& Op[0]; // lh  100001
   wire i_lbu  =  Op[5]&~Op[4]&~Op[3]& Op[2]&~Op[1]&~Op[0]; // lbu 100100
   wire i_lhu  =  Op[5]&~Op[4]&~Op[3]& Op[2]&~Op[1]& Op[0]; // lhu 100101
   wire i_sb   =  Op[5]&~Op[4]& Op[3]&~Op[2]&~Op[1]&~Op[0]; // sb  101000
   wire i_sh   =  Op[5]&~Op[4]& Op[3]&~Op[2]&~Op[1]& Op[0]; // sh  101001

  // j format
   wire i_j    = ~Op[5]&~Op[4]&~Op[3]&~Op[2]& Op[1]&~Op[0];  // j
   wire i_jal  = ~Op[5]&~Op[4]&~Op[3]&~Op[2]& Op[1]& Op[0];  // jal

  // generate control signals
  assign RegWrite   = rtype | i_lw | i_lb | i_lbu | i_lh | i_lhu | i_jal | i_addi | i_ori | i_lui | i_slti | i_andi; // register write  
  
  assign MemWrite   = i_sw | i_sb | i_sh;   // memory write
  assign AregSel    = i_sll | i_srl | i_sra; //ALU A is from rs or shamt                        
  assign ALUSrc     = i_lw | i_sw | i_addi | i_ori | i_slti | i_lui | i_andi | i_lb | i_lbu | i_lh | i_lhu | i_sb | i_sh;   // ALU B is from instruction immediate
  assign EXTOp      = i_addi | i_lw | i_sw | i_slti | i_lui | i_lb | i_lbu | i_lh | i_lhu | i_sb | i_sh;           // signed extension

  // GPRSel_RD   2'b00
  // GPRSel_RT   2'b01
  // GPRSel_31   2'b10
  assign GPRSel[0] = i_lw | i_addi | i_ori | i_slti | i_lui | i_andi |  i_lb | i_lbu | i_lh | i_lhu;
  assign GPRSel[1] = i_jal;
  
  // WDSel_FromALU 2'b00
  // WDSel_FromMEM 2'b01
  // WDSel_FromPC  2'b10
  assign WDSel[0] = i_lw | i_lb | i_lbu | i_lh | i_lhu;
  assign WDSel[1] = i_jal | jalr;

  // NPC_PLUS4   2'b00
  // NPC_BRANCH  2'b01
  // NPC_JUMP    2'b10
  // NPC_JR      2'b11
  assign NPCOp[0] = (i_beq & Zero) | (i_bne & ~Zero) | jr | jalr;
  assign NPCOp[1] = i_j | i_jal | jr | jalr;
  
  // ALU_NOP   4'b0000 
  // ALU_ADD   4'b0001
  // ALU_SUB   4'b0010 
  // ALU_AND   4'b0011
  // ALU_OR    4'b0100
  // ALU_SLT   4'b0101
  // ALU_SLTU  4'b0110
  // ALU_NOR   4'b0111
  // ALU_SLL   4'b1000
  // ALU_SRL   4'b1001
  // ALU_LUI   4'b1010
  // ALU_XOR   4'b1011
  // ALU_SRA   4'b1100
  // ALU_SLLV  4'b1101
  //ALU_SRLV   4'b1110
  assign ALUOp[0] = i_add | i_lw | i_sw | i_lb | i_lbu | i_lh | i_lhu | i_sb | i_sh | i_addi | i_and | i_andi | i_slt | i_addu | i_nor | i_slti | i_srl  | i_xor|i_sllv| i_srav;
  assign ALUOp[1] = i_sub | i_beq | i_and | i_andi | i_sltu | i_subu | i_bne | i_nor | i_lui | i_xor| i_srlv| i_srav;
  assign ALUOp[2] = i_or | i_ori | i_slt | i_sltu | i_nor | i_slti | i_sra | i_srav|i_sllv| i_srlv;
  assign ALUOp[3] = i_sll | i_sllv | i_srl | i_srlv | i_lui | i_sra | i_srav | i_xor;


 // DM_LW   3'b000
 // DM_LH   3'b001
 // DM_LHU  3'b010
 // DM_LB   3'b011
 // DM_LBU  3'b100
 // DM_SW   3'b101
 // DM_SH   3'b110
 // DM_SB   3'b111
  assign DMOp[0] = i_lh | i_lb | i_sw | i_sb;
  assign DMOp[1] = i_lhu| i_lb | i_sh | i_sb;
  assign DMOp[2] = i_lbu| i_sw | i_sh | i_sb;

endmodule
