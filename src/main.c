//
// main.c
// (c) 2014 Ted Gerold (tgwaste)
//

#include "main.h"


// incoming javascript messages
//
void jsmsg(DictionaryIterator *iter, void *context)
{
	Tuple *banner = dict_find(iter, KEY_BANNER);
	Tuple *weekday = dict_find(iter, KEY_WEEKDAY);
	Tuple *showdate = dict_find(iter, KEY_SHOWDATE);
	Tuple *footer = dict_find(iter, KEY_FOOTER);

	if (banner)
		snprintf(settings.banner, sizeof(settings.banner), "%.40s", banner->value->cstring);

	if (weekday)
		settings.weekday = weekday->value->cstring[0] == 'y' ? 1 : 0;

	if (showdate)
		settings.showdate = showdate->value->int16;

	if (footer)
		snprintf(settings.footer, sizeof(settings.footer), "%.40s", footer->value->cstring);

	persist_write_data(SAVEKEY_SETTINGS, &settings, sizeof(settings));

	banner = NULL;
	weekday = NULL;
	showdate = NULL;
	footer = NULL;

	layer_mark_dirty(window_layer);
}


// set our layer attributes
//
void set_layer_attr(TextLayer *textlayer, GFont font)
{
	text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
	text_layer_set_text_color(textlayer, GColorWhite);
	text_layer_set_background_color(textlayer, GColorBlack);
	text_layer_set_font(textlayer, fonts_get_system_font(font));
	layer_add_child(window_layer, text_layer_get_layer(textlayer));
}


// handle every minute
//
void handle_minute(struct tm *tm, TimeUnits units_changed)
{
	layer_mark_dirty(window_layer);
}


// display handler
//
void display_handler(Layer *me, GContext *context)
{
	static char time_text[] = "00:00";
	static char wday_text[] = "         ";
	static char date_text[] = "         ";
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);

	strftime(time_text, sizeof(time_text), clock_is_24h_style() ? "%H:%M" : "%l:%M", tm);
	strftime(wday_text, sizeof(wday_text), settings.weekday ? "%A" : "", tm);
	strftime(date_text, sizeof(date_text), settings.showdate ? "%B %d" : "", tm);

	text_layer_set_text(bannerLayer, settings.banner);
	text_layer_set_text(timeLayer, time_text);
	text_layer_set_text(weekdayLayer, wday_text);
	text_layer_set_text(dateLayer, date_text);
	text_layer_set_text(footerLayer, settings.footer);
}


// initialize window
//
void init(void)
{
	window = window_create();
	window_set_fullscreen(window, true);
	window_stack_push(window, true);
	window_set_background_color(window, GColorBlack);

	window_layer = layer_create(layer_get_frame(window_get_root_layer(window)));
	layer_add_child(window_get_root_layer(window), window_layer);
	layer_set_update_proc(window_layer, display_handler);

	bannerLayer = text_layer_create(GRect(0,0,WIDTH,22));
	set_layer_attr(bannerLayer, FONT_KEY_GOTHIC_18_BOLD);

	timeLayer = text_layer_create(GRect(0,22,WIDTH,55));
	set_layer_attr(timeLayer, FONT_KEY_ROBOTO_BOLD_SUBSET_49);

	weekdayLayer = text_layer_create(GRect(0,77,WIDTH,28));
	set_layer_attr(weekdayLayer, FONT_KEY_GOTHIC_24_BOLD);

	dateLayer = text_layer_create(GRect(0,105,WIDTH,28));
	set_layer_attr(dateLayer, FONT_KEY_GOTHIC_24_BOLD);

	footerLayer = text_layer_create(GRect(0,133,WIDTH,28));
	set_layer_attr(footerLayer, FONT_KEY_GOTHIC_24_BOLD);

	tick_timer_service_subscribe(MINUTE_UNIT, &handle_minute);
	persist_read_data(SAVEKEY_SETTINGS, &settings, sizeof(settings));

	APP_LOG(APP_LOG_LEVEL_DEBUG, "- Pebble JQuery Settings Example -");
	APP_LOG(APP_LOG_LEVEL_DEBUG, "(c) 2014 Ted Gerold (tgwaste)");
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Window ready [%p]", window);

	app_message_register_inbox_received(jsmsg);
	app_message_open(256,50); // in/out
}


// deinit the application
//
void deinit(void)
{
	tick_timer_service_unsubscribe();

	text_layer_destroy(bannerLayer);
	text_layer_destroy(timeLayer);
	text_layer_destroy(weekdayLayer);
	text_layer_destroy(dateLayer);
	text_layer_destroy(footerLayer);

	layer_destroy(window_layer);
	window_destroy(window);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "App shutting down... Goodbye.");
}


// good ol main
//
int main(void)
{
	init();
	app_event_loop();
	deinit();
}

