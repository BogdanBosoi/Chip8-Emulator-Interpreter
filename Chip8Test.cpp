//#include "catch.hpp"
//
//#include "Chip8.hpp"
//#include <iostream>
//
//TEST_CASE("OPCODE 00E0", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.opcode = 0x00E0;
//	chip8.initialize();
//	
//	chip8.emulateCycle();
//	bool blackScreen = true;
//
//	for (int i = 0; i < 2048; i++)
//		if (chip8.gfx[i] != 0)
//			blackScreen = false;
//
//	REQUIRE(blackScreen == true);
//}
//
//TEST_CASE("OPCODE 00EE", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x00EE;
//	chip8.pc = 0x350;
//	chip8.sp = 4;
//	chip8.stack[4] = 0x370;
//	
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x370);
//	REQUIRE(chip8.sp == 3);
//}
//
//TEST_CASE("OPCODE 1NNN", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x1234;
//	chip8.pc = 0x0400;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x234);
//}
//
//TEST_CASE("OPCODE 2NNN", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x2234;
//	chip8.pc = 0x0400;
//	chip8.sp = 3;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x234);
//	REQUIRE(chip8.sp == 4);
//	REQUIRE(chip8.stack[4] == 0x0400);
//}
//
//TEST_CASE("OPCODE 3XKK", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x3234;
//
//	chip8.V[2] = 0x0034;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//	REQUIRE(chip8.pc == 0x0404);
//
//	chip8.V[2] = 0x0030;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0402);
//}
//
//TEST_CASE("OPCODE 4XKK", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x4234;
//
//	chip8.V[2] = 0x0034;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0402);
//
//	chip8.V[2] = 0x0030;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0404);
//}
//
//TEST_CASE("OPCODE 5XY0", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x5230;
//	chip8.V[2] = 0x0034;
//	chip8.V[3] = 0x0034;
//	chip8.pc = 0x0400;
//
//	chip8.emulateCycle();
//	REQUIRE(chip8.pc == 0x0404);
//
//	chip8.V[2] = 0x0030;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0402);
//}
//
//TEST_CASE("OPCODE 6XKK", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x6234;
//	chip8.pc = 0x0200;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == 0x0034);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 7XKK", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x7234;
//	chip8.V[2] = 0x0020;
//	chip8.pc = 0x0200;
//	chip8.emulateCycle();
//	
//	REQUIRE(chip8.V[2] == 0x0054);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY0", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8230;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//	chip8.pc = 0x0200;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == chip8.V[3]);
//	REQUIRE(chip8.V[2] == 0x0030);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY1", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8231;
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == (0x0020 | 0x0030));
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY2", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8232;
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == (0x0020 & 0x0030));
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY3", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8233;
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == (0x0020 ^ 0x0030));
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY4", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8234;
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == (0x0020 + 0x0030));
//	REQUIRE(chip8.V[0xF] == 0);
//	REQUIRE(chip8.pc == 0x0202);
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x00FF;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == unsigned char(0x00FF + 0x0030));
//	REQUIRE(chip8.V[0xF] == 1);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY5", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8235;
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == unsigned char(0x0020 - 0x0030));
//	REQUIRE(chip8.V[0xF] == 0);
//	REQUIRE(chip8.pc == 0x0202);
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x00FF;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[2] == unsigned char(0x00FF - 0x0030));
//	REQUIRE(chip8.V[0xF] == 1);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XY6", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8236;
//	chip8.pc = 0x0200;
//	chip8.V[0xF] = 0;
//	chip8.V[2] = 0x0034;
//	chip8.emulateCycle();
//	REQUIRE(chip8.V[0xF] == (0x34 & 0x1));
//	REQUIRE(chip8.pc == 0x0202);
//	REQUIRE(chip8.V[2] == (0x34 >> 1));
//}
//
//TEST_CASE("OPCODE 8XY7", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x8237;
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x0020;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[3] == (0x0030 - 0x0020));
//	REQUIRE(chip8.V[0xF] == 1);
//	REQUIRE(chip8.pc == 0x0202);
//
//	chip8.pc = 0x0200;
//	chip8.V[2] = 0x00FF;
//	chip8.V[3] = 0x0030;
//	chip8.V[0xF] = 0;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.V[3] == unsigned char(0x0030 - 0x00FF));
//	REQUIRE(chip8.V[0xF] == 0);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE 8XYE", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x823E;
//	chip8.pc = 0x0200;
//	chip8.V[0xF] = 0;
//	chip8.V[2] = 0x0034;
//	chip8.emulateCycle();
//	REQUIRE(chip8.V[0xF] == (0x34 & 0x1));
//	REQUIRE(chip8.pc == 0x0202);
//	REQUIRE(chip8.V[2] == (0x34 << 1));
//}
//
//TEST_CASE("OPCODE 9XY0", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0x9230;
//	chip8.V[2] = 0x0034;
//	chip8.V[3] = 0x0034;
//	chip8.pc = 0x0400;
//
//	chip8.emulateCycle();
//	REQUIRE(chip8.pc == 0x0402);
//
//	chip8.V[2] = 0x0030;
//	chip8.pc = 0x0400;
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0404);
//
//}
//
//TEST_CASE("OPCODE ANNN", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0xA234;
//	chip8.pc = 0x0200;
//
//	chip8.emulateCycle();
//	
//	REQUIRE(chip8.I == 0x0234);
//	REQUIRE(chip8.pc == 0x0202);
//}
//
//TEST_CASE("OPCODE BNNN", "[opcode]")
//{
//	Chip8 chip8;
//	chip8.initialize();
//	chip8.debugTest = 1;
//	chip8.opcode = 0xB234;
//	chip8.V[0] = 0x0030;
//
//	chip8.pc = 0x0200;
//
//	chip8.emulateCycle();
//
//	REQUIRE(chip8.pc == 0x0264);
//}
