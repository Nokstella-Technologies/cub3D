#include "gtest/gtest.h"

extern "C" {
	#include "../src/cub.h"
	#include "../libft/libft.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}