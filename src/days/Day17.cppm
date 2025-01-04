module;
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
export module Day17;
import Files;
namespace Day17 {

enum Instructions {
  adv = 0, // division between A and 2 to the power combo, write to A
  bxl = 1, // Bitwise XOR of B and Literal (0 - 3)
  bst = 2, // Combo % 8 (keeping lowerst 3 bits), store in B register
  jnz = 3, // does nothing if A is 0, else jnumps by setting the instruction
           // ptr, to the value of its literal operand. if this instruction
           // jumps, the instruction pointer is not increased by 2 after this
  bxc = 4, // Bitwise XOR of B and C, store in B, reads the Combo but ignores
  out = 5, // calculates the value of its combo modulu 8, then outputs the
           // value, separate values are separated by comma
  bdv = 6, // divides A to 2 the power of combo, writes in B
  cdv = 7  // divides A to 2 the power of combo, writes in C
};

enum Combo {
  Zero = 0,
  One = 1,
  Two = 2,
  Three = 3,
  A = 4,
  B = 5,
  C = 6,
  NONE = 7
};

struct Computer {
  uint64_t A = 0;
  uint64_t B = 0;
  uint64_t C = 0;

  std::vector<int> instructions;
  std::vector<int> combo;
  int instructionPtr = 0;
  std::string outPut;
};

auto parseLines(auto lines) {
  Computer computer;
  int numShift = 12;
  for (const auto &line : lines) {
    if (line.find("A:") != std::string::npos) {
      computer.A = std::stoll(line.substr(numShift));
    } else if (line.find("B:") != std::string::npos) {
      computer.B = std::stoll(line.substr(numShift));
    } else if (line.find("C:") != std::string::npos) {
      computer.C = std::stoll(line.substr(numShift));
    } else if (line.find("Program:") != std::string::npos) {
      for (int i = 9; i < line.size(); i = i + 4) {
        {
          computer.instructions.push_back(line[i] - '0');
          computer.combo.push_back(line[i + 2] - '0');
        }
      }
    }
  }
  return computer;
}

uint64_t ReturnCombo(const Combo combo, const Computer computer) {
  switch (combo) {
  case Zero:
    return 0ll;
  case One:
    return 1ll;
  case Two:
    return 2ll;
  case Three:
    return 3ll;
  case A:
    return computer.A;
  case B:
    return computer.B;
  case C:
    return computer.C;
  case NONE:
  default:
    return 0ll;
  }
}

bool DoOperation(const int iinstruction, const int icombo, Computer &computer) {
  auto instruction = static_cast<Instructions>(iinstruction);
  auto combo = static_cast<Combo>(icombo);
  switch (instruction) {
  case adv:
    computer.A = computer.A / std::pow(2, ReturnCombo(combo, computer));
    break;
  case bxl:

    computer.B = computer.B ^ icombo;
    break;
  case bst:
    computer.B = ReturnCombo(combo, computer) % 8;
    break;
  case jnz:
    if (computer.A != 0) {
      computer.instructionPtr = icombo / 2;
      return false;
    }
    break;
  case bxc:
    computer.B = computer.B ^ computer.C;
    break;
  case out:
    computer.outPut += std::to_string(ReturnCombo(combo, computer) % 8);
    computer.outPut += ",";
    break;
  case bdv:
    computer.B = computer.A / std::pow(2, ReturnCombo(combo, computer));
    break;
  case cdv:
    computer.C = computer.A / std::pow(2, ReturnCombo(combo, computer));
    break;
  }
  return true;
}

std::string ConstructOutputProgram(const Computer &computer) {
  std::string output;
  for (int i = 0; i < computer.instructions.size(); i++) {
    output += std::to_string(computer.instructions[i]);
    output += ",";
    output += std::to_string(computer.combo[i]);
    output += ",";
  }
  return output;
}

void run(Computer &computer) {
  while (computer.instructionPtr < computer.instructions.size()) {
    auto doJump =
        DoOperation(computer.instructions[computer.instructionPtr],
                    computer.combo[computer.instructionPtr], computer);
    if (doJump)
      computer.instructionPtr++;
  }
}

export void solve(std::filesystem::path input_path) {
  auto lines = Files::readFile(input_path);
  auto computer = parseLines(lines);

  Computer PC = computer;
  run(PC);
  std::cout << "Part 1 : " << PC.outPut << std::endl;

  // part 2
  Computer PC2 = {117440, 0, 0, {0, 5, 3}, {3, 4, 0}};
  run(PC2);
  std::cout << "Part 2 (test): " << PC2.outPut << std::endl;
}
} // namespace Day17