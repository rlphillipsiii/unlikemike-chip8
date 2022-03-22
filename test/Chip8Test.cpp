#include <Processor.h>

#include <gtest/gtest.h>

class Chip8Test : public testing::Test {
public:

protected:
  Chip8Processor m_processor;

  void SetUp() override {
    m_processor.reset();
  }

  void TearDown() override {

  }

  void resetTest();
private:
};

void Chip8Test::resetTest() {
  EXPECT_EQ(0x200, m_processor.m_pc);
}

TEST_F(Chip8Test, TestReset) {
  resetTest();
}
