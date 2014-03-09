//
// main.h
// (c) 2013 Ted Gerold (tgwaste)
//

#pragma once
#include <pebble.h>


// standard defines
//
#define WIDTH 144
#define HEIGHT 168
#define SAVEKEY_SETTINGS 1


// javascript defines
//
enum {
	KEY_BANNER = 0,
	KEY_WEEKDAY = 1,
	KEY_SHOWDATE = 2,
	KEY_FOOTER = 3
};


// pebble variables
//
Window *window;
Layer *window_layer;
TextLayer *bannerLayer;
TextLayer *timeLayer;
TextLayer *weekdayLayer;
TextLayer *dateLayer;
TextLayer *footerLayer;


// settings structure
//
struct {
	char banner[40];
	char footer[40];
	int weekday;
	int showdate;
} settings;

