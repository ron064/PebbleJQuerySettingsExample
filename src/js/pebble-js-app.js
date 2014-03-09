//
// javascript
//


// callback for the app ready event
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
		var config = "https://dl.dropboxusercontent.com/u/61083309/pebble/jqexample.html";
		var settings = encodeURIComponent(localStorage.getItem("settings"));
		var url = config + "?settings=" + settings;
		console.log("Showing configuration screen...");
		console.log(url);
		Pebble.openURL(url);
	}
);


// close configuration screen
//
Pebble.addEventListener("webviewclosed",
	function(e) {
		var options;
		try {
			options = JSON.parse(decodeURIComponent(e.response));
			localStorage.clear();
			localStorage.setItem("settings", JSON.stringify(options));
			console.log("Settings: " + localStorage.getItem("settings"));
			Pebble.sendAppMessage({
				"banner":options.banner,
				"weekday":options.weekday,
				"showdate":(options.showdate===true)?"1":"0",
				"footer":options.footer
			});
		} catch(err) {
			options = false;
			console.log("No JSON response or received Cancel event");
		}
	}
);

