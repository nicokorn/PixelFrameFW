@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM
@REM Read about available command line parameters in the C-SPY Debugging
@REM Guide. Hints about additional command line parameters that may be
@REM useful in specific cases:
@REM   --download_only   Downloads a code image without starting a debug
@REM                     session afterwards.
@REM   --silent          Omits the sign-on message.
@REM   --timeout         Limits the maximum allowed execution time.
@REM 


@echo off 

if not "%~1" == "" goto debugFile 

@echo on 

"C:\Program Files\IAR Systems\Embedded Workbench 9.0\common\bin\cspybat" -f "D:\GitHub\NRF52840_WS2812B_BLE\nRF5_SDK_17.0.2_d674dde\examples\ble_peripheral\ble_app_template\pca10056\s140\iar\settings\ble_app_template_pca10056_s140.nrf52840_xxaa.general.xcl" --backend -f "D:\GitHub\NRF52840_WS2812B_BLE\nRF5_SDK_17.0.2_d674dde\examples\ble_peripheral\ble_app_template\pca10056\s140\iar\settings\ble_app_template_pca10056_s140.nrf52840_xxaa.driver.xcl" 

@echo off 
goto end 

:debugFile 

@echo on 

"C:\Program Files\IAR Systems\Embedded Workbench 9.0\common\bin\cspybat" -f "D:\GitHub\NRF52840_WS2812B_BLE\nRF5_SDK_17.0.2_d674dde\examples\ble_peripheral\ble_app_template\pca10056\s140\iar\settings\ble_app_template_pca10056_s140.nrf52840_xxaa.general.xcl" "--debug_file=%~1" --backend -f "D:\GitHub\NRF52840_WS2812B_BLE\nRF5_SDK_17.0.2_d674dde\examples\ble_peripheral\ble_app_template\pca10056\s140\iar\settings\ble_app_template_pca10056_s140.nrf52840_xxaa.driver.xcl" 

@echo off 
:end