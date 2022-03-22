#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include <array>
#include <cstdint>
#include <string>

#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_GENERAL_PURPOSE_REGISTER_COUNT 16
#define CHIP8_STACK_SIZE 16

class Chip8Processor {
public:
  /*
   *
   */
  Chip8Processor();
  
  /**
   * Resets the processor back to its intial state.  All of the registers, memory, etc.
   * should be intiialized to their starting values when this function returns
   */
  void reset();

  /**
   * Loads the given ROM in to the memory.  If the given string does not point to a
   * valid ROM file, then the function will return false.  Otherwise, the ROM should be
   * loaded in to the processor's memory when the function returns.
   *
   * @params
   *   rom - path to the ROM file to be loaded
   *
   * @returns
   *   true if the load was successful, otherwise false
   */
  bool load(const std::string& rom);
  
private:
  friend class Chip8Test;

  // Program counter that points to the next instruction to be fetched and executed.
  uint16_t m_pc;

  // 16 bit register.
  uint16_t m_iRegister;

  // Stack pointer that currently points to the top of the stack.
  uint8_t m_sp;

  // 4KB block of RAM
  std::array<uint8_t, CHIP8_MEMORY_SIZE> m_memory;

  // 16 8 bit general purpose registers.  On chip8, they are typically referred to as Vx
  // where x is index of the register that is being accessed.
  std::array<uint8_t, CHIP8_GENERAL_PURPOSE_REGISTER_COUNT> m_v;

  // 16 16 bit slots for the stack, which implies that the function call stack can never
  // exceed 16 functions.
  std::array<uint16_t, CHIP8_STACK_SIZE> m_stack;

  // Delay register.  This value should decrement at 60Hz if it is set to a non-zero
  // value.
  uint8_t m_delay;

  // Timer register.  This value should decrement at 60Hz if it is set to a non-zero
  // value.  As long as it's non-zero, the processor buzzer should play a single tone
  // at a set frequency.
  uint8_t m_timer;

  /**
   * Decodes and executes the opcode in the given instruction.
   *
   * @params
   *   instruction - 16 value holding the instruction to be executed by the processor
   */
  void execute(uint16_t instruction);

  /**
   * Fetches the instruction at the given address.
   *
   * @params
   *   address - the 16 bit address of the instruction to be fetched
   *
   * @returns
   *   The 16 bit instruction pointed to by the given address
   */
  uint16_t fetch(uint16_t address);
};

#endif
