#include "Processor.h"

Chip8Processor::Chip8Processor() {

}

void Chip8Processor::reset() {

}

bool Chip8Processor::load(const std::string& rom) {
  (void)rom;
  return false;
}

uint16_t Chip8Processor::fetch(uint16_t instruction) {
  (void)instruction;
  return 0x0000;
}

void Chip8Processor::execute(uint16_t instruction) {
  (void)instruction;
}
