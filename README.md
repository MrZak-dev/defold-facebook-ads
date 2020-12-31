# Defold Facebook Ads (Audience Network) extension (Android)

![demo](example.png)

## Installation
To use this library in your Defold project, add the following URL to your `game.project` dependencies:

https://github.com/MrZak-dev/defold-facebook-ads/archive/master.zip


## API reference

```lua

FacebookAds.initialize() --Initialize the extension

FacebookAds.load_interstitial(placememnt_id) -- load Interstitial Ad,  string : placememnt_id
FacebookAds.load_rewarded_video(placememnt_id) -- load Rewarded Video Ad,  string : placememnt_id
FacebookAds.load_banner(placememnt_id) -- load Banner Ad,  string : placememnt_id

FacebookAds.show_interstitial() -- Display loaded Interstitial Ad
FacebookAds.show_rewarded_video() -- Display loaded Rewarded Video Ad

FacebookAds.show_banner() -- Display loaded Banner Ad
FacebookAds.hide_banner() -- Hide loaded Banner Ad

FacebookAds.is_interstitial_loaded() -- Returns boolean , indicates if interstitial ad is loaded , returns True if Interstitial ad is LOADED and READY
FacebookAds.is_rewarded_loaded() -- Returns boolean , indicates if Rewarded video ad is loaded
FacebookAds.is_banner_loaded() -- Returns boolean , indicates if Banner ad is loaded

FacebookAds.is_interstitial_dismissed() -- Returns true if The Interstitial is dismissed by the user , This will be set to false after each show_interstitial() call
FacebookAds.is_rewarded_dismissed() -- Returns true if The Rewarded Video is dismissed (NOT COMPLETED) by the user , This will be set to false after each show_rewarded_video() call
FacebookAds.is_rewarded_completed() -- Returns true if The Rewarded Video is dismissed (COMPLETED/REWARD) by the user , This will be set to false after each show_rewarded_video() call

```

## Example

```lua
function init(self)

	if FacebookAds ~= nil then
		FacebookAds.initialize()
		FacebookAds.load_interstitial("your_placement_id")
        FacebookAds.load_rewarded_video("your_placement_id")
        FacebookAds.load_banner("your_placement_id")
    end
end

function on_message(self, message_id, message)
	
	if message_id == hash("show_interstitial") then
		if FacebookAds ~= nil then
			FacebookAds.show_interstitial()
		end
	end

	if message_id == hash("show_rewarded") then
		if FacebookAds ~= nil then
			FacebookAds.show_rewarded_video()
		end
    end
end

```

## Debugging

In order to make it easier to debug this extension, use `adb logcat` command-line tool, The extension messages are under `defold` Tag.


```bash
    adb logcat -v color defold *:S
```
