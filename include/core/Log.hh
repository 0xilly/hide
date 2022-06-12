#pragma once

#include <fmt/core.h>
#include <fmt/color.h>
#include <cstdlib>

#define INFO(msg) fmt::print("[INFO] {}\n", fmt::format(fg(fmt::color::green), msg));
#define WARN(msg) fmt::print("[WARN] {}\n", fmt::format(fg(fmt::color::yellow), msg));
#define PANIC(msg) fmt::print("[PANIC] {}\n", fmt::format(fg(fmt::color::red), msg)); std::exit(-1);

//#define Asset(expr, msg)
