#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <fstream>

using calibration_string = std::string;
using calibration_value = std::uint32_t;

constexpr std::optional<calibration_value>
get_calibration_value(
    const calibration_string &str) noexcept {
  std::optional<std::uint32_t> a;
  std::optional<std::uint32_t> b;

  std::string value;
  const auto is_digit = [](char c) {
    return c >= '0' && c <= '9';
  };

  for (auto begin = str.begin(); begin != str.end();
       ++begin) {
    if (is_digit(*begin)) {
      a = *begin - '0';
      break;
    }
  }

  for (auto rbegin = str.rbegin(); rbegin != str.rend();
       rbegin++) {
    if (is_digit(*rbegin)) {
      b = *rbegin - '0';
      break;
    }
  }

  if (!a.has_value() || !b.has_value())
    return std::nullopt;

  return a.value() * 10 + b.value();
}

// clang-format off
static_assert(
  get_calibration_value(calibration_string("1abc2")) == 12 &&
  get_calibration_value(calibration_string("pqr3stu8vwx")) == 38 &&
  get_calibration_value(calibration_string("a1b2c3d4e5f")) == 15 &&
  get_calibration_value(calibration_string("treb7uchet")) == 77
);
// clang-format on

int main(int argc, char **args) {
  if (argc < 2) {
    std::cout << "Expected path to file\n";
    std::cout << "run as: cmd <path_to_file>\n";
    return 1;
  }

  auto file = std::ifstream(args[1]);
  if (!file) {
    std::cout << "Failed to read file\n";
    return 1;
  }

  calibration_string line;
  calibration_value sum = 0;
  while (std::getline(file, line)) {
    const auto calibration = get_calibration_value(line);
    if (!calibration.has_value()) {
      std::cout << "Failed to parse calibration value: " << line << '\n';
      return 1;
    }

    sum += calibration.value();
  }
  
  std::cout << "Calibrated sum: " << sum << '\n';
}