#include "gtest/gtest.h"

extern "C" {
	#include "../src/cub.h"
	#include "../libft/libft.h"
}

TEST(verify_sprite_color, simple) {
	char *map[5] = {"SO      ./test.sh","WE ./test.sh","NO ./test.sh", "EA ./test.sh"};
	int res[5];
	t_map *cmap;
	for(int i = 0; i < 5; i++) {
		res[i] = verify_sprite_color(map[i], cmap);
		ASSERT_EQ(res[i], 1);
	}
	ASSERT_EQ(cmap->no, "./test.sh");
	ASSERT_EQ(cmap->so, "./test.sh");
	ASSERT_EQ(cmap->ea, "./test.sh");
	ASSERT_EQ(cmap->we, "./test.sh");
}