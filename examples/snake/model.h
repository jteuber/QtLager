//
// lager - library for functional interactive c++ programs
// Copyright (C) 2019 Carl Bussey
//
// This file is part of lager.
//
// lager is free software: you can redistribute it and/or modify
// it under the terms of the MIT License, as detailed in the LICENSE
// file located at the root of this source code distribution,
// or here: <https://github.com/arximboldi/lager/blob/master/LICENSE>
//

#pragma once

#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

using point_t = std::pair<int, int>;

inline int x(point_t p) { return p.first; }

inline int y(point_t p) { return p.second; }

enum class direction
{
    left,
    up,
    right,
    down
};

struct snake_model
{
    using body_t = std::vector<point_t>;
    body_t body{};
    direction dir{};
};

struct game_model
{
    snake_model snake;
    point_t apple_pos{};
    bool over;

    static constexpr int width{25};
    static constexpr int height{25};
};

template <typename Func>
inline point_t random_apple_pos(Func&& random)
{
    return {random(), random()};
}

template <typename Func>
game_model make_game(Func&& random)
{
    const point_t snake_head{game_model::width / 2, game_model::height / 2};
    snake_model::body_t body{snake_head,
                             {x(snake_head) - 1, y(snake_head)},
                             {x(snake_head) - 2, y(snake_head)}};

    return {snake_model{body, direction::right},
            random_apple_pos(std::forward<Func>(random)),
            false};
}

struct model
{
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

    game_model game;

    model()
        : dist{0, game_model::width - 1}
    {
        std::random_device rd;
        gen  = std::mt19937{unsigned(rd())};
        game = make_game([&] { return dist(gen); });
    }
};
