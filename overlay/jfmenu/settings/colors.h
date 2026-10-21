#pragma once
#include "../headers/includes.h"
#include "../headers/flags.h"
#include <memory>

class c_colors
{
public:
    c_col layout = { 30, 32, 36 };
    c_col white = { 240, 243, 248 };
    c_col black = { 15, 16, 18 };
    c_col child = { 38, 41, 47 };
    c_col text = { 160, 166, 178 };
    c_col widget = { 50, 54, 62 };
    c_col accent = { 190, 196, 208 };
    c_col border = { 65, 70, 80 };
    c_col tab_layout = { 55, 60, 70 };
    c_col popup_widget = { 50, 54, 62 };
    c_col popup = { 34, 37, 43 };
    c_col red = { 210, 95, 95 };
};

inline std::unique_ptr<c_colors> clr = std::make_unique<c_colors>();
