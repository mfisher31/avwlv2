#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

#include "lv2plugin/lv2plugin.hpp"

#include "test.hpp"

Test::Test(double rate) :
		Plugin<Test>(p_n_ports)
{
	 std::cout << "Constructor" << std::endl;
}

void Test::run(uint32_t nframes)
{
	unsigned int l2;

	for (l2 = 0; l2 < nframes; ++l2)
	{
		p(p_out)[l2] = 0;
	}
}

void Test::deactivate()
{
	 std::cout << "Destructor" << std::endl;
}

static int _ = Test::register_class("http://avwlv2.sourceforge.net/plugins/avw/test");

