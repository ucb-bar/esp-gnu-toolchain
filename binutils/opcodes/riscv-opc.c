/* RISC-V opcode list
   Copyright 2011-2014 Free Software Foundation, Inc.

   Contributed by Andrew Waterman (waterman@cs.berkeley.edu) at UC Berkeley.
   Based on MIPS target.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "opcode/riscv.h"
#include <stdio.h>

/* Register names used by gas and objdump.  */

const char * const riscv_gpr_names_numeric[32] =
{
  "x0",   "x1",   "x2",   "x3",   "x4",   "x5",   "x6",   "x7",
  "x8",   "x9",   "x10",  "x11",  "x12",  "x13",  "x14",  "x15",
  "x16",  "x17",  "x18",  "x19",  "x20",  "x21",  "x22",  "x23",
  "x24",  "x25",  "x26",  "x27",  "x28",  "x29",  "x30",  "x31"
};

const char * const riscv_gpr_names_abi[32] = {
  "zero", "ra", "sp",  "gp",  "tp", "t0",  "t1",  "t2",
  "s0",   "s1", "a0",  "a1",  "a2", "a3",  "a4",  "a5",
  "a6",   "a7", "s2",  "s3",  "s4", "s5",  "s6",  "s7",
  "s8",   "s9", "s10", "s11", "t3", "t4",  "t5",  "t6"
};

const char * const riscv_fpr_names_numeric[32] =
{
  "f0",   "f1",   "f2",   "f3",   "f4",   "f5",   "f6",   "f7",
  "f8",   "f9",   "f10",  "f11",  "f12",  "f13",  "f14",  "f15",
  "f16",  "f17",  "f18",  "f19",  "f20",  "f21",  "f22",  "f23",
  "f24",  "f25",  "f26",  "f27",  "f28",  "f29",  "f30",  "f31"
};

const char * const riscv_fpr_names_abi[32] = {
  "ft0", "ft1", "ft2",  "ft3",  "ft4", "ft5", "ft6",  "ft7",
  "fs0", "fs1", "fa0",  "fa1",  "fa2", "fa3", "fa4",  "fa5",
  "fa6", "fa7", "fs2",  "fs3",  "fs4", "fs5", "fs6",  "fs7",
  "fs8", "fs9", "fs10", "fs11", "ft8", "ft9", "ft10", "ft11"
};

const char * const riscv_vec_gpr_names[256] =
{
 "vv0",  "vv1",  "vv2",  "vv3",  "vv4",  "vv5",  "vv6",  "vv7",
 "vv8",  "vv9",  "vv10",  "vv11",  "vv12",  "vv13",  "vv14",  "vv15",
 "vv16",  "vv17",  "vv18",  "vv19",  "vv20",  "vv21",  "vv22",  "vv23",
 "vv24",  "vv25",  "vv26",  "vv27",  "vv28",  "vv29",  "vv30",  "vv31",
 "vv32",  "vv33",  "vv34",  "vv35",  "vv36",  "vv37",  "vv38",  "vv39",
 "vv40",  "vv41",  "vv42",  "vv43",  "vv44",  "vv45",  "vv46",  "vv47",
 "vv48",  "vv49",  "vv50",  "vv51",  "vv52",  "vv53",  "vv54",  "vv55",
 "vv56",  "vv57",  "vv58",  "vv59",  "vv60",  "vv61",  "vv62",  "vv63",
 "vv64",  "vv65",  "vv66",  "vv67",  "vv68",  "vv69",  "vv70",  "vv71",
 "vv72",  "vv73",  "vv74",  "vv75",  "vv76",  "vv77",  "vv78",  "vv79",
 "vv80",  "vv81",  "vv82",  "vv83",  "vv84",  "vv85",  "vv86",  "vv87",
 "vv88",  "vv89",  "vv90",  "vv91",  "vv92",  "vv93",  "vv94",  "vv95",
 "vv96",  "vv97",  "vv98",  "vv99", "vv100", "vv101", "vv102", "vv103",
 "vv104", "vv105", "vv106", "vv107", "vv108", "vv109", "vv110", "vv111",
 "vv112", "vv113", "vv114", "vv115", "vv116", "vv117", "vv118", "vv119",
 "vv120", "vv121", "vv122", "vv123", "vv124", "vv125", "vv126", "vv127",
 "vv128", "vv129", "vv130", "vv131", "vv132", "vv133", "vv134", "vv135",
 "vv136", "vv137", "vv138", "vv139", "vv140", "vv141", "vv142", "vv143",
 "vv144", "vv145", "vv146", "vv147", "vv148", "vv149", "vv150", "vv151",
 "vv152", "vv153", "vv154", "vv155", "vv156", "vv157", "vv158", "vv159",
 "vv160", "vv161", "vv162", "vv163", "vv164", "vv165", "vv166", "vv167",
 "vv168", "vv169", "vv170", "vv171", "vv172", "vv173", "vv174", "vv175",
 "vv176", "vv177", "vv178", "vv179", "vv180", "vv181", "vv182", "vv183",
 "vv184", "vv185", "vv186", "vv187", "vv188", "vv189", "vv190", "vv191",
 "vv192", "vv193", "vv194", "vv195", "vv196", "vv197", "vv198", "vv199",
 "vv200", "vv201", "vv202", "vv203", "vv204", "vv205", "vv206", "vv207",
 "vv208", "vv209", "vv210", "vv211", "vv212", "vv213", "vv214", "vv215",
 "vv216", "vv217", "vv218", "vv219", "vv220", "vv221", "vv222", "vv223",
 "vv224", "vv225", "vv226", "vv227", "vv228", "vv229", "vv230", "vv231",
 "vv232", "vv233", "vv234", "vv235", "vv236", "vv237", "vv238", "vv239",
 "vv240", "vv241", "vv242", "vv243", "vv244", "vv245", "vv246", "vv247",
 "vv248", "vv249", "vv250", "vv251", "vv252", "vv253", "vv254", "vv255"
};

const char * const riscv_vec_spr_names[256] =
{
 "vs0",  "vs1",  "vs2",  "vs3",  "vs4",  "vs5",  "vs6",  "vs7",
 "vs8",  "vs9",  "vs10",  "vs11",  "vs12",  "vs13",  "vs14",  "vs15",
 "vs16",  "vs17",  "vs18",  "vs19",  "vs20",  "vs21",  "vs22",  "vs23",
 "vs24",  "vs25",  "vs26",  "vs27",  "vs28",  "vs29",  "vs30",  "vs31",
 "vs32",  "vs33",  "vs34",  "vs35",  "vs36",  "vs37",  "vs38",  "vs39",
 "vs40",  "vs41",  "vs42",  "vs43",  "vs44",  "vs45",  "vs46",  "vs47",
 "vs48",  "vs49",  "vs50",  "vs51",  "vs52",  "vs53",  "vs54",  "vs55",
 "vs56",  "vs57",  "vs58",  "vs59",  "vs60",  "vs61",  "vs62",  "vs63",
 "vs64",  "vs65",  "vs66",  "vs67",  "vs68",  "vs69",  "vs70",  "vs71",
 "vs72",  "vs73",  "vs74",  "vs75",  "vs76",  "vs77",  "vs78",  "vs79",
 "vs80",  "vs81",  "vs82",  "vs83",  "vs84",  "vs85",  "vs86",  "vs87",
 "vs88",  "vs89",  "vs90",  "vs91",  "vs92",  "vs93",  "vs94",  "vs95",
 "vs96",  "vs97",  "vs98",  "vs99", "vs100", "vs101", "vs102", "vs103",
 "vs104", "vs105", "vs106", "vs107", "vs108", "vs109", "vs110", "vs111",
 "vs112", "vs113", "vs114", "vs115", "vs116", "vs117", "vs118", "vs119",
 "vs120", "vs121", "vs122", "vs123", "vs124", "vs125", "vs126", "vs127",
 "vs128", "vs129", "vs130", "vs131", "vs132", "vs133", "vs134", "vs135",
 "vs136", "vs137", "vs138", "vs139", "vs140", "vs141", "vs142", "vs143",
 "vs144", "vs145", "vs146", "vs147", "vs148", "vs149", "vs150", "vs151",
 "vs152", "vs153", "vs154", "vs155", "vs156", "vs157", "vs158", "vs159",
 "vs160", "vs161", "vs162", "vs163", "vs164", "vs165", "vs166", "vs167",
 "vs168", "vs169", "vs170", "vs171", "vs172", "vs173", "vs174", "vs175",
 "vs176", "vs177", "vs178", "vs179", "vs180", "vs181", "vs182", "vs183",
 "vs184", "vs185", "vs186", "vs187", "vs188", "vs189", "vs190", "vs191",
 "vs192", "vs193", "vs194", "vs195", "vs196", "vs197", "vs198", "vs199",
 "vs200", "vs201", "vs202", "vs203", "vs204", "vs205", "vs206", "vs207",
 "vs208", "vs209", "vs210", "vs211", "vs212", "vs213", "vs214", "vs215",
 "vs216", "vs217", "vs218", "vs219", "vs220", "vs221", "vs222", "vs223",
 "vs224", "vs225", "vs226", "vs227", "vs228", "vs229", "vs230", "vs231",
 "vs232", "vs233", "vs234", "vs235", "vs236", "vs237", "vs238", "vs239",
 "vs240", "vs241", "vs242", "vs243", "vs244", "vs245", "vs246", "vs247",
 "vs248", "vs249", "vs250", "vs251", "vs252", "vs253", "vs254", "vs255"
};

const char * const riscv_vec_apr_names[32] =
{
  "va0",   "va1",   "va2",   "va3",   "va4",   "va5",   "va6",   "va7",
  "va8",   "va9",   "va10",  "va11",  "va12",  "va13",  "va14",  "va15",
  "va16",  "va17",  "va18",  "va19",  "va20",  "va21",  "va22",  "va23",
  "va24",  "va25",  "va26",  "va27",  "va28",  "va29",  "va30",  "va31"
};

const char * const riscv_vec_ppr_names[16] =
{
  "vp0",   "vp1",   "vp2",   "vp3",   "vp4",   "vp5",   "vp6",   "vp7",
  "vp8",   "vp9",   "vp10",  "vp11",  "vp12",  "vp13",  "vp14",  "vp15"
};

/* The order of overloaded instructions matters.  Label arguments and
   register arguments look the same. Instructions that can have either
   for arguments must apear in the correct order in this table for the
   assembler to pick the right one. In other words, entries with
   immediate operands must apear after the same instruction with
   registers.

   Because of the lookup algorithm used, entries with the same opcode
   name must be contiguous. */

#define WR_xd INSN_WRITE_GPR_D
#define WR_fd INSN_WRITE_FPR_D
#define RD_xs1 INSN_READ_GPR_S
#define RD_xs2 INSN_READ_GPR_T
#define RD_fs1 INSN_READ_FPR_S
#define RD_fs2 INSN_READ_FPR_T
#define RD_fs3 INSN_READ_FPR_R

#define MASK_RS1 (OP_MASK_RS1 << OP_SH_RS1)
#define MASK_RS2 (OP_MASK_RS2 << OP_SH_RS2)
#define MASK_RD (OP_MASK_RD << OP_SH_RD)
#define MASK_IMM ENCODE_ITYPE_IMM(-1U)
#define MASK_UIMM ENCODE_UTYPE_IMM(-1U)
#define MASK_RM (OP_MASK_RM << OP_SH_RM)
#define MASK_PRED (OP_MASK_PRED << OP_SH_PRED)
#define MASK_SUCC (OP_MASK_SUCC << OP_SH_SUCC)
#define MASK_AQ (OP_MASK_AQ << OP_SH_AQ)
#define MASK_RL (OP_MASK_RL << OP_SH_RL)
#define MASK_AQRL (MASK_AQ | MASK_RL)

#define MASK_VRD (OP_MASK_VRD << OP_SH_VRD)
#define MASK_VRS1 (OP_MASK_VRS << OP_SH_VRS)
#define MASK_VRS2 ((insn_t)OP_MASK_VRT << OP_SH_VRT)
#define MASK_VIMM ENCODE_ITYPE_VIMM(-1U)
#define MASK_VRM ((insn_t)OP_MASK_VRM << OP_SH_VRM)
#define MASK_VAQ ((insn_t)OP_MASK_VAQ << OP_SH_VAQ)
#define MASK_VRL ((insn_t)OP_MASK_VRL << OP_SH_VRL)
#define MASK_VAQRL (MASK_VAQ | MASK_VRL)
#define MASK_VPRED ((insn_t)OP_MASK_VPRED << OP_SH_VPRED)
#define MASK_VN ((insn_t)OP_MASK_VN << OP_SH_VN)
#define MASK_VPREV (OP_MASK_VPREV << OP_SH_VPREV)
#define MASK_VSUCC (OP_MASK_VSUCC << OP_SH_VSUCC)

static int match_opcode(const struct riscv_opcode *op, insn_t insn)
{
  return (insn & op->mask) == op->match;
}

static int match_never(const struct riscv_opcode *op ATTRIBUTE_UNUSED,
		       insn_t insn ATTRIBUTE_UNUSED)
{
  return 0;
}

static int match_rs1_eq_rs2(const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode(op, insn) &&
    ((insn & MASK_RS1) >> OP_SH_RS1) == ((insn & MASK_RS2) >> OP_SH_RS2);
}

const struct riscv_opcode riscv_builtin_opcodes[] =
{
/* These instructions appear first so that the disassembler will find
   them first.  The assemblers uses a hash table based on the
   instruction name anyhow.  */
/* name,      isa,   operands, match, mask, pinfo */
{"unimp",     "I",   "",         0, 0xffff,  match_opcode, 0 },
{"nop",       "I",   "",         MATCH_ADDI, MASK_ADDI | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode,  INSN_ALIAS },
{"li",        "I",   "d,j",      MATCH_ADDI, MASK_ADDI | MASK_RS1, match_opcode,  INSN_ALIAS|WR_xd }, /* addi */
{"li",        "I",   "d,I",  0,    (int) M_LI,  match_never, INSN_MACRO },
{"mv",        "I",   "d,s",  MATCH_ADDI, MASK_ADDI | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"move",      "I",   "d,s",  MATCH_ADDI, MASK_ADDI | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"andi",      "I",   "d,s,j",  MATCH_ANDI, MASK_ANDI, match_opcode,   WR_xd|RD_xs1 },
{"and",       "I",   "d,s,t",  MATCH_AND, MASK_AND, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"and",       "I",   "d,s,j",  MATCH_ANDI, MASK_ANDI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"beqz",      "I",   "s,p",  MATCH_BEQ, MASK_BEQ | MASK_RS2, match_opcode,   INSN_ALIAS|RD_xs1 },
{"beq",       "I",   "s,t,p",  MATCH_BEQ, MASK_BEQ, match_opcode,   RD_xs1|RD_xs2 },
{"blez",      "I",   "t,p",  MATCH_BGE, MASK_BGE | MASK_RS1, match_opcode,   INSN_ALIAS|RD_xs2 },
{"bgez",      "I",   "s,p",  MATCH_BGE, MASK_BGE | MASK_RS2, match_opcode,   INSN_ALIAS|RD_xs1 },
{"ble",       "I",   "t,s,p",  MATCH_BGE, MASK_BGE, match_opcode,   INSN_ALIAS|RD_xs1|RD_xs2 },
{"bleu",      "I",   "t,s,p",  MATCH_BGEU, MASK_BGEU, match_opcode,   INSN_ALIAS|RD_xs1|RD_xs2 },
{"bge",       "I",   "s,t,p",  MATCH_BGE, MASK_BGE, match_opcode,   RD_xs1|RD_xs2 },
{"bgeu",      "I",   "s,t,p",  MATCH_BGEU, MASK_BGEU, match_opcode,   RD_xs1|RD_xs2 },
{"bltz",      "I",   "s,p",  MATCH_BLT, MASK_BLT | MASK_RS2, match_opcode,   INSN_ALIAS|RD_xs1 },
{"bgtz",      "I",   "t,p",  MATCH_BLT, MASK_BLT | MASK_RS1, match_opcode,   INSN_ALIAS|RD_xs2 },
{"blt",       "I",   "s,t,p",  MATCH_BLT, MASK_BLT, match_opcode,   RD_xs1|RD_xs2 },
{"bltu",      "I",   "s,t,p",  MATCH_BLTU, MASK_BLTU, match_opcode,   RD_xs1|RD_xs2 },
{"bgt",       "I",   "t,s,p",  MATCH_BLT, MASK_BLT, match_opcode,   INSN_ALIAS|RD_xs1|RD_xs2 },
{"bgtu",      "I",   "t,s,p",  MATCH_BLTU, MASK_BLTU, match_opcode,   INSN_ALIAS|RD_xs1|RD_xs2 },
{"bnez",      "I",   "s,p",  MATCH_BNE, MASK_BNE | MASK_RS2, match_opcode,   INSN_ALIAS|RD_xs1 },
{"bne",       "I",   "s,t,p",  MATCH_BNE, MASK_BNE, match_opcode,   RD_xs1|RD_xs2 },
{"addi",      "I",   "d,s,j",  MATCH_ADDI, MASK_ADDI, match_opcode,  WR_xd|RD_xs1 },
{"add",       "I",   "d,s,t",  MATCH_ADD, MASK_ADD, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"add",       "I",   "d,s,t,0",MATCH_ADD, MASK_ADD, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"add",       "I",   "d,s,j",  MATCH_ADDI, MASK_ADDI, match_opcode,  INSN_ALIAS|WR_xd|RD_xs1 },
{"la",        "I",   "d,A",  0,    (int) M_LA,  match_never, INSN_MACRO },
{"lla",       "I",   "d,A",  0,    (int) M_LLA,  match_never, INSN_MACRO },
{"la.tls.gd", "I",   "d,A",  0,    (int) M_LA_TLS_GD,  match_never, INSN_MACRO },
{"la.tls.ie", "I",   "d,A",  0,    (int) M_LA_TLS_IE,  match_never, INSN_MACRO },
{"neg",       "I",   "d,t",  MATCH_SUB, MASK_SUB | MASK_RS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 }, /* sub 0 */
{"slli",      "I",   "d,s,>",   MATCH_SLLI, MASK_SLLI, match_opcode,   WR_xd|RD_xs1 },
{"sll",       "I",   "d,s,t",   MATCH_SLL, MASK_SLL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"sll",       "I",   "d,s,>",   MATCH_SLLI, MASK_SLLI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"srli",      "I",   "d,s,>",   MATCH_SRLI, MASK_SRLI, match_opcode,   WR_xd|RD_xs1 },
{"srl",       "I",   "d,s,t",   MATCH_SRL, MASK_SRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"srl",       "I",   "d,s,>",   MATCH_SRLI, MASK_SRLI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"srai",      "I",   "d,s,>",   MATCH_SRAI, MASK_SRAI, match_opcode,   WR_xd|RD_xs1 },
{"sra",       "I",   "d,s,t",   MATCH_SRA, MASK_SRA, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"sra",       "I",   "d,s,>",   MATCH_SRAI, MASK_SRAI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"sub",       "I",   "d,s,t",  MATCH_SUB, MASK_SUB, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"ret",       "I",   "",  MATCH_JALR | (X_RA << OP_SH_RS1), MASK_JALR | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"j",         "I",   "a",  MATCH_JAL, MASK_JAL | MASK_RD, match_opcode,   INSN_ALIAS },
{"jal",       "I",   "a",  MATCH_JAL | (X_RA << OP_SH_RD), MASK_JAL | MASK_RD, match_opcode,   INSN_ALIAS|WR_xd },
{"jal",       "I",   "d,a",  MATCH_JAL, MASK_JAL, match_opcode,   WR_xd },
{"call",      "I",   "c", (X_T0 << OP_SH_RS1) | (X_RA << OP_SH_RD), (int) M_CALL,  match_never, INSN_MACRO },
{"tail",      "I",   "c", (X_T0 << OP_SH_RS1), (int) M_CALL,  match_never, INSN_MACRO },
{"jump",      "I",   "c,s", 0, (int) M_CALL,  match_never, INSN_MACRO },
{"jr",        "I",   "s",  MATCH_JALR, MASK_JALR | MASK_RD | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"jr",        "I",   "s,j",  MATCH_JALR, MASK_JALR | MASK_RD, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"jalr",      "I",   "s",  MATCH_JALR | (X_RA << OP_SH_RD), MASK_JALR | MASK_RD | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"jalr",      "I",   "s,j",  MATCH_JALR | (X_RA << OP_SH_RD), MASK_JALR | MASK_RD, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"jalr",      "I",   "d,s",  MATCH_JALR, MASK_JALR | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"jalr",      "I",   "d,s,j",  MATCH_JALR, MASK_JALR, match_opcode,   WR_xd|RD_xs1 },
{"lb",        "I",   "d,o(s)",  MATCH_LB, MASK_LB, match_opcode,   WR_xd|RD_xs1 },
{"lb",        "I",   "d,A",  0, (int) M_LB, match_never, INSN_MACRO },
{"lbu",       "I",   "d,o(s)",  MATCH_LBU, MASK_LBU, match_opcode,   WR_xd|RD_xs1 },
{"lbu",       "I",   "d,A",  0, (int) M_LBU, match_never, INSN_MACRO },
{"lh",        "I",   "d,o(s)",  MATCH_LH, MASK_LH, match_opcode,   WR_xd|RD_xs1 },
{"lh",        "I",   "d,A",  0, (int) M_LH, match_never, INSN_MACRO },
{"lhu",       "I",   "d,o(s)",  MATCH_LHU, MASK_LHU, match_opcode,   WR_xd|RD_xs1 },
{"lhu",       "I",   "d,A",  0, (int) M_LHU, match_never, INSN_MACRO },
{"lw",        "I",   "d,o(s)",  MATCH_LW, MASK_LW, match_opcode,   WR_xd|RD_xs1 },
{"lw",        "I",   "d,A",  0, (int) M_LW, match_never, INSN_MACRO },
{"lui",       "I",   "d,u",  MATCH_LUI, MASK_LUI, match_opcode,   WR_xd },
{"not",       "I",   "d,s",  MATCH_XORI | MASK_IMM, MASK_XORI | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"ori",       "I",   "d,s,j",  MATCH_ORI, MASK_ORI, match_opcode,   WR_xd|RD_xs1 },
{"or",        "I",   "d,s,t",  MATCH_OR, MASK_OR, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"or",        "I",   "d,s,j",  MATCH_ORI, MASK_ORI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"auipc",     "I",   "d,u",  MATCH_AUIPC, MASK_AUIPC, match_opcode,  WR_xd },
{"seqz",      "I",   "d,s",  MATCH_SLTIU | ENCODE_ITYPE_IMM(1), MASK_SLTIU | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"snez",      "I",   "d,t",  MATCH_SLTU, MASK_SLTU | MASK_RS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 },
{"sltz",      "I",   "d,s",  MATCH_SLT, MASK_SLT | MASK_RS2, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"sgtz",      "I",   "d,t",  MATCH_SLT, MASK_SLT | MASK_RS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 },
{"slti",      "I",   "d,s,j",  MATCH_SLTI, MASK_SLTI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"slt",       "I",   "d,s,t",  MATCH_SLT, MASK_SLT, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"slt",       "I",   "d,s,j",  MATCH_SLTI, MASK_SLTI, match_opcode,   WR_xd|RD_xs1 },
{"sltiu",     "I",   "d,s,j",  MATCH_SLTIU, MASK_SLTIU, match_opcode,   WR_xd|RD_xs1 },
{"sltu",      "I",   "d,s,t",  MATCH_SLTU, MASK_SLTU, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"sltu",      "I",   "d,s,j",  MATCH_SLTIU, MASK_SLTIU, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"sgt",       "I",   "d,t,s",  MATCH_SLT, MASK_SLT, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1|RD_xs2 },
{"sgtu",      "I",   "d,t,s",  MATCH_SLTU, MASK_SLTU, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1|RD_xs2 },
{"sb",        "I",   "t,q(s)",  MATCH_SB, MASK_SB, match_opcode,   RD_xs1|RD_xs2 },
{"sb",        "I",   "t,A,s",  0, (int) M_SB, match_never,  INSN_MACRO },
{"sh",        "I",   "t,q(s)",  MATCH_SH, MASK_SH, match_opcode,   RD_xs1|RD_xs2 },
{"sh",        "I",   "t,A,s",  0, (int) M_SH, match_never,  INSN_MACRO },
{"sw",        "I",   "t,q(s)",  MATCH_SW, MASK_SW, match_opcode,   RD_xs1|RD_xs2 },
{"sw",        "I",   "t,A,s",  0, (int) M_SW, match_never,  INSN_MACRO },
{"fence",     "I",   "",  MATCH_FENCE | MASK_PRED | MASK_SUCC, MASK_FENCE | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode,   INSN_ALIAS },
{"fence",     "I",   "P,Q",  MATCH_FENCE, MASK_FENCE | MASK_RD | MASK_RS1 | (MASK_IMM & ~MASK_PRED & ~MASK_SUCC), match_opcode,   0 },
{"fence.i",   "I",   "",  MATCH_FENCE_I, MASK_FENCE | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode,   0 },
{"rdcycle",   "I",   "d",  MATCH_RDCYCLE, MASK_RDCYCLE, match_opcode,  WR_xd },
{"rdinstret", "I",   "d",  MATCH_RDINSTRET, MASK_RDINSTRET, match_opcode,  WR_xd },
{"rdtime",    "I",   "d",  MATCH_RDTIME, MASK_RDTIME, match_opcode,  WR_xd },
{"rdcycleh",  "32I", "d",  MATCH_RDCYCLEH, MASK_RDCYCLEH, match_opcode,  WR_xd },
{"rdinstreth","32I", "d",  MATCH_RDINSTRETH, MASK_RDINSTRETH, match_opcode,  WR_xd },
{"rdtimeh",   "32I", "d",  MATCH_RDTIMEH, MASK_RDTIMEH, match_opcode,  WR_xd },
{"sbreak",    "I",   "",    MATCH_SBREAK, MASK_SBREAK, match_opcode,   0 },
{"scall",     "I",   "",    MATCH_SCALL, MASK_SCALL, match_opcode,   0 },
{"ecall",     "I",   "",    MATCH_SCALL, MASK_SCALL, match_opcode,   0 },
{"xori",      "I",   "d,s,j",  MATCH_XORI, MASK_XORI, match_opcode,   WR_xd|RD_xs1 },
{"xor",       "I",   "d,s,t",  MATCH_XOR, MASK_XOR, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"xor",       "I",   "d,s,j",  MATCH_XORI, MASK_XORI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"lwu",       "64I", "d,o(s)",  MATCH_LWU, MASK_LWU, match_opcode,   WR_xd|RD_xs1 },
{"lwu",       "64I", "d,A",  0, (int) M_LWU, match_never, INSN_MACRO },
{"ld",        "64I", "d,o(s)", MATCH_LD, MASK_LD, match_opcode,  WR_xd|RD_xs1 },
{"ld",        "64I", "d,A",  0, (int) M_LD, match_never, INSN_MACRO },
{"sd",        "64I", "t,q(s)",  MATCH_SD, MASK_SD, match_opcode,   RD_xs1|RD_xs2 },
{"sd",        "64I", "t,A,s",  0, (int) M_SD, match_never,  INSN_MACRO },
{"sext.w",    "64I", "d,s",  MATCH_ADDIW, MASK_ADDIW | MASK_IMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"addiw",     "64I", "d,s,j",  MATCH_ADDIW, MASK_ADDIW, match_opcode,   WR_xd|RD_xs1 },
{"addw",      "64I", "d,s,t",  MATCH_ADDW, MASK_ADDW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"addw",      "64I", "d,s,j",  MATCH_ADDIW, MASK_ADDIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"negw",      "64I", "d,t",  MATCH_SUBW, MASK_SUBW | MASK_RS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 }, /* sub 0 */
{"slliw",     "64I", "d,s,<",   MATCH_SLLIW, MASK_SLLIW, match_opcode,   WR_xd|RD_xs1 },
{"sllw",      "64I", "d,s,t",   MATCH_SLLW, MASK_SLLW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"sllw",      "64I", "d,s,<",   MATCH_SLLIW, MASK_SLLIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"srliw",     "64I", "d,s,<",   MATCH_SRLIW, MASK_SRLIW, match_opcode,   WR_xd|RD_xs1 },
{"srlw",      "64I", "d,s,t",   MATCH_SRLW, MASK_SRLW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"srlw",      "64I", "d,s,<",   MATCH_SRLIW, MASK_SRLIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"sraiw",     "64I", "d,s,<",   MATCH_SRAIW, MASK_SRAIW, match_opcode,   WR_xd|RD_xs1 },
{"sraw",      "64I", "d,s,t",   MATCH_SRAW, MASK_SRAW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"sraw",      "64I", "d,s,<",   MATCH_SRAIW, MASK_SRAIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"subw",      "64I", "d,s,t",  MATCH_SUBW, MASK_SUBW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },

/* Atomic memory operation instruction subset */
{"lr.w",         "A",   "d,0(s)",    MATCH_LR_W, MASK_LR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.w",         "A",   "d,t,0(s)",  MATCH_SC_W, MASK_SC_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.w",     "A",   "d,t,0(s)",  MATCH_AMOADD_W, MASK_AMOADD_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.w",    "A",   "d,t,0(s)",  MATCH_AMOSWAP_W, MASK_AMOSWAP_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.w",     "A",   "d,t,0(s)",  MATCH_AMOAND_W, MASK_AMOAND_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.w",      "A",   "d,t,0(s)",  MATCH_AMOOR_W, MASK_AMOOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.w",     "A",   "d,t,0(s)",  MATCH_AMOXOR_W, MASK_AMOXOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.w",     "A",   "d,t,0(s)",  MATCH_AMOMAX_W, MASK_AMOMAX_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.w",    "A",   "d,t,0(s)",  MATCH_AMOMAXU_W, MASK_AMOMAXU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.w",     "A",   "d,t,0(s)",  MATCH_AMOMIN_W, MASK_AMOMIN_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.w",    "A",   "d,t,0(s)",  MATCH_AMOMINU_W, MASK_AMOMINU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.w.aq",      "A",   "d,0(s)",    MATCH_LR_W | MASK_AQ, MASK_LR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.w.aq",      "A",   "d,t,0(s)",  MATCH_SC_W | MASK_AQ, MASK_SC_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.w.aq",  "A",   "d,t,0(s)",  MATCH_AMOADD_W | MASK_AQ, MASK_AMOADD_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.w.aq", "A",   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_AQ, MASK_AMOSWAP_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.w.aq",  "A",   "d,t,0(s)",  MATCH_AMOAND_W | MASK_AQ, MASK_AMOAND_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.w.aq",   "A",   "d,t,0(s)",  MATCH_AMOOR_W | MASK_AQ, MASK_AMOOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.w.aq",  "A",   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_AQ, MASK_AMOXOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.w.aq",  "A",   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_AQ, MASK_AMOMAX_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.w.aq", "A",   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_AQ, MASK_AMOMAXU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.w.aq",  "A",   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_AQ, MASK_AMOMIN_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.w.aq", "A",   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_AQ, MASK_AMOMINU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.w.rl",      "A",   "d,0(s)",    MATCH_LR_W | MASK_RL, MASK_LR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.w.rl",      "A",   "d,t,0(s)",  MATCH_SC_W | MASK_RL, MASK_SC_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.w.rl",  "A",   "d,t,0(s)",  MATCH_AMOADD_W | MASK_RL, MASK_AMOADD_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.w.rl", "A",   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_RL, MASK_AMOSWAP_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.w.rl",  "A",   "d,t,0(s)",  MATCH_AMOAND_W | MASK_RL, MASK_AMOAND_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.w.rl",   "A",   "d,t,0(s)",  MATCH_AMOOR_W | MASK_RL, MASK_AMOOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.w.rl",  "A",   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_RL, MASK_AMOXOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.w.rl",  "A",   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_RL, MASK_AMOMAX_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.w.rl", "A",   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_RL, MASK_AMOMAXU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.w.rl",  "A",   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_RL, MASK_AMOMIN_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.w.rl", "A",   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_RL, MASK_AMOMINU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.w.sc",      "A",   "d,0(s)",    MATCH_LR_W | MASK_AQRL, MASK_LR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.w.sc",      "A",   "d,t,0(s)",  MATCH_SC_W | MASK_AQRL, MASK_SC_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.w.sc",  "A",   "d,t,0(s)",  MATCH_AMOADD_W | MASK_AQRL, MASK_AMOADD_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.w.sc", "A",   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_AQRL, MASK_AMOSWAP_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.w.sc",  "A",   "d,t,0(s)",  MATCH_AMOAND_W | MASK_AQRL, MASK_AMOAND_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.w.sc",   "A",   "d,t,0(s)",  MATCH_AMOOR_W | MASK_AQRL, MASK_AMOOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.w.sc",  "A",   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_AQRL, MASK_AMOXOR_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.w.sc",  "A",   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_AQRL, MASK_AMOMAX_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.w.sc", "A",   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_AQRL, MASK_AMOMAXU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.w.sc",  "A",   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_AQRL, MASK_AMOMIN_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.w.sc", "A",   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_AQRL, MASK_AMOMINU_W | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.d",         "64A", "d,0(s)",    MATCH_LR_D, MASK_LR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.d",         "64A", "d,t,0(s)",  MATCH_SC_D, MASK_SC_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.d",     "64A", "d,t,0(s)",  MATCH_AMOADD_D, MASK_AMOADD_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.d",    "64A", "d,t,0(s)",  MATCH_AMOSWAP_D, MASK_AMOSWAP_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.d",     "64A", "d,t,0(s)",  MATCH_AMOAND_D, MASK_AMOAND_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.d",      "64A", "d,t,0(s)",  MATCH_AMOOR_D, MASK_AMOOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.d",     "64A", "d,t,0(s)",  MATCH_AMOXOR_D, MASK_AMOXOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.d",     "64A", "d,t,0(s)",  MATCH_AMOMAX_D, MASK_AMOMAX_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.d",    "64A", "d,t,0(s)",  MATCH_AMOMAXU_D, MASK_AMOMAXU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.d",     "64A", "d,t,0(s)",  MATCH_AMOMIN_D, MASK_AMOMIN_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.d",    "64A", "d,t,0(s)",  MATCH_AMOMINU_D, MASK_AMOMINU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.d.aq",      "64A", "d,0(s)",    MATCH_LR_D | MASK_AQ, MASK_LR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.d.aq",      "64A", "d,t,0(s)",  MATCH_SC_D | MASK_AQ, MASK_SC_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.d.aq",  "64A", "d,t,0(s)",  MATCH_AMOADD_D | MASK_AQ, MASK_AMOADD_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.d.aq", "64A", "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_AQ, MASK_AMOSWAP_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.d.aq",  "64A", "d,t,0(s)",  MATCH_AMOAND_D | MASK_AQ, MASK_AMOAND_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.d.aq",   "64A", "d,t,0(s)",  MATCH_AMOOR_D | MASK_AQ, MASK_AMOOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.d.aq",  "64A", "d,t,0(s)",  MATCH_AMOXOR_D | MASK_AQ, MASK_AMOXOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.d.aq",  "64A", "d,t,0(s)",  MATCH_AMOMAX_D | MASK_AQ, MASK_AMOMAX_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.d.aq", "64A", "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_AQ, MASK_AMOMAXU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.d.aq",  "64A", "d,t,0(s)",  MATCH_AMOMIN_D | MASK_AQ, MASK_AMOMIN_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.d.aq", "64A", "d,t,0(s)",  MATCH_AMOMINU_D | MASK_AQ, MASK_AMOMINU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.d.rl",      "64A", "d,0(s)",    MATCH_LR_D | MASK_RL, MASK_LR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.d.rl",      "64A", "d,t,0(s)",  MATCH_SC_D | MASK_RL, MASK_SC_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.d.rl",  "64A", "d,t,0(s)",  MATCH_AMOADD_D | MASK_RL, MASK_AMOADD_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.d.rl", "64A", "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_RL, MASK_AMOSWAP_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.d.rl",  "64A", "d,t,0(s)",  MATCH_AMOAND_D | MASK_RL, MASK_AMOAND_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.d.rl",   "64A", "d,t,0(s)",  MATCH_AMOOR_D | MASK_RL, MASK_AMOOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.d.rl",  "64A", "d,t,0(s)",  MATCH_AMOXOR_D | MASK_RL, MASK_AMOXOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.d.rl",  "64A", "d,t,0(s)",  MATCH_AMOMAX_D | MASK_RL, MASK_AMOMAX_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.d.rl", "64A", "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_RL, MASK_AMOMAXU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.d.rl",  "64A", "d,t,0(s)",  MATCH_AMOMIN_D | MASK_RL, MASK_AMOMIN_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.d.rl", "64A", "d,t,0(s)",  MATCH_AMOMINU_D | MASK_RL, MASK_AMOMINU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"lr.d.sc",      "64A", "d,0(s)",    MATCH_LR_D | MASK_AQRL, MASK_LR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1 },
{"sc.d.sc",      "64A", "d,t,0(s)",  MATCH_SC_D | MASK_AQRL, MASK_SC_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoadd.d.sc",  "64A", "d,t,0(s)",  MATCH_AMOADD_D | MASK_AQRL, MASK_AMOADD_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoswap.d.sc", "64A", "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_AQRL, MASK_AMOSWAP_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoand.d.sc",  "64A", "d,t,0(s)",  MATCH_AMOAND_D | MASK_AQRL, MASK_AMOAND_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoor.d.sc",   "64A", "d,t,0(s)",  MATCH_AMOOR_D | MASK_AQRL, MASK_AMOOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amoxor.d.sc",  "64A", "d,t,0(s)",  MATCH_AMOXOR_D | MASK_AQRL, MASK_AMOXOR_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomax.d.sc",  "64A", "d,t,0(s)",  MATCH_AMOMAX_D | MASK_AQRL, MASK_AMOMAX_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomaxu.d.sc", "64A", "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_AQRL, MASK_AMOMAXU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amomin.d.sc",  "64A", "d,t,0(s)",  MATCH_AMOMIN_D | MASK_AQRL, MASK_AMOMIN_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"amominu.d.sc", "64A", "d,t,0(s)",  MATCH_AMOMINU_D | MASK_AQRL, MASK_AMOMINU_D | MASK_AQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },

/* Multiply/Divide instruction subset */
{"mul",       "M",   "d,s,t",  MATCH_MUL, MASK_MUL, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"mulh",      "M",   "d,s,t",  MATCH_MULH, MASK_MULH, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"mulhu",     "M",   "d,s,t",  MATCH_MULHU, MASK_MULHU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"mulhsu",    "M",   "d,s,t",  MATCH_MULHSU, MASK_MULHSU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"div",       "M",   "d,s,t",  MATCH_DIV, MASK_DIV, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"divu",      "M",   "d,s,t",  MATCH_DIVU, MASK_DIVU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"rem",       "M",   "d,s,t",  MATCH_REM, MASK_REM, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"remu",      "M",   "d,s,t",  MATCH_REMU, MASK_REMU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"mulw",      "64M", "d,s,t",  MATCH_MULW, MASK_MULW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"divw",      "64M", "d,s,t",  MATCH_DIVW, MASK_DIVW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"divuw",     "64M", "d,s,t",  MATCH_DIVUW, MASK_DIVUW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"remw",      "64M", "d,s,t",  MATCH_REMW, MASK_REMW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"remuw",     "64M", "d,s,t",  MATCH_REMUW, MASK_REMUW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },

/* Single-precision floating-point instruction subset */
{"frsr",      "F",   "d",  MATCH_FRCSR, MASK_FRCSR, match_opcode,  WR_xd },
{"fssr",      "F",   "s",  MATCH_FSCSR, MASK_FSCSR | MASK_RD, match_opcode,  RD_xs1 },
{"fssr",      "F",   "d,s",  MATCH_FSCSR, MASK_FSCSR, match_opcode,  WR_xd|RD_xs1 },
{"frcsr",     "F",   "d",  MATCH_FRCSR, MASK_FRCSR, match_opcode,  WR_xd },
{"fscsr",     "F",   "s",  MATCH_FSCSR, MASK_FSCSR | MASK_RD, match_opcode,  RD_xs1 },
{"fscsr",     "F",   "d,s",  MATCH_FSCSR, MASK_FSCSR, match_opcode,  WR_xd|RD_xs1 },
{"frrm",      "F",   "d",  MATCH_FRRM, MASK_FRRM, match_opcode,  WR_xd },
{"fsrm",      "F",   "s",  MATCH_FSRM, MASK_FSRM | MASK_RD, match_opcode,  RD_xs1 },
{"fsrm",      "F",   "d,s",  MATCH_FSRM, MASK_FSRM, match_opcode,  WR_xd|RD_xs1 },
{"frflags",   "F",   "d",  MATCH_FRFLAGS, MASK_FRFLAGS, match_opcode,  WR_xd },
{"fsflags",   "F",   "s",  MATCH_FSFLAGS, MASK_FSFLAGS | MASK_RD, match_opcode,  RD_xs1 },
{"fsflags",   "F",   "d,s",  MATCH_FSFLAGS, MASK_FSFLAGS, match_opcode,  WR_xd|RD_xs1 },
{"flw",       "F",   "D,o(s)",  MATCH_FLW, MASK_FLW, match_opcode,   WR_fd|RD_xs1 },
{"flw",       "F",   "D,A,s",  0, (int) M_FLW, match_never,  INSN_MACRO },
{"fsw",       "F",   "T,q(s)",  MATCH_FSW, MASK_FSW, match_opcode,   RD_xs1|RD_fs2 },
{"fsw",       "F",   "T,A,s",  0, (int) M_FSW, match_never,  INSN_MACRO },
{"fmv.x.s",   "F",   "d,S",  MATCH_FMV_X_S, MASK_FMV_X_S, match_opcode,  WR_xd|RD_fs1 },
{"fmv.s.x",   "F",   "D,s",  MATCH_FMV_S_X, MASK_FMV_S_X, match_opcode,  WR_fd|RD_xs1 },
{"fmv.s",     "F",   "D,U",  MATCH_FSGNJ_S, MASK_FSGNJ_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fneg.s",    "F",   "D,U",  MATCH_FSGNJN_S, MASK_FSGNJN_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fabs.s",    "F",   "D,U",  MATCH_FSGNJX_S, MASK_FSGNJX_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fsgnj.s",   "F",   "D,S,T",  MATCH_FSGNJ_S, MASK_FSGNJ_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsgnjn.s",  "F",   "D,S,T",  MATCH_FSGNJN_S, MASK_FSGNJN_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsgnjx.s",  "F",   "D,S,T",  MATCH_FSGNJX_S, MASK_FSGNJX_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fadd.s",    "F",   "D,S,T",  MATCH_FADD_S | MASK_RM, MASK_FADD_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fadd.s",    "F",   "D,S,T,m",  MATCH_FADD_S, MASK_FADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsub.s",    "F",   "D,S,T",  MATCH_FSUB_S | MASK_RM, MASK_FSUB_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsub.s",    "F",   "D,S,T,m",  MATCH_FSUB_S, MASK_FSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmul.s",    "F",   "D,S,T",  MATCH_FMUL_S | MASK_RM, MASK_FMUL_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmul.s",    "F",   "D,S,T,m",  MATCH_FMUL_S, MASK_FMUL_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fdiv.s",    "F",   "D,S,T",  MATCH_FDIV_S | MASK_RM, MASK_FDIV_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fdiv.s",    "F",   "D,S,T,m",  MATCH_FDIV_S, MASK_FDIV_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsqrt.s",   "F",   "D,S",  MATCH_FSQRT_S | MASK_RM, MASK_FSQRT_S | MASK_RM, match_opcode,  WR_fd|RD_fs1 },
{"fsqrt.s",   "F",   "D,S,m",  MATCH_FSQRT_S, MASK_FSQRT_S, match_opcode,  WR_fd|RD_fs1 },
{"fmin.s",    "F",   "D,S,T",  MATCH_FMIN_S, MASK_FMIN_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmax.s",    "F",   "D,S,T",  MATCH_FMAX_S, MASK_FMAX_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmadd.s",   "F",   "D,S,T,R",  MATCH_FMADD_S | MASK_RM, MASK_FMADD_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmadd.s",   "F",   "D,S,T,R,m",  MATCH_FMADD_S, MASK_FMADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmadd.s",  "F",   "D,S,T,R",  MATCH_FNMADD_S | MASK_RM, MASK_FNMADD_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmadd.s",  "F",   "D,S,T,R,m",  MATCH_FNMADD_S, MASK_FNMADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmsub.s",   "F",   "D,S,T,R",  MATCH_FMSUB_S | MASK_RM, MASK_FMSUB_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmsub.s",   "F",   "D,S,T,R,m",  MATCH_FMSUB_S, MASK_FMSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmsub.s",  "F",   "D,S,T,R",  MATCH_FNMSUB_S | MASK_RM, MASK_FNMSUB_S | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmsub.s",  "F",   "D,S,T,R,m",  MATCH_FNMSUB_S, MASK_FNMSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fcvt.w.s",  "F",   "d,S",  MATCH_FCVT_W_S | MASK_RM, MASK_FCVT_W_S | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.w.s",  "F",   "d,S,m",  MATCH_FCVT_W_S, MASK_FCVT_W_S, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.wu.s", "F",   "d,S",  MATCH_FCVT_WU_S | MASK_RM, MASK_FCVT_WU_S | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.wu.s", "F",   "d,S,m",  MATCH_FCVT_WU_S, MASK_FCVT_WU_S, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.s.w",  "F",   "D,s",  MATCH_FCVT_S_W | MASK_RM, MASK_FCVT_S_W | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.w",  "F",   "D,s,m",  MATCH_FCVT_S_W, MASK_FCVT_S_W, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.wu", "F",   "D,s",  MATCH_FCVT_S_WU | MASK_RM, MASK_FCVT_S_W | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.wu", "F",   "D,s,m",  MATCH_FCVT_S_WU, MASK_FCVT_S_WU, match_opcode,   WR_fd|RD_xs1 },
{"fclass.s",  "F",   "d,S",  MATCH_FCLASS_S, MASK_FCLASS_S, match_opcode,   WR_xd|RD_fs1 },
{"feq.s",     "F",   "d,S,T",    MATCH_FEQ_S, MASK_FEQ_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"flt.s",     "F",   "d,S,T",    MATCH_FLT_S, MASK_FLT_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fle.s",     "F",   "d,S,T",    MATCH_FLE_S, MASK_FLE_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fgt.s",     "F",   "d,T,S",    MATCH_FLT_S, MASK_FLT_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fge.s",     "F",   "d,T,S",    MATCH_FLE_S, MASK_FLE_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fcvt.l.s",  "64F", "d,S",  MATCH_FCVT_L_S | MASK_RM, MASK_FCVT_L_S | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.l.s",  "64F", "d,S,m",  MATCH_FCVT_L_S, MASK_FCVT_L_S, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.lu.s", "64F", "d,S",  MATCH_FCVT_LU_S | MASK_RM, MASK_FCVT_LU_S | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.lu.s", "64F", "d,S,m",  MATCH_FCVT_LU_S, MASK_FCVT_LU_S, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.s.l",  "64F", "D,s",  MATCH_FCVT_S_L | MASK_RM, MASK_FCVT_S_L | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.l",  "64F", "D,s,m",  MATCH_FCVT_S_L, MASK_FCVT_S_L, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.lu", "64F", "D,s",  MATCH_FCVT_S_LU | MASK_RM, MASK_FCVT_S_L | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.s.lu", "64F", "D,s,m",  MATCH_FCVT_S_LU, MASK_FCVT_S_LU, match_opcode,   WR_fd|RD_xs1 },

/* Double-precision floating-point instruction subset */
{"fld",       "D",   "D,o(s)",  MATCH_FLD, MASK_FLD, match_opcode,  WR_fd|RD_xs1 },
{"fld",       "D",   "D,A,s",  0, (int) M_FLD, match_never,  INSN_MACRO },
{"fsd",       "D",   "T,q(s)",  MATCH_FSD, MASK_FSD, match_opcode,  RD_xs1|RD_fs2 },
{"fsd",       "D",   "T,A,s",  0, (int) M_FSD, match_never,  INSN_MACRO },
{"fmv.d",     "D",   "D,U",  MATCH_FSGNJ_D, MASK_FSGNJ_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fneg.d",    "D",   "D,U",  MATCH_FSGNJN_D, MASK_FSGNJN_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fabs.d",    "D",   "D,U",  MATCH_FSGNJX_D, MASK_FSGNJX_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"fsgnj.d",   "D",   "D,S,T",  MATCH_FSGNJ_D, MASK_FSGNJ_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsgnjn.d",  "D",   "D,S,T",  MATCH_FSGNJN_D, MASK_FSGNJN_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsgnjx.d",  "D",   "D,S,T",  MATCH_FSGNJX_D, MASK_FSGNJX_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fadd.d",    "D",   "D,S,T",  MATCH_FADD_D | MASK_RM, MASK_FADD_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fadd.d",    "D",   "D,S,T,m",  MATCH_FADD_D, MASK_FADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsub.d",    "D",   "D,S,T",  MATCH_FSUB_D | MASK_RM, MASK_FSUB_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsub.d",    "D",   "D,S,T,m",  MATCH_FSUB_D, MASK_FSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmul.d",    "D",   "D,S,T",  MATCH_FMUL_D | MASK_RM, MASK_FMUL_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmul.d",    "D",   "D,S,T,m",  MATCH_FMUL_D, MASK_FMUL_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fdiv.d",    "D",   "D,S,T",  MATCH_FDIV_D | MASK_RM, MASK_FDIV_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fdiv.d",    "D",   "D,S,T,m",  MATCH_FDIV_D, MASK_FDIV_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fsqrt.d",   "D",   "D,S",  MATCH_FSQRT_D | MASK_RM, MASK_FSQRT_D | MASK_RM, match_opcode,  WR_fd|RD_fs1 },
{"fsqrt.d",   "D",   "D,S,m",  MATCH_FSQRT_D, MASK_FSQRT_D, match_opcode,  WR_fd|RD_fs1 },
{"fmin.d",    "D",   "D,S,T",  MATCH_FMIN_D, MASK_FMIN_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmax.d",    "D",   "D,S,T",  MATCH_FMAX_D, MASK_FMAX_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"fmadd.d",   "D",   "D,S,T,R",  MATCH_FMADD_D | MASK_RM, MASK_FMADD_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmadd.d",   "D",   "D,S,T,R,m",  MATCH_FMADD_D, MASK_FMADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmadd.d",  "D",   "D,S,T,R",  MATCH_FNMADD_D | MASK_RM, MASK_FNMADD_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmadd.d",  "D",   "D,S,T,R,m",  MATCH_FNMADD_D, MASK_FNMADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmsub.d",   "D",   "D,S,T,R",  MATCH_FMSUB_D | MASK_RM, MASK_FMSUB_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fmsub.d",   "D",   "D,S,T,R,m",  MATCH_FMSUB_D, MASK_FMSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmsub.d",  "D",   "D,S,T,R",  MATCH_FNMSUB_D | MASK_RM, MASK_FNMSUB_D | MASK_RM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fnmsub.d",  "D",   "D,S,T,R,m",  MATCH_FNMSUB_D, MASK_FNMSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"fcvt.w.d",  "D",   "d,S",  MATCH_FCVT_W_D | MASK_RM, MASK_FCVT_W_D | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.w.d",  "D",   "d,S,m",  MATCH_FCVT_W_D, MASK_FCVT_W_D, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.wu.d", "D",   "d,S",  MATCH_FCVT_WU_D | MASK_RM, MASK_FCVT_WU_D | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.wu.d", "D",   "d,S,m",  MATCH_FCVT_WU_D, MASK_FCVT_WU_D, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.d.w",  "D",   "D,s",  MATCH_FCVT_D_W, MASK_FCVT_D_W | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.d.wu", "D",   "D,s",  MATCH_FCVT_D_WU, MASK_FCVT_D_WU | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.d.s",  "D",   "D,S",  MATCH_FCVT_D_S, MASK_FCVT_D_S | MASK_RM, match_opcode,   WR_fd|RD_fs1 },
{"fcvt.s.d",  "D",   "D,S",  MATCH_FCVT_S_D | MASK_RM, MASK_FCVT_S_D | MASK_RM, match_opcode,   WR_fd|RD_fs1 },
{"fcvt.s.d",  "D",   "D,S,m",  MATCH_FCVT_S_D, MASK_FCVT_S_D, match_opcode,   WR_fd|RD_fs1 },
{"fclass.d",  "D",   "d,S",  MATCH_FCLASS_D, MASK_FCLASS_D, match_opcode,   WR_xd|RD_fs1 },
{"feq.d",     "D",   "d,S,T",    MATCH_FEQ_D, MASK_FEQ_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"flt.d",     "D",   "d,S,T",    MATCH_FLT_D, MASK_FLT_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fle.d",     "D",   "d,S,T",    MATCH_FLE_D, MASK_FLE_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fgt.d",     "D",   "d,T,S",    MATCH_FLT_D, MASK_FLT_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fge.d",     "D",   "d,T,S",    MATCH_FLE_D, MASK_FLE_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"fmv.x.d",   "64D", "d,S",  MATCH_FMV_X_D, MASK_FMV_X_D, match_opcode,  WR_xd|RD_fs1 },
{"fmv.d.x",   "64D", "D,s",  MATCH_FMV_D_X, MASK_FMV_D_X, match_opcode,  WR_fd|RD_xs1 },
{"fcvt.l.d",  "64D", "d,S",  MATCH_FCVT_L_D | MASK_RM, MASK_FCVT_L_D | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.l.d",  "64D", "d,S,m",  MATCH_FCVT_L_D, MASK_FCVT_L_D, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.lu.d", "64D", "d,S",  MATCH_FCVT_LU_D | MASK_RM, MASK_FCVT_LU_D | MASK_RM, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.lu.d", "64D", "d,S,m",  MATCH_FCVT_LU_D, MASK_FCVT_LU_D, match_opcode,  WR_xd|RD_fs1 },
{"fcvt.d.l",  "64D", "D,s",  MATCH_FCVT_D_L | MASK_RM, MASK_FCVT_D_L | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.d.l",  "64D", "D,s,m",  MATCH_FCVT_D_L, MASK_FCVT_D_L, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.d.lu", "64D", "D,s",  MATCH_FCVT_D_LU | MASK_RM, MASK_FCVT_D_L | MASK_RM, match_opcode,   WR_fd|RD_xs1 },
{"fcvt.d.lu", "64D", "D,s,m",  MATCH_FCVT_D_LU, MASK_FCVT_D_LU, match_opcode,   WR_fd|RD_xs1 },

/* Supervisor instructions */
{"csrr",      "I",   "d,E",  MATCH_CSRRS, MASK_CSRRS | MASK_RS1, match_opcode,  WR_xd },
{"csrwi",     "I",   "E,Z",  MATCH_CSRRWI, MASK_CSRRWI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrw",      "I",   "E,s",  MATCH_CSRRW, MASK_CSRRW | MASK_RD, match_opcode,  RD_xs1 },
{"csrw",      "I",   "E,Z",  MATCH_CSRRWI, MASK_CSRRWI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrsi",     "I",   "E,Z",  MATCH_CSRRSI, MASK_CSRRSI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrs",      "I",   "E,s",  MATCH_CSRRS, MASK_CSRRS | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrs",      "I",   "E,Z",  MATCH_CSRRSI, MASK_CSRRSI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrci",     "I",   "E,Z",  MATCH_CSRRCI, MASK_CSRRCI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrc",      "I",   "E,s",  MATCH_CSRRC, MASK_CSRRC | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrc",      "I",   "E,Z",  MATCH_CSRRCI, MASK_CSRRCI | MASK_RD, match_opcode,  WR_xd|RD_xs1 },
{"csrrw",     "I",   "d,E,s",  MATCH_CSRRW, MASK_CSRRW, match_opcode,  WR_xd|RD_xs1 },
{"csrrw",     "I",   "d,E,Z",  MATCH_CSRRWI, MASK_CSRRWI, match_opcode,  WR_xd|RD_xs1 },
{"csrrs",     "I",   "d,E,s",  MATCH_CSRRS, MASK_CSRRS, match_opcode,  WR_xd|RD_xs1 },
{"csrrs",     "I",   "d,E,Z",  MATCH_CSRRSI, MASK_CSRRSI, match_opcode,  WR_xd|RD_xs1 },
{"csrrc",     "I",   "d,E,s",  MATCH_CSRRC, MASK_CSRRC, match_opcode,  WR_xd|RD_xs1 },
{"csrrc",     "I",   "d,E,Z",  MATCH_CSRRCI, MASK_CSRRCI, match_opcode,  WR_xd|RD_xs1 },
{"csrrwi",    "I",   "d,E,Z",  MATCH_CSRRWI, MASK_CSRRWI, match_opcode,  WR_xd|RD_xs1 },
{"csrrsi",    "I",   "d,E,Z",  MATCH_CSRRSI, MASK_CSRRSI, match_opcode,  WR_xd|RD_xs1 },
{"csrrci",    "I",   "d,E,Z",  MATCH_CSRRCI, MASK_CSRRCI, match_opcode,  WR_xd|RD_xs1 },
{"sret",      "I",   "",     MATCH_SRET, MASK_SRET, match_opcode,  0 },
{"eret",      "I",   "",     MATCH_SRET, MASK_SRET, match_opcode,  0 },
{"mrts",      "I",   "",     MATCH_MRTS, MASK_MRTS, match_opcode,  0 },
{"sfence.vm", "I",   "",     MATCH_SFENCE_VM | MASK_RS1, MASK_SFENCE_VM | MASK_RS1, match_opcode,  0 },
{"sfence.vm", "I",   "s",    MATCH_SFENCE_VM, MASK_SFENCE_VM, match_opcode,  RD_xs1 },


/* Rocket Custom Coprocessor extension */
{"custom0",   "Xcustom", "d,s,t,^j", MATCH_CUSTOM0_RD_RS1_RS2, MASK_CUSTOM0_RD_RS1_RS2, match_opcode, 0},
{"custom0",   "Xcustom", "d,s,^t,^j", MATCH_CUSTOM0_RD_RS1, MASK_CUSTOM0_RD_RS1, match_opcode, 0},
{"custom0",   "Xcustom", "d,^s,^t,^j", MATCH_CUSTOM0_RD, MASK_CUSTOM0_RD, match_opcode, 0},
{"custom0",   "Xcustom", "^d,s,t,^j", MATCH_CUSTOM0_RS1_RS2, MASK_CUSTOM0_RS1_RS2, match_opcode, 0},
{"custom0",   "Xcustom", "^d,s,^t,^j", MATCH_CUSTOM0_RS1, MASK_CUSTOM0_RS1, match_opcode, 0},
{"custom0",   "Xcustom", "^d,^s,^t,^j", MATCH_CUSTOM0, MASK_CUSTOM0, match_opcode, 0},
{"custom1",   "Xcustom", "d,s,t,^j", MATCH_CUSTOM1_RD_RS1_RS2, MASK_CUSTOM1_RD_RS1_RS2, match_opcode, 0},
{"custom1",   "Xcustom", "d,s,^t,^j", MATCH_CUSTOM1_RD_RS1, MASK_CUSTOM1_RD_RS1, match_opcode, 0},
{"custom1",   "Xcustom", "d,^s,^t,^j", MATCH_CUSTOM1_RD, MASK_CUSTOM1_RD, match_opcode, 0},
{"custom1",   "Xcustom", "^d,s,t,^j", MATCH_CUSTOM1_RS1_RS2, MASK_CUSTOM1_RS1_RS2, match_opcode, 0},
{"custom1",   "Xcustom", "^d,s,^t,^j", MATCH_CUSTOM1_RS1, MASK_CUSTOM1_RS1, match_opcode, 0},
{"custom1",   "Xcustom", "^d,^s,^t,^j", MATCH_CUSTOM1, MASK_CUSTOM1, match_opcode, 0},
{"custom2",   "Xcustom", "d,s,t,^j", MATCH_CUSTOM2_RD_RS1_RS2, MASK_CUSTOM2_RD_RS1_RS2, match_opcode, 0},
{"custom2",   "Xcustom", "d,s,^t,^j", MATCH_CUSTOM2_RD_RS1, MASK_CUSTOM2_RD_RS1, match_opcode, 0},
{"custom2",   "Xcustom", "d,^s,^t,^j", MATCH_CUSTOM2_RD, MASK_CUSTOM2_RD, match_opcode, 0},
{"custom2",   "Xcustom", "^d,s,t,^j", MATCH_CUSTOM2_RS1_RS2, MASK_CUSTOM2_RS1_RS2, match_opcode, 0},
{"custom2",   "Xcustom", "^d,s,^t,^j", MATCH_CUSTOM2_RS1, MASK_CUSTOM2_RS1, match_opcode, 0},
{"custom2",   "Xcustom", "^d,^s,^t,^j", MATCH_CUSTOM2, MASK_CUSTOM2, match_opcode, 0},
{"custom3",   "Xcustom", "d,s,t,^j", MATCH_CUSTOM3_RD_RS1_RS2, MASK_CUSTOM3_RD_RS1_RS2, match_opcode, 0},
{"custom3",   "Xcustom", "d,s,^t,^j", MATCH_CUSTOM3_RD_RS1, MASK_CUSTOM3_RD_RS1, match_opcode, 0},
{"custom3",   "Xcustom", "d,^s,^t,^j", MATCH_CUSTOM3_RD, MASK_CUSTOM3_RD, match_opcode, 0},
{"custom3",   "Xcustom", "^d,s,t,^j", MATCH_CUSTOM3_RS1_RS2, MASK_CUSTOM3_RS1_RS2, match_opcode, 0},
{"custom3",   "Xcustom", "^d,s,^t,^j", MATCH_CUSTOM3_RS1, MASK_CUSTOM3_RS1, match_opcode, 0},
{"custom3",   "Xcustom", "^d,^s,^t,^j", MATCH_CUSTOM3, MASK_CUSTOM3, match_opcode, 0},

/* Xhwacha extension ct instructions*/
{"vsetcfg",   "Xhwacha", "s", MATCH_VSETCFG, MASK_VSETCFG | MASK_IMM, match_opcode, 0},
{"vsetcfg",   "Xhwacha", "#g,#f", MATCH_VSETCFG, MASK_VSETCFG | MASK_RS1, match_opcode, 0},
{"vsetcfg",   "Xhwacha", "s,#g,#f", MATCH_VSETCFG, MASK_VSETCFG, match_opcode, 0},
{"vsetucfg",  "Xhwacha", "d,u", MATCH_LUI, MASK_LUI, match_opcode, INSN_ALIAS | WR_xd},
{"vsetvl",    "Xhwacha", "d,s", MATCH_VSETVL, MASK_VSETVL, match_opcode, 0},
{"vgetcfg",   "Xhwacha", "d", MATCH_VGETCFG, MASK_VGETCFG, match_opcode, 0},
{"vgetvl",    "Xhwacha", "d", MATCH_VGETVL, MASK_VGETVL, match_opcode, 0},
{"vuncfg",    "Xhwacha", "", MATCH_VUNCFG, MASK_VUNCFG, match_opcode, 0},

{"vmss",      "Xhwacha", "#E,s", MATCH_VMSS, MASK_VMSS, match_opcode, 0},
{"vmsa",      "Xhwacha", "#e,s", MATCH_VMSA, MASK_VMSA, match_opcode, 0},

{"vf",        "Xhwacha", "q(s)", MATCH_VF, MASK_VF, match_opcode, 0},
{"vf",        "Xhwacha", "A,s", 0, (int) M_VF, match_never, INSN_MACRO },

{"vxcptcause",   "Xhwacha", "d", MATCH_VXCPTCAUSE, MASK_VXCPTCAUSE, match_opcode, 0},
{"vxcptaux",     "Xhwacha", "d", MATCH_VXCPTAUX, MASK_VXCPTAUX, match_opcode, 0},

{"vxcptsave",    "Xhwacha", "s", MATCH_VXCPTSAVE, MASK_VXCPTSAVE, match_opcode, 0},
{"vxcptrestore", "Xhwacha", "s", MATCH_VXCPTRESTORE, MASK_VXCPTRESTORE, match_opcode, 0},
{"vxcptkill",    "Xhwacha", "", MATCH_VXCPTKILL, MASK_VXCPTKILL, match_opcode, 0},

{"vxcptevac",    "Xhwacha", "s", MATCH_VXCPTEVAC, MASK_VXCPTEVAC, match_opcode, 0},
{"vxcpthold",    "Xhwacha", "s", MATCH_VXCPTHOLD, MASK_VXCPTHOLD, match_opcode, 0},
{"venqcmd",      "Xhwacha", "s,t", MATCH_VENQCMD, MASK_VENQCMD, match_opcode, 0},
{"venqimm1",     "Xhwacha", "s,t", MATCH_VENQIMM1, MASK_VENQIMM1, match_opcode, 0},
{"venqimm2",     "Xhwacha", "s,t", MATCH_VENQIMM2, MASK_VENQIMM2, match_opcode, 0},
{"venqcnt",      "Xhwacha", "s,t", MATCH_VENQCNT, MASK_VENQCNT, match_opcode, 0},

/* Xhwacha extension work thread instructions*/
{"vstop",     "Xhwacha", "", MATCH_VSTOP, MASK_VSTOP, match_opcode, 0},
{"vfence",    "Xhwacha", "#G,#H", MATCH_VFENCE, MASK_VFENCE, match_opcode, 0},
{"vfence",    "Xhwacha", "",  MATCH_VFENCE | MASK_VPREV | MASK_VSUCC, MASK_VFENCE | MASK_VRD,  match_opcode,   INSN_ALIAS },
{"veidx",     "Xhwacha", "#N,#p,#d", MATCH_VEIDX, MASK_VEIDX, match_opcode, WR_xd},
{"vfirst",    "Xhwacha", "#N,#p,#D,#s", MATCH_VFIRST, MASK_VFIRST, match_opcode, WR_xd},

/* work thread control flow instructions */
{"vcjal",     "Xhwacha", "#N,#p,#c,#D,#k", MATCH_VCJAL, MASK_VCJAL, match_opcode, WR_xd},
{"vcjalr",    "Xhwacha", "#N,#p,#c,#D,#S,#k", MATCH_VCJALR, MASK_VCJALR, match_opcode, WR_xd},

/* scalar load upper */
{"vlui",      "Xhwacha", "#D,#j", MATCH_VLUI, MASK_VLUI, match_opcode, WR_xd},
{"vauipc",    "Xhwacha", "#D,#j", MATCH_VAUIPC, MASK_VAUIPC, match_opcode, WR_xd},

/* vnop */
{"vnop",      "Xhwacha",   "",  MATCH_VADDI, MASK_VADDI | MASK_VRD | MASK_VRS1 | MASK_VIMM | MASK_VPRED | MASK_VN, match_opcode,  INSN_ALIAS},

/* vector loads */
/* unit stride */
/* xloads */
{"vld",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLD, MASK_VLD, match_opcode, 0},
{"vlw",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLW, MASK_VLW, match_opcode, 0},
{"vlwu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLWU, MASK_VLWU, match_opcode, 0},
{"vlh",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLH, MASK_VLH, match_opcode, 0},
{"vlhu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLHU, MASK_VLHU, match_opcode, 0},
{"vlb",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLB, MASK_VLB, match_opcode, 0},
{"vlbu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLBU, MASK_VLBU, match_opcode, 0},

/* stride */
/* xloads */
{"vlstd",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTD, MASK_VLSTD, match_opcode, 0},
{"vlstw",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTW, MASK_VLSTW, match_opcode, 0},
{"vlstwu",    "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTWU, MASK_VLSTWU, match_opcode, 0},
{"vlsth",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTH, MASK_VLSTH, match_opcode, 0},
{"vlsthu",    "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTHU, MASK_VLSTHU, match_opcode, 0},
{"vlstb",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTB, MASK_VLSTB, match_opcode, 0},
{"vlstbu",    "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VLSTBU, MASK_VLSTBU, match_opcode, 0},

/* segment */
/* xloads */
{"vlsegd",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGD, MASK_VLSEGD, match_opcode, 0},
{"vlsegw",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGW, MASK_VLSEGW, match_opcode, 0},
{"vlsegwu",   "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGWU, MASK_VLSEGWU, match_opcode, 0},
{"vlsegh",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGH, MASK_VLSEGH, match_opcode, 0},
{"vlseghu",   "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGHU, MASK_VLSEGHU, match_opcode, 0},
{"vlsegb",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGB, MASK_VLSEGB, match_opcode, 0},
{"vlsegbu",   "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VLSEGBU, MASK_VLSEGBU, match_opcode, 0},

/* stride segment */
/* xloads */
{"vlsegstd",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTD, MASK_VLSEGSTD, match_opcode, 0},
{"vlsegstw",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTW, MASK_VLSEGSTW, match_opcode, 0},
{"vlsegstwu", "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTWU, MASK_VLSEGSTWU, match_opcode, 0},
{"vlsegsth",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTH, MASK_VLSEGSTH, match_opcode, 0},
{"vlsegsthu", "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTHU, MASK_VLSEGSTHU, match_opcode, 0},
{"vlsegstb",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTB, MASK_VLSEGSTB, match_opcode, 0},
{"vlsegstbu", "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VLSEGSTBU, MASK_VLSEGSTBU, match_opcode, 0},

/* unit stride */
/* xstores */
{"vsd",       "Xhwacha", "#N,#p,#d,#A", MATCH_VSD, MASK_VSD, match_opcode, 0},
{"vsw",       "Xhwacha", "#N,#p,#d,#A", MATCH_VSW, MASK_VSW, match_opcode, 0},
{"vsh",       "Xhwacha", "#N,#p,#d,#A", MATCH_VSH, MASK_VSH, match_opcode, 0},
{"vsb",       "Xhwacha", "#N,#p,#d,#A", MATCH_VSB, MASK_VSB, match_opcode, 0},

/* stride */
/* xstores */
{"vsstd",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VSSTD, MASK_VSSTD, match_opcode, 0},
{"vsstw",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VSSTW, MASK_VSSTW, match_opcode, 0},
{"vssth",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VSSTH, MASK_VSSTH, match_opcode, 0},
{"vsstb",     "Xhwacha", "#N,#p,#d,#A,#B", MATCH_VSSTB, MASK_VSSTB, match_opcode, 0},

/* segment */
/* xstores */
{"vssegd",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VSSEGD, MASK_VSSEGD, match_opcode, 0},
{"vssegw",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VSSEGW, MASK_VSSEGW, match_opcode, 0},
{"vssegh",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VSSEGH, MASK_VSSEGH, match_opcode, 0},
{"vssegb",    "Xhwacha", "#N,#p,#d,#A,#n", MATCH_VSSEGB, MASK_VSSEGB, match_opcode, 0},

/* stride segment */
/* xsegstores */
{"vssegstd",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VSSEGSTD, MASK_VSSEGSTD, match_opcode, 0},
{"vssegstw",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VSSEGSTW, MASK_VSSEGSTW, match_opcode, 0},
{"vssegsth",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VSSEGSTH, MASK_VSSEGSTH, match_opcode, 0},
{"vssegstb",  "Xhwacha", "#N,#p,#d,#A,#B,#n", MATCH_VSSEGSTB, MASK_VSSEGSTB, match_opcode, 0},

/* indexed load/stores */
/* xloads */
{"vlxd",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXD, MASK_VLXD, match_opcode, 0},
{"vlxw",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXW, MASK_VLXW, match_opcode, 0},
{"vlxwu",      "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXWU,MASK_VLXWU, match_opcode, 0},
{"vlxh",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXH, MASK_VLXH, match_opcode, 0},
{"vlxhu",      "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXHU,MASK_VLXHU, match_opcode, 0},
{"vlxb",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXB, MASK_VLXB, match_opcode, 0},
{"vlxbu",      "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VLXBU,MASK_VLXBU, match_opcode, 0},
/* xstores */
{"vsxd",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VSXD, MASK_VSXD, match_opcode, 0},
{"vsxw",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VSXW, MASK_VSXW, match_opcode, 0},
{"vsxh",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VSXH, MASK_VSXH, match_opcode, 0},
{"vsxb",       "Xhwacha", "#N,#p,#d,#S,#t", MATCH_VSXB, MASK_VSXB, match_opcode, 0},

/* shared loads from shared registers */
/* xloads */
{"vlsd",       "Xhwacha", "#N,#p,#d,#S", MATCH_VLSD, MASK_VLSD, match_opcode, 0},
{"vlsw",       "Xhwacha", "#N,#p,#d,#S", MATCH_VLSW, MASK_VLSW, match_opcode, 0},
{"vlswu",      "Xhwacha", "#N,#p,#d,#S", MATCH_VLSWU,MASK_VLSWU, match_opcode, 0},
{"vlsh",       "Xhwacha", "#N,#p,#d,#S", MATCH_VLSH, MASK_VLSH, match_opcode, 0},
{"vlshu",      "Xhwacha", "#N,#p,#d,#S", MATCH_VLSHU,MASK_VLSHU, match_opcode, 0},
{"vlsb",       "Xhwacha", "#N,#p,#d,#S", MATCH_VLSB, MASK_VLSB, match_opcode, 0},
{"vlsbu",      "Xhwacha", "#N,#p,#d,#S", MATCH_VLSBU,MASK_VLSBU, match_opcode, 0},
/* xstores */
{"vssd",       "Xhwacha", "#N,#p,#S,#T", MATCH_VSSD, MASK_VSSD, match_opcode, 0},
{"vssw",       "Xhwacha", "#N,#p,#S,#T", MATCH_VSSW, MASK_VSSW, match_opcode, 0},
{"vssh",       "Xhwacha", "#N,#p,#S,#T", MATCH_VSSH, MASK_VSSH, match_opcode, 0},
{"vssb",       "Xhwacha", "#N,#p,#S,#T", MATCH_VSSB, MASK_VSSB, match_opcode, 0},

/* shared loads from address registers */
/* xloads */
{"vlad",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLAD, MASK_VLAD, match_opcode, 0},
{"vlaw",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLAW, MASK_VLAW, match_opcode, 0},
{"vlawu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLAWU,MASK_VLAWU, match_opcode, 0},
{"vlah",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLAH, MASK_VLAH, match_opcode, 0},
{"vlahu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLAHU,MASK_VLAHU, match_opcode, 0},
{"vlab",       "Xhwacha", "#N,#p,#d,#A", MATCH_VLAB, MASK_VLAB, match_opcode, 0},
{"vlabu",      "Xhwacha", "#N,#p,#d,#A", MATCH_VLABU,MASK_VLABU, match_opcode, 0},
/* xstores */
{"vsad",       "Xhwacha", "#N,#p,#A,#T", MATCH_VSAD, MASK_VSAD, match_opcode, 0},
{"vsaw",       "Xhwacha", "#N,#p,#A,#T", MATCH_VSAW, MASK_VSAW, match_opcode, 0},
{"vsah",       "Xhwacha", "#N,#p,#A,#T", MATCH_VSAH, MASK_VSAH, match_opcode, 0},
{"vsab",       "Xhwacha", "#N,#p,#A,#T", MATCH_VSAB, MASK_VSAB, match_opcode, 0},

/* Vector-vector ut operations */
{"vandi",      "I",   "#d,#s,#j",  MATCH_VANDI, MASK_VANDI, match_opcode,   WR_xd|RD_xs1 },
{"vand",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VAND, MASK_VAND, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vand",       "I",   "#d,#s,#j",  MATCH_VANDI, MASK_VANDI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vaddi",      "I",   "#d,#s,#j",  MATCH_VADDI, MASK_VADDI, match_opcode,  WR_xd|RD_xs1 },
{"vadd",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VADD, MASK_VADD, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vadd",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t,0",MATCH_VADD, MASK_VADD, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vadd",       "I",   "#d,#s,#j",  MATCH_VADDI, MASK_VADDI, match_opcode,  INSN_ALIAS|WR_xd|RD_xs1 },
{"vslli",      "I",   "#d,#s,#>",   MATCH_VSLLI, MASK_VSLLI, match_opcode,   WR_xd|RD_xs1 },
{"vsll",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSLL, MASK_VSLL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsll",       "I",   "#d,#s,#>",   MATCH_VSLLI, MASK_VSLLI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsrli",      "I",   "#d,#s,#>",   MATCH_VSRLI, MASK_VSRLI, match_opcode,   WR_xd|RD_xs1 },
{"vsrl",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSRL, MASK_VSRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsrl",       "I",   "#d,#s,#>",   MATCH_VSRLI, MASK_VSRLI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsrai",      "I",   "#d,#s,#>",   MATCH_VSRAI, MASK_VSRAI, match_opcode,   WR_xd|RD_xs1 },
{"vsra",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSRA, MASK_VSRA, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsra",       "I",   "#d,#s,#>",   MATCH_VSRAI, MASK_VSRAI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsub",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VSUB, MASK_VSUB, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vori",       "I",   "#d,#s,#j",  MATCH_VORI, MASK_VORI, match_opcode,   WR_xd|RD_xs1 },
{"vor",        "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VOR, MASK_VOR, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vor",        "I",   "#d,#s,#j",  MATCH_VORI, MASK_VORI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vseqz",      "I",   "#d,#s",  MATCH_VSLTIU | ENCODE_ITYPE_VIMM(1), MASK_VSLTIU | MASK_VIMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsnez",      "I",   "#N,#p,#v,#w,#x,#d,#t",  MATCH_VSLTU, MASK_VSLTU | MASK_VRS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 },
{"vsltz",      "I",   "#N,#p,#v,#w,#x,#d,#s",  MATCH_VSLT, MASK_VSLT | MASK_VRS2, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsgtz",      "I",   "#N,#p,#v,#w,#x,#d,#t",  MATCH_VSLT, MASK_VSLT | MASK_VRS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 },
{"vslti",      "I",   "#d,#s,#j",  MATCH_VSLTI, MASK_VSLTI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vslt",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VSLT, MASK_VSLT, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vslt",       "I",   "#d,#s,#j",  MATCH_VSLTI, MASK_VSLTI, match_opcode,   WR_xd|RD_xs1 },
{"vsltiu",     "I",   "#d,#s,#j",  MATCH_VSLTIU, MASK_VSLTIU, match_opcode,   WR_xd|RD_xs1 },
{"vsltu",      "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VSLTU, MASK_VSLTU, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsltu",      "I",   "#d,#s,#j",  MATCH_VSLTIU, MASK_VSLTIU, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsgt",       "I",   "#N,#p,#v,#w,#x,#d,#t,#s",  MATCH_VSLT, MASK_VSLT, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1|RD_xs2 },
{"vsgtu",      "I",   "#N,#p,#v,#w,#x,#d,#t,#s",  MATCH_VSLTU, MASK_VSLTU, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1|RD_xs2 },
{"vxori",      "I",   "#d,#s,#j",  MATCH_VXORI, MASK_VXORI, match_opcode,   WR_xd|RD_xs1 },
{"vxor",       "I",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VXOR, MASK_VXOR, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vxor",       "I",   "#d,#s,#j",  MATCH_VXORI, MASK_VXORI, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsext.w",    "64I", "#d,#s",  MATCH_VADDIW, MASK_VADDIW | MASK_VIMM, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vaddiw",     "64I", "#d,#s,#j",  MATCH_VADDIW, MASK_VADDIW, match_opcode,   WR_xd|RD_xs1 },
{"vaddw",      "64I", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VADDW, MASK_VADDW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vaddw",      "64I", "#d,#s,#j",  MATCH_VADDIW, MASK_VADDIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vnegw",      "64I", "#N,#p,#v,#w,#x,#d,#t",  MATCH_VSUBW, MASK_VSUBW | MASK_VRS1, match_opcode,   INSN_ALIAS|WR_xd|RD_xs2 }, /* sub 0 */
{"vslliw",     "64I", "#d,#s,#<",   MATCH_VSLLIW, MASK_VSLLIW, match_opcode,   WR_xd|RD_xs1 },
{"vsllw",      "64I", "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSLLW, MASK_VSLLW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsllw",      "64I", "#d,#s,#<",   MATCH_VSLLIW, MASK_VSLLIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsrliw",     "64I", "#d,#s,#<",   MATCH_VSRLIW, MASK_VSRLIW, match_opcode,   WR_xd|RD_xs1 },
{"vsrlw",      "64I", "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSRLW, MASK_VSRLW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsrlw",      "64I", "#d,#s,#<",   MATCH_VSRLIW, MASK_VSRLIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsraiw",     "64I", "#d,#s,#<",   MATCH_VSRAIW, MASK_VSRAIW, match_opcode,   WR_xd|RD_xs1 },
{"vsraw",      "64I", "#N,#p,#v,#w,#x,#d,#s,#t",   MATCH_VSRAW, MASK_VSRAW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vsraw",      "64I", "#d,#s,#<",   MATCH_VSRAIW, MASK_VSRAIW, match_opcode,   INSN_ALIAS|WR_xd|RD_xs1 },
{"vsubw",      "64I", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VSUBW, MASK_VSUBW, match_opcode,   WR_xd|RD_xs1|RD_xs2 },

/* Vector Comparison worker-thread operations */
{"vcmpeq",  "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPEQ, MASK_VCMPEQ, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vcmplt",  "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPLT, MASK_VCMPLT, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vcmpltu", "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPLTU, MASK_VCMPLTU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },

/* Vector predicate register load/stores */
{"vpl", "Xhwacha", "#N,#p,#F,#A", MATCH_VPL, MASK_VPL, match_opcode, 0},
{"vps", "Xhwacha", "#N,#p,#F,#A", MATCH_VPS, MASK_VPS, match_opcode, 0},

/* Vector predicate register arithmetic */
{"vpop",     "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q,#z", MATCH_VPOP, MASK_VPOP, match_opcode, 0 },
{"vpclear",  "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPCLEAR, MASK_VPCLEAR, match_opcode, 0 },
{"vpset",    "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPSET, MASK_VPSET, match_opcode, 0 },
{"vpxorxor", "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPXORXOR, MASK_VPXORXOR, match_opcode, 0 },
{"vpxorand", "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPXORAND, MASK_VPXORAND, match_opcode, 0 },
{"vpxoror",  "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPXOROR, MASK_VPXOROR, match_opcode, 0 },
{"vandxor",  "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPANDXOR, MASK_VPANDXOR, match_opcode, 0 },
{"vandand",  "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPANDAND, MASK_VPANDAND, match_opcode, 0 },
{"vandor",   "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPANDOR, MASK_VPANDOR, match_opcode, 0 },
{"vorxor",   "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPORXOR, MASK_VPORXOR, match_opcode, 0 },
{"vorand",   "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPORAND, MASK_VPORAND, match_opcode, 0 },
{"voror",    "Xhwacha",   "#N,#p,#w,#x,#y,#F,#O,#P,#Q",    MATCH_VPOROR, MASK_VPOROR, match_opcode, 0 },

/* Atomic memory operation instruction subset */
{"vamoadd.w",     "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_W, MASK_VAMOADD_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.w",    "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_W, MASK_VAMOSWAP_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.w",     "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_W, MASK_VAMOAND_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.w",      "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_W, MASK_VAMOOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.w",     "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_W, MASK_VAMOXOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.w",     "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_W, MASK_VAMOMAX_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.w",    "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_W, MASK_VAMOMAXU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.w",     "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_W, MASK_VAMOMIN_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.w",    "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_W, MASK_VAMOMINU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.w.aq",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_W | MASK_VAQ, MASK_VAMOADD_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.w.aq", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_W | MASK_VAQ, MASK_VAMOSWAP_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.w.aq",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_W | MASK_VAQ, MASK_VAMOAND_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.w.aq",   "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_W | MASK_VAQ, MASK_VAMOOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.w.aq",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_W | MASK_VAQ, MASK_VAMOXOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.w.aq",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_W | MASK_VAQ, MASK_VAMOMAX_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.w.aq", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_W | MASK_VAQ, MASK_VAMOMAXU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.w.aq",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_W | MASK_VAQ, MASK_VAMOMIN_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.w.aq", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_W | MASK_VAQ, MASK_VAMOMINU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.w.rl",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_W | MASK_VRL, MASK_VAMOADD_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.w.rl", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_W | MASK_VRL, MASK_VAMOSWAP_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.w.rl",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_W | MASK_VRL, MASK_VAMOAND_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.w.rl",   "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_W | MASK_VRL, MASK_VAMOOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.w.rl",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_W | MASK_VRL, MASK_VAMOXOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.w.rl",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_W | MASK_VRL, MASK_VAMOMAX_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.w.rl", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_W | MASK_VRL, MASK_VAMOMAXU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.w.rl",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_W | MASK_VRL, MASK_VAMOMIN_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.w.rl", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_W | MASK_VRL, MASK_VAMOMINU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.w.sc",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_W | MASK_VAQRL, MASK_VAMOADD_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.w.sc", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_W | MASK_VAQRL, MASK_VAMOSWAP_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.w.sc",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_W | MASK_VAQRL, MASK_VAMOAND_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.w.sc",   "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_W | MASK_VAQRL, MASK_VAMOOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.w.sc",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_W | MASK_VAQRL, MASK_VAMOXOR_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.w.sc",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_W | MASK_VAQRL, MASK_VAMOMAX_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.w.sc", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_W | MASK_VAQRL, MASK_VAMOMAXU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.w.sc",  "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_W | MASK_VAQRL, MASK_VAMOMIN_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.w.sc", "A",   "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_W | MASK_VAQRL, MASK_VAMOMINU_W | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.d",     "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_D, MASK_VAMOADD_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.d",    "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_D, MASK_VAMOSWAP_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.d",     "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_D, MASK_VAMOAND_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.d",      "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_D, MASK_VAMOOR_D | MASK_VAQRL, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vamoxor.d",     "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_D, MASK_VAMOXOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.d",     "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_D, MASK_VAMOMAX_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.d",    "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_D, MASK_VAMOMAXU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.d",     "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_D, MASK_VAMOMIN_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.d",    "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_D, MASK_VAMOMINU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.d.aq",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_D | MASK_VAQ, MASK_VAMOADD_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.d.aq", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_D | MASK_VAQ, MASK_VAMOSWAP_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.d.aq",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_D | MASK_VAQ, MASK_VAMOAND_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.d.aq",   "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_D | MASK_VAQ, MASK_VAMOOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.d.aq",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_D | MASK_VAQ, MASK_VAMOXOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.d.aq",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_D | MASK_VAQ, MASK_VAMOMAX_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.d.aq", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_D | MASK_VAQ, MASK_VAMOMAXU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.d.aq",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_D | MASK_VAQ, MASK_VAMOMIN_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.d.aq", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_D | MASK_VAQ, MASK_VAMOMINU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.d.rl",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_D | MASK_VRL, MASK_VAMOADD_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.d.rl", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_D | MASK_VRL, MASK_VAMOSWAP_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.d.rl",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_D | MASK_VRL, MASK_VAMOAND_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.d.rl",   "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_D | MASK_VRL, MASK_VAMOOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.d.rl",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_D | MASK_VRL, MASK_VAMOXOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.d.rl",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_D | MASK_VRL, MASK_VAMOMAX_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.d.rl", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_D | MASK_VRL, MASK_VAMOMAXU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.d.rl",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_D | MASK_VRL, MASK_VAMOMIN_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.d.rl", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_D | MASK_VRL, MASK_VAMOMINU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoadd.d.sc",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOADD_D | MASK_VAQRL, MASK_VAMOADD_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoswap.d.sc", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOSWAP_D | MASK_VAQRL, MASK_VAMOSWAP_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoand.d.sc",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOAND_D | MASK_VAQRL, MASK_VAMOAND_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoor.d.sc",   "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOOR_D | MASK_VAQRL, MASK_VAMOOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamoxor.d.sc",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOXOR_D | MASK_VAQRL, MASK_VAMOXOR_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomax.d.sc",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAX_D | MASK_VAQRL, MASK_VAMOMAX_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomaxu.d.sc", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMAXU_D | MASK_VAQRL, MASK_VAMOMAXU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamomin.d.sc",  "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMIN_D | MASK_VAQRL, MASK_VAMOMIN_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },
{"vamominu.d.sc", "64A", "#N,#p,#v,#x,#w,#d,#t,0(#s)",  MATCH_VAMOMINU_D | MASK_VAQRL, MASK_VAMOMINU_D | MASK_VAQRL, match_opcode,   WR_xd|RD_xs1|RD_xs2 },

/* Multiply/Divide instruction subset */
{"vmul",       "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VMUL, MASK_VMUL, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vmulh",      "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VMULH, MASK_VMULH, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vmulhu",     "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VMULHU, MASK_VMULHU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vmulhsu",    "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VMULHSU, MASK_VMULHSU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vdiv",       "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VDIV, MASK_VDIV, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vdivu",      "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VDIVU, MASK_VDIVU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vrem",       "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VREM, MASK_VREM, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vremu",      "M",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VREMU, MASK_VREMU, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vmulw",      "64M", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VMULW, MASK_VMULW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vdivw",      "64M", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VDIVW, MASK_VDIVW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vdivuw",     "64M", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VDIVUW, MASK_VDIVUW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vremw",      "64M", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VREMW, MASK_VREMW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },
{"vremuw",     "64M", "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VREMUW, MASK_VREMUW, match_opcode,  WR_xd|RD_xs1|RD_xs2 },

/* Single-precision floating-point instruction subset */
{"vfmv.s",     "F",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJ_S, MASK_VFSGNJ_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfneg.s",    "F",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJN_S, MASK_VFSGNJN_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfabs.s",    "F",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJX_S, MASK_VFSGNJX_S, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfsgnj.s",   "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJ_S, MASK_VFSGNJ_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjn.s",  "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJN_S, MASK_VFSGNJN_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjx.s",  "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJX_S, MASK_VFSGNJX_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfadd.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_S | MASK_VRM, MASK_VFADD_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfadd.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_S, MASK_VFADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsub.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_S | MASK_VRM, MASK_VFSUB_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsub.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_S, MASK_VFSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmul.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_S | MASK_VRM, MASK_VFMUL_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmul.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_S, MASK_VFMUL_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFDIV_S | MASK_VRM, MASK_VFDIV_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFDIV_S, MASK_VFDIV_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsqrt.s",   "F",   "#N,#p,#v,#w,#d,#s",  MATCH_VFSQRT_S | MASK_VRM, MASK_VFSQRT_S | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfsqrt.s",   "F",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFSQRT_S, MASK_VFSQRT_S, match_opcode,  WR_fd|RD_fs1 },
{"vfmin.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMIN_S, MASK_VFMIN_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmax.s",    "F",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMAX_S, MASK_VFMAX_S, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmadd.s",   "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMADD_S | MASK_VRM, MASK_VFMADD_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmadd.s",   "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMADD_S, MASK_VFMADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.s",  "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMADD_S | MASK_VRM, MASK_VFNMADD_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.s",  "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMADD_S, MASK_VFNMADD_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.s",   "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMSUB_S | MASK_VRM, MASK_VFMSUB_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.s",   "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMSUB_S, MASK_VFMSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.s",  "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMSUB_S | MASK_VRM, MASK_VFNMSUB_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.s",  "F",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMSUB_S, MASK_VFNMSUB_S, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfclass.s",  "F",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCLASS_S, MASK_VFCLASS_S, match_opcode,   WR_xd|RD_fs1 },
{"vcmpfeq.s",  "F",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFEQ_S, MASK_VCMPFEQ_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpflt.s",  "F",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLT_S, MASK_VCMPFLT_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfle.s",  "F",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLE_S, MASK_VCMPFLE_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfgt.s",  "F",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLT_S, MASK_VCMPFLT_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfge.s",  "F",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLE_S, MASK_VCMPFLE_S, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vfcvt.w.s",  "F",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_W_S | MASK_VRM, MASK_VFCVT_W_S | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.w.s",  "F",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_W_S, MASK_VFCVT_W_S, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.s", "F",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_WU_S | MASK_VRM, MASK_VFCVT_WU_S | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.s", "F",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_WU_S, MASK_VFCVT_WU_S, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.s.w",  "F",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_S_W | MASK_VRM, MASK_VFCVT_S_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.w",  "F",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_S_W, MASK_VFCVT_S_W, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.wu", "F",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_S_WU | MASK_VRM, MASK_VFCVT_S_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.wu", "F",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_S_WU, MASK_VFCVT_S_WU, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.l.s",  "64F", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_L_S | MASK_VRM, MASK_VFCVT_L_S | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.l.s",  "64F", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_L_S, MASK_VFCVT_L_S, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.s", "64F", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_LU_S | MASK_VRM, MASK_VFCVT_LU_S | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.s", "64F", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_LU_S, MASK_VFCVT_LU_S, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.s.l",  "64F", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_S_L | MASK_VRM, MASK_VFCVT_S_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.l",  "64F", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_S_L, MASK_VFCVT_S_L, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.lu", "64F", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_S_LU | MASK_VRM, MASK_VFCVT_S_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.s.lu", "64F", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_S_LU, MASK_VFCVT_S_LU, match_opcode,   WR_fd|RD_xs1 },

/* Double-precision floating-point instruction subset */
{"vfmv.d",     "D",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJ_D, MASK_VFSGNJ_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfneg.d",    "D",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJN_D, MASK_VFSGNJN_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfabs.d",    "D",   "#N,#p,#v,#w,#x,#d,#u",  MATCH_VFSGNJX_D, MASK_VFSGNJX_D, match_rs1_eq_rs2,   INSN_ALIAS|WR_fd|RD_fs1|RD_fs2 },
{"vfsgnj.d",   "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJ_D, MASK_VFSGNJ_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjn.d",  "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJN_D, MASK_VFSGNJN_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjx.d",  "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJX_D, MASK_VFSGNJX_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfadd.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_D | MASK_VRM, MASK_VFADD_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfadd.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_D, MASK_VFADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_D | MASK_VRM, MASK_VFSUB_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_D, MASK_VFSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_D | MASK_VRM, MASK_VFMUL_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_D, MASK_VFMUL_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFDIV_D | MASK_VRM, MASK_VFDIV_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFDIV_D, MASK_VFDIV_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfsqrt.d",   "D",   "#N,#p,#v,#w,#d,#s",  MATCH_VFSQRT_D | MASK_VRM, MASK_VFSQRT_D | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfsqrt.d",   "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFSQRT_D, MASK_VFSQRT_D, match_opcode,  WR_fd|RD_fs1 },
{"vfmin.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMIN_D, MASK_VFMIN_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmax.d",    "D",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMAX_D, MASK_VFMAX_D, match_opcode,   WR_fd|RD_fs1|RD_fs2 },
{"vfmadd.d",   "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMADD_D | MASK_VRM, MASK_VFMADD_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmadd.d",   "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMADD_D, MASK_VFMADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.d",  "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMADD_D | MASK_VRM, MASK_VFNMADD_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.d",  "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMADD_D, MASK_VFNMADD_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.d",   "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMSUB_D | MASK_VRM, MASK_VFMSUB_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.d",   "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMSUB_D, MASK_VFMSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.d",  "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMSUB_D | MASK_VRM, MASK_VFNMSUB_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.d",  "D",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMSUB_D, MASK_VFNMSUB_D, match_opcode,   WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfcvt.d.s",  "D",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_D_S, MASK_VFCVT_D_S | MASK_VRM, match_opcode,   WR_fd|RD_fs1 },
{"vfcvt.s.d",  "D",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_S_D | MASK_VRM, MASK_VFCVT_S_D | MASK_VRM, match_opcode,   WR_fd|RD_fs1 },
{"vfcvt.s.d",  "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_S_D, MASK_VFCVT_S_D, match_opcode,   WR_fd|RD_fs1 },
{"vfclass.d",  "D",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCLASS_D, MASK_VFCLASS_D, match_opcode,   WR_xd|RD_fs1 },
{"vcmpfeq.d",  "D",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFEQ_D, MASK_VCMPFEQ_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpflt.d",  "D",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLT_D, MASK_VCMPFLT_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfle.d",  "D",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLE_D, MASK_VCMPFLE_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfgt.d",  "D",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLT_D, MASK_VCMPFLT_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vcmpfge.d",  "D",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLE_D, MASK_VCMPFLE_D, match_opcode,  WR_xd|RD_fs1|RD_fs2 },
{"vfcvt.w.d",  "D",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_W_D | MASK_VRM, MASK_VFCVT_W_D | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.w.d",  "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_W_D, MASK_VFCVT_W_D, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.d", "D",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_WU_D | MASK_VRM, MASK_VFCVT_WU_D | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.d", "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_WU_D, MASK_VFCVT_WU_D, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.d.w",  "D",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_D_W | MASK_VRM, MASK_VFCVT_D_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.w",  "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_D_W, MASK_VFCVT_D_W, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.wu", "D",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_D_WU | MASK_VRM, MASK_VFCVT_D_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.wu", "D",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_D_WU, MASK_VFCVT_D_WU, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.l.d",  "64D", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_L_D | MASK_VRM, MASK_VFCVT_L_D | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.l.d",  "64D", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_L_D, MASK_VFCVT_L_D, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.d", "64D", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_LU_D | MASK_VRM, MASK_VFCVT_LU_D | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.d", "64D", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_LU_D, MASK_VFCVT_LU_D, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.d.l",  "64D", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_D_L | MASK_VRM, MASK_VFCVT_D_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.l",  "64D", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_D_L, MASK_VFCVT_D_L, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.lu", "64D", "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_D_LU | MASK_VRM, MASK_VFCVT_D_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.d.lu", "64D", "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_D_LU, MASK_VFCVT_D_LU, match_opcode,   WR_fd|RD_xs1 },

/* Half-precision floating-point instruction subset */
{"vfsgnj.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJ_H, MASK_VFSGNJ_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjn.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJN_H, MASK_VFSGNJN_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsgnjx.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSGNJX_H, MASK_VFSGNJX_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_H | MASK_VRM, MASK_VFADD_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_H, MASK_VFADD_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_H | MASK_VRM, MASK_VFSUB_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_H, MASK_VFSUB_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_H | MASK_VRM, MASK_VFMUL_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_H, MASK_VFMUL_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFDIV_H | MASK_VRM, MASK_VFDIV_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfdiv.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFDIV_H, MASK_VFDIV_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsqrt.h",   "Xhwacha",   "#N,#p,#v,#w,#d,#s",  MATCH_VFSQRT_H | MASK_VRM, MASK_VFSQRT_H | MASK_VRM, match_opcode, WR_fd|RD_fs1 },
{"vfsqrt.h",   "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFSQRT_H, MASK_VFSQRT_H, match_opcode, WR_fd|RD_fs1 },
{"vfmin.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMIN_H, MASK_VFMIN_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmax.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMAX_H, MASK_VFMAX_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmadd.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMADD_H | MASK_VRM, MASK_VFMADD_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmadd.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMADD_H, MASK_VFMADD_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMADD_H | MASK_VRM, MASK_VFNMADD_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMADD_H, MASK_VFNMADD_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMSUB_H | MASK_VRM, MASK_VFMSUB_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMSUB_H, MASK_VFMSUB_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMSUB_H | MASK_VRM, MASK_VFNMSUB_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMSUB_H, MASK_VFNMSUB_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfcvt.s.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_S_H, MASK_VFCVT_S_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfcvt.h.s",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_H_S | MASK_VRM, MASK_VFCVT_H_S | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfcvt.h.s",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_S, MASK_VFCVT_H_S, match_opcode,  WR_fd|RD_fs1 },
{"vfcvt.d.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_D_H, MASK_VFCVT_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfcvt.h.d",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",  MATCH_VFCVT_H_D | MASK_VRM, MASK_VFCVT_H_D | MASK_VRM, match_opcode,  WR_fd|RD_fs1 },
{"vfcvt.h.d",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_D, MASK_VFCVT_H_D, match_opcode,  WR_fd|RD_fs1 },
{"vcmpfeq.h",  "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFEQ_H, MASK_VCMPFEQ_H, match_opcode, WR_xd|RD_fs1|RD_fs2 },
{"vcmpflt.h",  "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLT_H, MASK_VCMPFLT_H, match_opcode, WR_xd|RD_fs1|RD_fs2 },
{"vcmpfle.h",  "Xhwacha",   "#N,#p,#w,#x,#F,#s,#t",    MATCH_VCMPFLE_H, MASK_VCMPFLE_H, match_opcode, WR_xd|RD_fs1|RD_fs2 },
{"vcmpfgt.h",  "Xhwacha",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLT_H, MASK_VCMPFLT_H, match_opcode, WR_xd|RD_fs1|RD_fs2 },
{"vcmpfge.h",  "Xhwacha",   "#N,#p,#w,#x,#F,#t,#s",    MATCH_VCMPFLE_H, MASK_VCMPFLE_H, match_opcode, WR_xd|RD_fs1|RD_fs2 },
{"vfcvt.w.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_W_H | MASK_VRM, MASK_VFCVT_W_H | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.w.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_W_H, MASK_VFCVT_W_H, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.h", "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_WU_H | MASK_VRM, MASK_VFCVT_WU_H | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.wu.h", "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_WU_H, MASK_VFCVT_WU_H, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.h.w",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_H_W | MASK_VRM, MASK_VFCVT_H_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.w",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_W, MASK_VFCVT_H_W, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.wu", "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_H_WU | MASK_VRM, MASK_VFCVT_H_W | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.wu", "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_WU, MASK_VFCVT_H_WU, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.l.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_L_H | MASK_VRM, MASK_VFCVT_L_H | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.l.h",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_L_H, MASK_VFCVT_L_H, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.h", "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_LU_H | MASK_VRM, MASK_VFCVT_LU_H | MASK_VRM, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.lu.h", "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_LU_H, MASK_VFCVT_LU_H, match_opcode,  WR_xd|RD_fs1 },
{"vfcvt.h.l",  "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_H_L | MASK_VRM, MASK_VFCVT_H_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.l",  "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_L, MASK_VFCVT_H_L, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.lu", "Xhwacha",   "#N,#p,#v,#w,#d,#s",     MATCH_VFCVT_H_LU | MASK_VRM, MASK_VFCVT_H_L | MASK_VRM, match_opcode,   WR_fd|RD_xs1 },
{"vfcvt.h.lu", "Xhwacha",   "#N,#p,#v,#w,#d,#s,#m",  MATCH_VFCVT_H_LU, MASK_VFCVT_H_LU, match_opcode,   WR_fd|RD_xs1 },

/* Mixed-precision floating-point instruction subset */
{"vfadd.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_S_H | MASK_VRM, MASK_VFADD_S_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_S_H, MASK_VFADD_S_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_S_H | MASK_VRM, MASK_VFSUB_S_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_S_H, MASK_VFSUB_S_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_S_H | MASK_VRM, MASK_VFMUL_S_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.s.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_S_H, MASK_VFMUL_S_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_D_H | MASK_VRM, MASK_VFADD_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_D_H, MASK_VFADD_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_D_H | MASK_VRM, MASK_VFSUB_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_D_H, MASK_VFSUB_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_D_H | MASK_VRM, MASK_VFMUL_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d.h",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_D_H, MASK_VFMUL_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmadd.d.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMADD_D_H | MASK_VRM, MASK_VFMADD_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmadd.d.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMADD_D_H, MASK_VFMADD_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.d.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMADD_D_H | MASK_VRM, MASK_VFNMADD_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmadd.d.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMADD_D_H, MASK_VFNMADD_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.d.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFMSUB_D_H | MASK_VRM, MASK_VFMSUB_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfmsub.d.h",   "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFMSUB_D_H, MASK_VFMSUB_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.d.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r",  MATCH_VFNMSUB_D_H | MASK_VRM, MASK_VFNMSUB_D_H | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfnmsub.d.h",  "Xhwacha",   "#N,#p,#v,#w,#x,#y,#d,#s,#t,#r,#m",  MATCH_VFNMSUB_D_H, MASK_VFNMSUB_D_H, match_opcode,  WR_fd|RD_fs1|RD_fs2|RD_fs3 },
{"vfadd.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFADD_D_S | MASK_VRM, MASK_VFADD_D_S | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfadd.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFADD_D_S, MASK_VFADD_D_S, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFSUB_D_S | MASK_VRM, MASK_VFSUB_D_S | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfsub.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFSUB_D_S, MASK_VFSUB_D_S, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t",  MATCH_VFMUL_D_S | MASK_VRM, MASK_VFMUL_D_S | MASK_VRM, match_opcode,  WR_fd|RD_fs1|RD_fs2 },
{"vfmul.d.s",    "Xhwacha",   "#N,#p,#v,#w,#x,#d,#s,#t,#m",  MATCH_VFMUL_D_S, MASK_VFMUL_D_S, match_opcode,  WR_fd|RD_fs1|RD_fs2 },

};

#define RISCV_NUM_OPCODES \
  ((sizeof riscv_builtin_opcodes) / (sizeof (riscv_builtin_opcodes[0])))
const int bfd_riscv_num_builtin_opcodes = RISCV_NUM_OPCODES;

/* const removed from the following to allow for dynamic extensions to the
 * built-in instruction set. */
struct riscv_opcode *riscv_opcodes =
  (struct riscv_opcode *) riscv_builtin_opcodes;
int bfd_riscv_num_opcodes = RISCV_NUM_OPCODES;
#undef RISCV_NUM_OPCODES
