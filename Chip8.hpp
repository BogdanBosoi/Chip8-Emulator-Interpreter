#pragma once
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cstdio>


class Chip8
{
public:
	static const int CHIP_WIDTH = 64;
	static const int CHIP_HEIGHT = 32;
#define ivoid inline void

	void initialize();

	void emulateCycle();

	void loadGame(const char* fileName);

	unsigned short opcode;			// stocarea opcode-urilor
	unsigned char memory[4096];		// ram-ul

	unsigned char V[16];			// cei 16 registri de general purpose

	unsigned short I;				// index register
	unsigned short pc;				// program counter

	/***************
	Memoria mapata:

	0x000 - 0x1FF - Interpreter-ul de la Chip8 (contine setul de font)
	0x050 - 0x0A0 - Folosit pentru construirea in 4x5 a setului de font (0 - F)
	0x200 - 0xFFF - Program ROM si work RAM


	****************/

	unsigned char gfx[64 * 32];		// memoria grafica
									// consolele pe chip8 au grafica monocroma, deci 1 pt aprins si 0 pt stins

	unsigned char delay_timer;		// registru de count down
	unsigned char sound_timer;		// registru de count down pentru buzzer, cand e 0 bipaie baiatul

	unsigned short stack[16];		// stiva de instructiuni
	unsigned short sp;				// stack pointer-ul

	unsigned char key[16];

	unsigned char chip8_fontset[80] =
	{
	  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	  0x20, 0x60, 0x20, 0x20, 0x70, // 1
	  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	bool render;
	bool debugTest = 0;

private:

	ivoid op_00E0() // Clear screen
	{
		memset(gfx, 0, 2048);
		render = true;
		pc += 2;
	}
	ivoid op_00EE() // Return from a subroutine
	{
		pc = stack[sp--];
		pc += 2;
	}
	ivoid op_1nnn()	// Jump at nnn
	{
		pc = opcode & 0x0FFF;
	}
	ivoid op_2nnn()	// Call subroutine at nnn
	{
		stack[++sp] = pc;
		pc = opcode & 0x0FFF;
	}
	ivoid op_3xkk()	// Skip if V[x] == 0xkk
	{
		if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			pc += 2;
		pc += 2;
	}
	ivoid op_4xkk()	// Skip if V[x] != 0xkk
	{
		if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			pc += 2;
		pc += 2;
	}
	ivoid op_5xy0()	// Skip if V[x] == V[y]
	{
		if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
			pc += 2;
		pc += 2;
	}
	ivoid op_6xkk()	// V[x] = 0xkk
	{
		V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
		pc += 2;
	}
	ivoid op_7xkk()	// V[x] += 0xkk
	{
		V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
		pc += 2;
	}
	ivoid op_8xy0()	// V[x] = V[y]
	{
		V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}
	ivoid op_8xy1()	// V[x] = V[x] | V[y]
	{
		V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}
	ivoid op_8xy2()	// V[x] = V[x] & V[y]
	{
		V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}
	ivoid op_8xy3() // V[x] = V[x] ^ V[y]
	{
		V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}
	ivoid op_8xy4() // V[x] += V[y], if V[x] > 255 then V[f] = 1
	{
		unsigned short val = V[(opcode & 0x00F0) >> 4] + V[(opcode & 0x0F00) >> 8];
		if (val > 255)
			V[0xF] = 1;
		else
			V[0xF] = 0;
		V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}
	ivoid op_8xy5()	// V[x] -= V[y], if V[x] > V[y] then V[f] = 1
	{
		if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])
			V[0xF] = 1;
		else
			V[0xF] = 0;	// there is a borrow

		V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
		pc += 2;
	}

	ivoid op_8xy6()	// V[f] = LSD of V[x], then V[x] is shifted right by one bit
	{
		V[0xF] = (V[(opcode & 0x0F00) >> 8]) & 0x1;
		V[(opcode & 0x0F00) >> 8] >>= 1;
		pc += 2;
	}

	ivoid op_8xy7() // V[y] -= V[x], if V[y] > V[x] then V[f] = 1
	{
		if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])
			V[0xF] = 0; // there is a borrow
		else
			V[0xF] = 1;

		V[(opcode & 0x00F0) >> 4] -= V[(opcode & 0x0F00) >> 8];
		pc += 2;
	}

	ivoid op_8xyE() // V[f] = MSD of V[x], then V[x] is shifted left by one bit
	{
		V[0xF] = (V[(opcode & 0x0F00) >> 8]) >> 7;
		V[(opcode & 0x0F00) >> 8] <<= 1;
		pc += 2;
	}

	ivoid op_9xy0()	// skip if V[x] != V[y]
	{
		if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
			pc += 2;
		pc += 2;
	}

	ivoid op_Annn() // I = nnn
	{
		I = opcode & 0x0FFF;
		pc += 2;
	}

	ivoid op_Bnnn()	// jmp to nnn + V[0]
	{
		pc = (opcode & 0x0FFF) + V[0];
	}
	ivoid op_Cxkk() // V[x] = random byte & kk
	{
		V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
		pc += 2;
	}

	ivoid op_Dxyn()	// draw 8xN sprite at position x, y
	{
		unsigned short n = opcode & 0x000F;
		unsigned short x = V[(opcode & 0x0F00) >> 8] % CHIP_WIDTH;
		unsigned short y = V[(opcode & 0x00F0) >> 4] % CHIP_HEIGHT;
		unsigned short pixel;
		V[0xF] = 0;
		for (int hline = 0; hline < n; hline++)
		{
			pixel = memory[hline + I];
			for (int wline = 0; wline < 8; wline++)
			{
				if (( pixel & (0x80 >> wline)) != 0)
				{
					if (gfx[(x + wline + ((y + hline) * 64))] == 1)
						V[0xF] = 1;
					gfx[(x + wline + ((y + hline) * 64))] ^= 1;
				}
			}
		}
		render = true;
		pc += 2;
	}

	ivoid op_Ex9E()	// skip if key with the value of V[x] is pressed
	{
		if (key[V[(opcode & 0x0F00) >> 8]] != 0)
			pc += 2;
		pc += 2;
	}

	ivoid op_ExA1() // skip if key with the value of V[x] is not pressed
	{
		if (key[V[(opcode & 0x0F00) >> 8]] == 0)
			pc += 2;
		pc += 2;
	}

	ivoid op_Fx07() // V[x] = delay_timer
	{
		V[(opcode & 0x0F00) >> 8] = delay_timer;
		pc += 2;
	}

	ivoid op_Fx0A() // Wait for key press, then return execution
	{
		bool pressed = false;
		for (int i = 0; i < 16; i++)
		{
			if (key[i] != 0)
			{
				V[(opcode & 0x0F00) >> 8] = i;
				pressed = true;
			}
		}

		if (!pressed)
			return;

		pc += 2;
	}

	ivoid op_Fx15() // delay_timer = V[x]
	{
		delay_timer = V[(opcode & 0x0F00) >> 8];
		pc += 2;
	}

	ivoid op_Fx18() // sound_timer = V[x]
	{
		sound_timer = V[(opcode & 0x0F00) >> 8];
		pc += 2;
	}

	ivoid op_Fx1E() // I += V[x]
	{
		I += V[(opcode & 0x0F00) >> 8];
		pc += 2;
	}

	ivoid op_Fx29() // I = gfx[V[x]]
	{
		I = V[(opcode & 0x0F00) >> 8] * 0x05;
		pc += 2;
	}

	ivoid op_Fx33() // memory[I] = V[x] / 100, memory[I+1] = V[x] / 10, memory[I+2] = V[x]
	{
		memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
		memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
		memory[I + 2] = V[(opcode & 0x0F00) >> 8] % 10;
		pc += 2;
	}

	ivoid op_Fx55() // memory[I + i] = V[i], ( 0 <= i <= x )
	{
		for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
			memory[I + i] = V[i];
		
		I += ((opcode & 0x0F00) >> 8) + 1;
		pc += 2;
	}

	ivoid op_Fx65() // V[i] = memory[I + i], (0 <= i <= x)
	{
		for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
			V[i] = memory[I + i];

		I += ((opcode & 0x0F00) >> 8) + 1;
		pc += 2;
	}
};

