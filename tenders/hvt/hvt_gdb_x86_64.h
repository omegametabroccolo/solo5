/*
 * Copyright (c) 2015-2019 Contributors as noted in the AUTHORS file
 *
 * This file is part of Solo5, a sandboxed execution environment.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * hvt_gdb_x86_64.h: GDB constants common to x86_64 backend implementations.
 */

#ifndef HVT_GDB_X86_64_H
#define HVT_GDB_X86_64_H

// NOTE:
// structures defined here MUST BE packed in order to avoid padding.
// FPU registers in x86 are 80 bits wide and C compilers WILL insert
// padding otherwise, making serialisation trickier.

// GDB expects FPU registers as 80 bit numbers,
// but C doesn't have a type for this.
struct fpu_reg { unsigned char data[10]; } __attribute__((packed));

#define FPU_REGS 8

/*
 * XXX: While there is no header file in GDB to include here,
 * the register structure is described in XML here:
 * https://sourceware.org/git/?p=binutils-gdb.git;a=blob;f=gdb/features/i386/64bit-core.xml;h=5cbae2c0ef489699fa6c6e8ed07f5fe6d3b8a6b6;hb=HEAD
 */

struct hvt_gdb_regs {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
    // In GDB wire protocol, EFLAGS is 32 bits.
    uint32_t eflags;

    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;

    struct fpu_reg st[FPU_REGS];
    uint32_t fctrl;
    uint32_t fstat;
    uint32_t ftag;
    uint32_t fiseg;
    uint32_t fioff;
    uint32_t foseg;
    uint32_t fooff;
    uint32_t fop;
} __attribute__((packed));

#endif /* HVT_GDB_X86_64_H */
