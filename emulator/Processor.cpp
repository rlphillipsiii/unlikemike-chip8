#include "Processor.h"

Chip8Processor::Chip8Processor() {

}

void Chip8Processor::reset() {

}

bool Chip8Processor::load(const std::string& rom) {
  (void)rom;
  return false;
}

void Chip8Processor::execute(uint16_t instruction) {
  (void)instruction;
}
