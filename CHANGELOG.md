## ChangeLog

### 1.0-RC1 - 2019-05-14

**Enhancements**

This release is a major update to the previous release and includes the following changes:
* Alexa:
 * All the Alexa functional and music certification tests can now be passed with this release.
 * Robustness enhancements that pass 100-hour long duration stress tests.
 * Wi-Fi and Alexa configuration on BLE (Bluetooth Low Energy) makes the provisioning experience much smoother (This mandates that you upgrade to the latest phone apps while using this release.).
   * Newer app and firmware supports WiFi scanlist as well.
 * Supports greater number of music stations because of:
   * Greater tolerance for variance in different music stations M3U8 formats.
   * Support for additional 'Content-Type' as reported by some music stations.
* Improved directory structure to add flexibility to provide way to test other ESP32 based audio boards. Examples can be build and flashed on any of the following development boards with proper "AUDIO_BOARD_PATH" provided:
 1. LyraT
 2. LyraTD-SYNA
 3. LyraTD-DSPG
 4. LyraTD-MSC

* LEDs and tones are added for GVA and Dialogflow.
* Support for setting custom tones.
* nvs-set CLI supports setting and getting int16_t variable type.

**API Changes**

* Examples directories are renamed according to voice assistants. There are now 3 examples viz., amazon_alexa, google_voice_assistant and google_dialogflow.
* BLE provisioning and authentication for Alexa instead of SoftAP provisioning.
* Local Player, Equalizer and AWS-IoT are moved inside amazon_alexa/additional_components/
* voice_assistant_app_cb.h:
  * va_app_set_volume() is now deprected. A new function va_app_volume_is_set() is now introduced. Earlier the app had to change the volume itself. Now this is directly handled in the medial-hal layer. The application layer only gets a notification once the volume changed has happened.
  * va_app_set_mute() is now deprected. A new function va_app_mute_is_set() is now introduced. Earlier the app had to mute the volume itself. Now this is directly handled in the medial-hal layer. The application layer only gets a notification once the mute change has happened.
* A new API va_boot_is_finish() is introduced that allows applications to wait until the complete boot-up has finished.
* A new API tone_set_custom() lets application override the existing tone with a custom tone that can be played.
* The audio_player_stop() API is now updated to include one additional parameter which is a notify callback.
* The alexa_config_t structure now includes two additional members 'device_serial_num' and 'product_id' which are now used for communication with the AVS service.


**Bug Fixes**

* Fixed What’s up interruption stalling the device.
* Code restructuring in the SDK to fix various race conditions occurring during long-duration testing
* Improved stability for if the Internet or Wi-Fi connectivity is intermittent.
* All well known TuneIn radio stations are now supported.

### v1.0b1r7 (Beta) - 2019-01-08

**Enhancements**

* Support for Google Voice Assistant (GVA) and Google Dialogflow (Alpha release). Please check README of each voice assistant to get started.
* Support to play custom tones from application.
* nvs-set CLI supports setting and getting int8_t variable type.

**API Changes**

* Example directories are renamed.
* Many structures, functions and header files with "alexa" prefix are renamed with "va" prefix. Please follow the `Upgrading from Previous Release` section from `README-Getting-Started.md` if you want to compile and run older examples with new SDK.

**Bug Fixes**

* Background noise in audio with lower sampling rates.
* In case of incorrect provisioning parameters, device needed to be reset via command line (via esptool.py on host or nvs-erase on device). Now reset-to-factory push button (Mode) could also be used.
* Capabilities are announced automatically when an updated firmware with new capabilities is flashed onto the device.
* More SNTP servers are added for faster time synchronization on device boot-up.

**Known Issues/Improvements**

* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0b1r6 (Beta) - 2018-12-24

**Enhancements**

* Support for local mp3 playback. Example application has also been added.
* Support for EqualizerController interface. Just facilitating APIs are added, user should register and implement callback function for actual Equalizer control.
* Support for CLI-based PlaybackController interface. Play, pause, next, previous, button and toggle commands are supported. "button" CLI can be used to emulate button press on the device. Or application can call appropriate API from playback_controller.h to notify SDK of button press (if user wants to implement hardware button).
* Support for CLI based WiFi provisioning. App is still required for Amazon authentication.

**API Changes**

* Removed support for static authentication (AVS partition based authentication).

**Bug Fixes**

* Fixed bugs related to stability and device getting stuck in infinite loop in some cases.

**Known Issues/Improvements**

* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0b1r5 (Beta) - 2018-11-12

**Enhancements**

* TLS Certificate validation of Amazon and other streaming sites.

**API Changes**

* http_connection_new now requires pointer to esp_tls_cfg_t object.
* Check application's README for a new patch on esp-idf, without which compilation will fail with this release.

**Bug Fixes**

* Device goes in infinite loop if internet goes down while responding to "What's up?"
* Other minor exception fixes

**Known Issues/Improvements**

* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0b1r4 (Beta) - 2018-09-28

**Enhancements**

* Support for PLS playlist parser
* Support for Pandora music streaming service
* TuneIn stations using PLS playlist format are now supported
* LyraTD-MSC board support

**API Changes**

* Older http_stream.c/.h is now renamed to http_playback_stream.c/.h. All APIs starting with http_stream are renamed to http_playback_stream
* http_stream.c/.h file now contains APIs which are useful to create a stream to POST data to cloud and receive response on the same connection and stream

**Bug Fixes**

* Stability related fixes
* Fixed crashes seen in Audible when segments >512 are received

**Known Issues/Improvements**

* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.
* TLS Certificate validation of Amazon and other streaming sites is yet to be done.

### v1.0b1r3 (Beta) - 2018-08-28

**Enhancements**

* Seeking support for Audible books
* Support for OffsetInMilliSeconds, ProgressReportDelayElapsed and ProgressReportIntervalElapsed
* LED patterns for various Alexa states as per Alexa UX design guidelines
* Playing Alerts/Timers, Reminders from received URL even after device reboot. Device used to play stored tunes if device rebooted in between setting the Alarm and its timeout
* Minute latency improvement where Recognize event is now being sent earlier upon WW detection

**Bug Fixes**

* No intermittent audio playback between multiple Speak directives of the same dialog (e.g "What's up")
* Few stability related fixes

**Known Issues**

* Crashes are seen in Audible when segments >512 are received
* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0b1r2 (Beta) - 2018-08-14

**Enhancements**

* Support for persistent Alerts/Timers, Reminders and Notifications

**Bug Fixes**

* Multiple race conditions fixed to improve the stability

**Known Issues**

* Regression in Audible support - crashes are seen with Audible
* Book and audio playback seeking is not yet supported
* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0b1r1 (Beta) - 2018-08-06

**Enhancements**

* Amazon music support
* Alerts/Timers, Reminders, Notifications support
* Audible support
* Capabilities API integration
* AudioActivityTracker support

**Bug Fixes**
* Overall stability improvements
* Fixed minor issues with Android App
* Amazon app is no more required on phone for authentication. App opens login page on device's browser if app isn't found.

**Known Issues**

* Alerts/Timers, Reminders and Notifications do not persist across device reboot
* Book and audio playback seeking is not yet supported
* Only limited TuneIn radio stations are supported
* It is largely tested with internet and WiFi connectivity intact throughout its operation. Some issues are seen when device loses connectivity.

### v1.0a1r1 (Alpha) - 2018-07-09

* Complete C-Based SDK from ground-up with support for
    * Basic conversation
    * Multi-turn
    * Audio playback - Saavn, TuneIn, Kindle
    * Volume control (both physical and spoken)
    * Tap-To-Talk
* Salvaged 75KB of internal memory as compared to CPP based port
* Phone app (Android) support for:
    * Network configuration
    * Alexa authentication

### v0.15

* Port of Amazon's CPP SDK (v1.3) with additional optimizations for embedded target
