#include <Processor.h>

#include <gtest/gtest.h>

#include <vector>

static const std::vector<uint8_t> kChip8Fontset = {
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

class Chip8Test : public testing::Test {
public:

protected:
  Chip8Processor m_processor;

  void SetUp() override {
    m_processor.reset();
  }

  void TearDown() override {

  }

  void returnTest();
  void callTest();
  void resetTest();
  void fetchTest();
  void jumpTest();
private:
};

////////////////////////////////////////////////////////////////////////////////
void Chip8Test::returnTest() {
  const uint16_t address = 0x023A;
  const uint16_t pc = 0x0200;
  const uint8_t sp = 9;

  // Set the PC and stack pointer to known values
  m_processor.m_pc = pc;
  m_processor.m_sp = sp;
  m_processor.m_stack[sp - 1] = address;

  m_processor.execute(0x00EE);

  // The return instruction should pop the address off the top of the stack and
  // set the PC to that value
  EXPECT_EQ(address, m_processor.m_pc);
  EXPECT_EQ(sp - 1, m_processor.m_sp);
}

void Chip8Test::callTest() {
  const uint16_t address = 0x0234;
  const uint16_t pc = 0x0200;
  const uint8_t sp = 5;

  // Set the PC and stack pointer to known values
  m_processor.m_pc = pc;
  m_processor.m_sp = sp;
  m_processor.m_stack[sp] = 0x0000;

  uint16_t instruction = 0x2000 | address;
  m_processor.execute(instruction);

  // The call instruction should set the PC to the given address and should push
  // the address of the PC prior to the "call" on to the top of the stack.
  EXPECT_EQ(address, m_processor.m_pc);
  EXPECT_EQ(sp + 1, m_processor.m_sp);
  EXPECT_EQ(pc, m_processor.m_stack[sp]);
}

void Chip8Test::jumpTest() {
  const uint16_t address = 0x0236;

  // Set the PC to a known value.  The jump should change this.
  m_processor.m_pc = 0x0200;

  uint16_t instruction = 0x1000 | address;
  m_processor.execute(instruction);

  // The jump instruction to set the PC to the address that was given with the
  // instruction.
  EXPECT_EQ(address, m_processor.m_pc);
}

void Chip8Test::fetchTest() {
  const uint16_t address = 0x0200;

  // Set up a random instruction at a known address.
  m_processor.m_memory[address] = 0xAA;
  m_processor.m_memory[address + 1] = 0xBB;

  // Read back the instruction that was just put in the processor's RAM
  uint16_t instruction = m_processor.fetch(address);

  // Make sure that the instruction that was read out is correct.  The upper byte
  // should be equal to the byte that we set at the index "address" and the lower
  // byte should be equal to the byte that we set at the index "address + 1"
  EXPECT_EQ(0xAA, instruction >> 8);
  EXPECT_EQ(0xBB, instruction & 0xFF);
}

void Chip8Test::resetTest() {
  // Make sure that the PC is initialzed correctly.  0x200 is the address of the
  // first ROM instruction, so the PC should point there after reset
  EXPECT_EQ(0x200, m_processor.m_pc);

  // The first 80 bytes of RAM should contain the fontset, which is made up of 16
  // 8x5 sprites for use by ROMs
  for (size_t i = 0; i < kChip8Fontset.size(); i++) {
    EXPECT_EQ(kChip8Fontset.at(i), m_processor.m_memory.at(i));
  }

  // The sound and delay registers should be set to 0 on reset.  A non-zero value
  // triggers actions by the processor hardware.
  EXPECT_EQ(0, m_processor.m_delay);
  EXPECT_EQ(0, m_processor.m_timer);

  // The stack pointer should be initialized to point to the top of the stack
  EXPECT_EQ(0, m_processor.m_pc);
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(Chip8Test, TestReset) {
  resetTest();
}
TEST_F(Chip8Test, TestFetch) {
  fetchTest();
}
TEST_F(Chip8Test, TestJump) {
  jumpTest();
}
TEST_F(Chip8Test, TestCall) {
  callTest();
}
TEST_F(Chip8Test, TestReturn) {
  returnTest();
}
