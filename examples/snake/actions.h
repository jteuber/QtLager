#ifndef ACTIONS_H
#define ACTIONS_H

#include <variant>

/// *** Reserved Actions ***
/// these actions are reserved by the QtLager core. You can dispatch them from
/// your views to trigger the described effect but they are not passed through
/// to your reducers

struct reload_views
{};
struct reload_reducers
{};
using reserved_actions = std::variant<reload_views, reload_reducers>;

/// *** Custom Actions ***
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

using actions = std::
    variant<reserved_actions, go_left, go_right, go_up, go_down, reset, tick>;

#endif // ACTIONS_H
