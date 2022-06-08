#include Processor.h

void Chip8Processor::instruction_set(){

	opcode = m_memory[m_pc] << 8 | m_memory[m_pc + 1];
	uint8_t *Vx = &m_v[(opcode & 0x0F00) >> 8];
	uint8_t *Vy = &m_v[(opcode & 0x00F0) >> 4];
	uint8_t *Vf = &m_v[0xF]
	uint8_t byte = (opcode & 0x00FF);
	char key_press;

	switch(opcode & 0xF000){
		case 0x0000:
			switch(opcode & 0x00FF) {
				// opcode: 00E0
				// CLS - clear display
				case 0x00E0:	

				// opcode: 00EE
				// RET - return from subroutine
				// Interpreter sets program counter to address at top of stack,
				// then subtracts 1 from stack pointer
				case 0x00EE:	
					m_pc = m_stack[m_sp];
					--m_sp;
					break;
			}
			break;

		// opcode: 1nnn
		// JP addr - jump to location
		// Interpreter sets prgoram counter to nnn
		case 0x1000:	
			m_pc = opcode & 0x0FFF;
			break;

		// opcode: 2nnn
		// CALL addr - call subroutine at nnn
		// Interpreter increments stack pointer, then puts current PC on top of stack
		// PC then set to nnn
		case 0x2000:	
			++m_sp;
			m_stack[m_sp] = m_pc;
			m_pc = opcode & 0x0FFF;
			break;

		// opcode: 3xkk
		// SE Vx, byte - Skip next instruction if Vx = kk
		// Interpreter compares register Vx to kk, if equal: increments PC by 2
		case 0x3000:	
			if Vx == byte
				pc += 2
			break;

		// opcode: 4xkk
		// SNE Vx, byte - Skip next instruction if Vx !=kk
		// Interpreter compares register Vx to kk, if not equal: increments PC by 2
		case 0x4000:	
			if Vx != byte
				pc += 2
			break;

		// opcdoe: 5xy0
		// SE Vx, Vy - Skip next instruciton if Vx = Vy
		// Interpreter compares register Vx to Vy, if equal: increments PC by 2
		case 0x5000:	
			if Vx == Vy
				pc += 2
			break;

		// opcdoe: 6xkk
		// LD Vx, byte - Set Vx = kk
		case 0x6000:	
			m_v[(opcode & 0x0F00) >> 8] = byte;
			break;

		// opcdoe: 7xkk
		// ADD Vx, byte - Set Vx = Vx + kk
		case 0x7000:	
			m_v[(opcode & 0x0F00) >> 8] += byte;
			break;

		case 0x8000:
			switch(opcode & 0x000F){
				// opcode: 8xy0
				// LD Vx, Vy - Set Vx = Vy
				case 0x0000:	
					m_v[(opcode & 0x0F00) >> 8] = Vy;
					break;

				// opcode: 8xy1
				// OR Vx, Vy - Set Vx = Vx OR Vy
				case 0x0001:	
					m_v[(opcode & 0x0F00) >> 8] |= Vy;
					break;

				// opcode: 8xy2
				// AND Vx, Vy - Set Vx = Vx AND Vy
				case 0x0002:	
					m_v[(opcode & 0x0F00) >> 8] &= Vy;
					break;

				// opcode: 8xy3
				// XOR Vx, Vy - Set Vx = Vx XOR Vy
				case 0x0003:	
					m_v[(opcode & 0x0F00) >> 8] ^= Vy;
					break;

				// opcode: 8xy4
				// ADD Vx, Vy - Set Vx = Vx + Vy, VF = carry
				case 0x0004:	
					m_v[(opcode & 0x0F00) >> 8] += Vy

					if(Vx > 255)
						m_v[0xF] = 1;
					else
						m_v[0xF] = 0;

					m_v[(opcode & 0x0F00) >> 8] &= 0xFF;
					break;

				// opcode: 8xy5
				// SUB Vx, Vy - Set Vx = Vx - Vy, VF = NOT borrow
				// If Vx > Vy then VF set to 1, otherwise 0
				case 0x0005:	
					if(Vx > Vy)
						m_v[0xF] = 1;
					else
						m_v[0xF] = 0;

					m_v[(opcode & 0x0F00) >> 8] -= Vy;
					break;

				// opcode: 8xy6
				// SHR Vx, Vy - Set Vx = Vx SHR 1
				// If least-significant bit of Vx is 1, then VF is 1, otherwise 0.
				//Then Vx is divided by 2
				case 0x0006:	
					m_v[0xF] = Vx & 0x1;
					m_v[(opcode & 0x0F00) >> 8] >>= 1;
					break;

				// opcode: 8xy7
				// SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow
				// If Vy > Vx then VF set to 1, otherwise 0)
				case 0x0007:	
					if(Vy > Vx)
						m_v[0xF] = 1;
					else
						m_v[0xF] = 0;

					m_v[(opcode & 0x00F0) >> 4] -= Vx;
					break;

				// opcode: 8xyE
				// SHL Vx {, Vy} - Set Vx = Vx SHL 1
				// If most-significant bit of Vx is 1, then VF set to 1, otherwise 0.
				// Vx is multiplied by 2
				case 0x000E:	
					m_v[0xF] = (Vx >> 7) & 0x1;
					m_v[(opcode & 0x0F00) >> 8] <<= 1;
			}

		// opcode: 9xy0
		// SNE Vx, Vy - Skip next instruction if Vx != Vy
		// If not equal, PC increased by 2
		case 0x9000:	
			if Vx != Vy
				pc += 2;
			break;

		// opcode: Annn
		// LD I, addr - Set I = nnn
		// Value of register I is set to nnn
		case 0xA000:	
			m_iRegister = opcode & 0x0FFF;
			break;

		// opcode: Bnnn
		// JP V0, addr - jump to location nnn + v0
		case 0xB000:	
			m_pc = m_v[0] + (opcode & 0x0FFF);
			break;

		// opcode: Cxkk
		// RND Vx, byte - Set Vx = random byte AND kk
		// Interpreter generates random number from 0 to 255 which is ANDed with kk.
		// Results stored in Vx
		case 0xC000:	
			m_v[(opcode & 0x0F00) >> 8] =  & byte

		// opcode: Dxyn
		// DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location I at (Vx, Vy)
		// Set VF = collision
		case 0xD000:	 
			uint8_t height = opcode & 0x000F;
			uint8_t pixel;

			for(int row = 0; row < height; row++){
				pixel = memory[m_iRegister + row];
				for(int col = 0; col < 8; col++){
					uint8_t nextPixel = pixel & (0x80 >> col);

					// Check for Pixel
					if(nextPixel){
						uint32_t* currentPixel = &screen[Vx + col + ((Vy + row) * 64)];

						// Check for pixel on screen
						if(currentPixel == 1)
						{
							m_v[0xF] = 1;
						}

						*currentPixel ^= 1;
					}
				}
			}
			break;

		case 0xE000:
			switch(opcode & 0x00FF){
				// opcode: Ex9E
				// SKIP Vx - Skip next instruction if key with the value of Vx is down
				// If key corresponding to Vx down, PC increased by 2
				case 0x009E:	
					cin >> key_press; //Don't yet know what key_press is
					if(key_press == Vx)
						m_pc += 2;
					break;

				// opcode: ExA1
				// SKNP Vx - Skip next instruction if key with the value of Vx is up
				// If key corresponding to Vx up, PC increased by 2
				case 0x00A1:	
					cin >> key_press; //Don't yet know what key_press is
					if(key_press != Vx)
						m_pc += 2;
					break;
			}
			break;

			case 0xF000:
				switch(opcode & 0x00FF){
					// opcode: Fx07
					//LD Vx, DT - Set Vx = delay timer value
					case 0x0007:	
						m_v[(opcode & 0x0F00) >> 8] = m_delay;
						break;

					// opcode: Fx0A
					// LD Vx, K - Wait for a key press, store the value of the key in Vx
					// All execution stops until a key is pressed, then value of key stored in Vx
					case 0x000A:	
						//stop all execution until key is pressed
						cin >> key_press;
						m_v[(opcode & 0x0F00) >> 8] = key_press;
						break;

					// opcode: Fx15
					//LD DT, Vx - Set delay timer = Vx
					case 0x0015:	
						m_delay = Vx;
						break;

					// opcode: Fx18
					//LD ST, Vx - Set sound timer = Vx
					case 0x0018:	
						m_timer = Vx;
						break;

					// opcode: Fx1E
					//ADD I, Vx - Set I = I + Vx
					case 0x001E:	
						m_iRegister += Vx;
						break;

					// opcode: Fx29
					// LD F, Vx - Set I = location of sprite for digit Vx
					case 0x0029:	
						m_iRegister = 

					// opcode: Fx33
					// LD B, Vx - store BCD representation of Vx in memory locations I, I+1 and I+2
					// Interpreter takes Vx and places
					// thundreds digit in memory at location in I
					// tens in I+1,
					// and ones in I+2
					case 0x0033:	
						m_memory[m_iRegister] = Vx / 100;
						m_memory[m_iRegister + 1] = (Vx/10) % 10;
						m_memory[m_iRegister + 2] = Vx % 10;
						break; 

					// opcode: Fx55
					//LD[I], Vx - store registers V0 - Vx in memory starting at I
					case 0x0055:	
						for(int i = 0; i <= Vx; i++)
							m_memory[m_iRegister + i] = m_v[i];
						break;

					// opcode: Fx65
					//LD Vx, [I] - read registers V0 - Vx from memory starting at location I
					case 0x0065:	
						for(int i = 0; i <= Vx; i++)
							m_v[i] = m_memory[m_iRegister + i];
						break;

				}
				break;
	}
}