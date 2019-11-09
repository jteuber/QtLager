#ifndef ACTIONS_H
#define ACTIONS_H

#include <variant>

struct go_left
{};
struct go_right
{};
struct go_up
{};
struct go_down
{};
struct reset
{};
struct tick
{};
using Actions = std::variant<go_left, go_right, go_up, go_down, reset, tick>;

#endif // ACTIONS_H
