/*
 * Example app demonstrating the different settings with Pebble, JQuery and Javascript
 *
 * (c) 2014 Ted Gerold (tgwaste)
 *
 * This code may be used or modified in any way without permission.
*/


// app message sent successfully
//
function appMessageAck(e) {
	console.log("App message sent successfully");
}


// app message failed to send
//
function appMessageNack(e) {
	console.log("App message failed to send: " + e.error.message);
}


// app ready event
//
Pebble.addEventListener("ready",
	function(e) {
		console.log("connect! [" + e.ready + "] (" + e.type + ")");
	}
);


// display configuration screen
//
Pebble.addEventListener("showConfiguration",
	function() {
		var settings = encodeURIComponent(localStorage.getItem("settings"));
		var url = 'http://dl.dropbox.com/u/61083309/pebble/jqexample.html?settings=' + settings;
		console.log("Opening Config: " + url);
		Pebble.openURL(url);
	}
);


// close configuration screen
//
Pebble.addEventListener("webviewclosed",
	function(e) {
		var settings;
		try {
			settings = JSON.parse(decodeURIComponent(e.response));
			localStorage.clear();
			localStorage.setItem("settings", JSON.stringify(settings));
			console.log("Settings: " + localStorage.getItem("settings"));
			Pebble.sendAppMessage(settings, appMessageAck, appMessageNack);
		} catch(err) {
			settings = false;
			console.log("No JSON response or received Cancel event");
		}
	}
);

