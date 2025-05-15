#pragma once

#include<cstdint>

namespace ColorsConsts
{
	struct Color {
		std::uint8_t r, g, b, a;

		constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
			: r(red), g(green), b(blue), a(alpha) {}

		Color() {};
	};

	static constexpr Color gray {0x33, 0x33, 0x33, 0x99};
	static constexpr Color green {0x00, 0xFF, 0x00, 0x55};
	static constexpr Color black {0x00, 0x00, 0x00, 0x00};
	static constexpr Color white {0xFF, 0xFF, 0xFF, 0xFF};
	static constexpr Color red {0xFF, 0x00, 0x00, 0x55};

}