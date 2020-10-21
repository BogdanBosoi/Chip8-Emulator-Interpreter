#include "Chip8.hpp"
#include <intrin.h>

void Chip8::initialize()
{
	srand(time(NULL));
	pc = 0x200;		// pc pleaca de la 512
	opcode = 0;
	I = 0;
	sp = 0;
	debugTest = 0;

	// Clear display

	std::memset(gfx, 0, sizeof gfx);

	// Clear stack

	std::memset(stack, 0, sizeof stack);

	// Clear registers V0-VF

	std::memset(V, 0, sizeof V);

	// Clear memory

	std::memset(memory, 0, sizeof memory);

	// Load fontset

	for (int i = 0; i < 80; memory[i] = chip8_fontset[i++]);

	// Reset timers
	delay_timer = 0;
	sound_timer = 0;

	render = true;
}

void Chip8::emulateCycle()
{
	// fetch opcode
	/*if(debugTest == 0)*/
		opcode = (memory[pc] << 8) | memory[pc + 1];
	// decode opcode
	
	switch (opcode & 0xF000)
	{
		// execute opcodes
		case 0x0000:
		{
			switch (opcode & 0x00FF)
			{
			case 0x0000:
				pc += 2;
				break;
			case 0x00E0:
				op_00E0();
				break;
			case 0x00EE:
				op_00EE();
				break;
			default:
			{
				printf("Unknown opcode: 0x%X\n", opcode);
				pc += 2;
				break;
			}
			}
			break;
		}
		case 0x1000:
			op_1nnn();
			break;
		case 0x2000:
			op_2nnn();
			break;
		case 0x3000:
			op_3xkk();
			break;
		case 0x4000:
			op_4xkk();
			break;
		case 0x5000:
			op_5xy0();
			break;
		case 0x6000:
			op_6xkk();
			break;
		case 0x7000:
			op_7xkk();
			break;
		case 0x8000:
		{
			switch (opcode & 0x000F)
			{
			case 0x0000:
				op_8xy0();
				break;
			case 0x0001:
				op_8xy1();
				break;
			case 0x0002:
				op_8xy2();
				break;
			case 0x0003:
				op_8xy3();
				break;
			case 0x0004:
				op_8xy4();
				break;
			case 0x0005:
				op_8xy5();
				break;
			case 0x0006:
				op_8xy6();
				break;
			case 0x0007:
				op_8xy7();
				break;
			case 0x000E:
				op_8xyE();
				break;
			default:
			{
				printf("Unknown opcode: 0x%X\n", opcode);
				pc += 2;
				break;
			}
			}
			break;
		}

		case 0x9000:
			op_9xy0();
			break;

		case 0xA000:
			op_Annn();
			break;

		case 0xB000:
			op_Bnnn();
			break;

		case 0xC000:
			op_Cxkk();
			break;

		case 0xD000:
			op_Dxyn();
			break;

		case 0xE000:
		{
			switch (opcode & 0x00FF)
			{
			case 0x009E:
				op_Ex9E();
				break;
			case 0x00A1:
				op_ExA1();
				break;
			default:
			{
				printf("Unknown opcode: 0x%X\n", opcode);
				pc += 2;
				break;
			}
			}
			break;
		}

		case 0xF000:
		{
			switch (opcode & 0x00FF)
			{
			case 0x0007:
				op_Fx07();
				break;
			case 0x000A:
				op_Fx0A();
				break;
			case 0x0015:
				op_Fx15();
				break;
			case 0x0018:
				op_Fx18();
				break;
			case 0x001E:
				op_Fx1E();
				break;
			case 0x0029:
				op_Fx29();
				break;
			case 0x0033:
				op_Fx33();
				break;
			case 0x0055:
				op_Fx55();
				break;
			case 0x0065:
				op_Fx65();
				break;
			default:
			{
				printf("Unknown opcode: 0x%X\n", opcode);
				pc += 2;
				break;
			}
			}

			break;

		}

		default: 
		{
			printf("Unknown opcode: 0x%X\n", opcode);
			pc += 2;
			break;
		}
	}



}

void Chip8::loadGame(const char* fileName)
{
	
	FILE* game;
	game = fopen(fileName, "rb+");
	
	if (game == NULL)
		return ;

	fseek(game, 0, SEEK_END);

	unsigned short bufferSize = ftell(game);
	rewind(game);

	unsigned char* buffer = new unsigned char[bufferSize + 1];
	fseek(game, 0, SEEK_SET);
	int result = fread(buffer, 1, bufferSize, game);
	if (result != bufferSize)
	{
		printf("Reading error\n");
		return;
	}
	
	fclose(game);
	for (int i = 0; i < bufferSize; i++)
	{
		memory[i + 512] = buffer[i];
	}
	delete[] buffer;
}
