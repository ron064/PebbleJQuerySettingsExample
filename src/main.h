/*
 * Example app demonstrating the different settings with Pebble, JQuery and Javascript
 *
 * (c) 2014 Ted Gerold (tgwaste)
 *
 * This code may be used or modified in any way without permission.
*/

#pragma once
#include <pebble.h>


// standard defines
//
#define WIDTH 144
#define HEIGHT 168
#define SAVEKEY_SETTINGS 1


// javascript keys
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

