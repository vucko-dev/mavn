

# MAVN Translator

**MAVN Translator** is a tool that translates code written in MAVN (a high-level assembly language developed by the University of Technical Sciences Novi Sad) to MIPS 32-bit language. Here is an example of its output:

This is the MAVN code:

    _mem m1 6;
    _mem m2 5;
    
    _reg r1;
    _reg r2;
    _reg r3;
    _reg r4;
    _reg r5;
    
    _func main;
    	la		r4, m1;
    	lw		r1, 0(r4);
    	la		r5, m2;
    	lw		r2, 0(r5);
    	add		r3, r1, r2;
	
And this is the MIPS code after using MAVN Translator:

    .globl main
    
    .data
    m1:	.word 6
    m2:	.word 5
    
    .text
    main:
    		
    	la		$t0, m1
    	lw		$t1, 0($t0)
    	la		$t0, m2
    	lw		$t0, 0($t0)
    	add		$t0, $t1, $t0
As you can see, the result uses a smaller number of registers to achieve the same functionality.
The translator performs lexical, syntax, and semantic error checking. If any errors are found, it generates a detailed report of the detected errors. From a `.mavn` file, it creates a `.s` file, which can be run as MIPS 32-bit assembly code. Additionally, while creating the `.s` file, the translator optimizes memory usage to be as efficient as possible.

**Detailed documentation is available in the `doc` folder.**
