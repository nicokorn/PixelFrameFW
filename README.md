# PixelFrame firmware
Firmware code for a pixel frame. The firmware runs on a Nordic nRF52840 and uses the pwm peripheral to control ws2812b leds. The fds module is used to store and load peristent data from the internal flash. To control the pixel frame I also developed an Android App which is held in a seperate repo: https://github.com/nicokorn/PixelFrameApp . The housing I have drawn in Autocad in several pieces and then 3D printed with pla filament. The source code is a bit hidden on the inside of the SDK, find it on: https://github.com/nicokorn/PixelFrameFW/tree/main/nRF5_SDK_17.0.2_d674dde/examples/ble_peripheral/ble_app_ws2812b . If you want to know how the ws2812b rgb leds are driven, visit my ws2812b repo front page: https://github.com/nicokorn/NRF52840_WS2812B .

<html>
<body>

<h2>Pictures/vids of the pixel frame</h2>
Short demo on youtube: https://www.youtube.com/watch?v=DLWldU1EluU
<img src="https://github.com/nicokorn/NRF52840_WS2812B_BLE/blob/main/docs/20210811_175008.jpg" alt="px1">
<img src="https://github.com/nicokorn/NRF52840_WS2812B_BLE/blob/main/docs/20210811_175349.jpg" alt="px2">
<img src="https://github.com/nicokorn/NRF52840_WS2812B_BLE/blob/main/docs/Screenshot_20210811-180451.jpg" alt="px3">
<img src="https://github.com/nicokorn/NRF52840_WS2812B_BLE/blob/main/docs/Screenshot_20210811-175719.jpg" alt="px4">
</body>
</html>
