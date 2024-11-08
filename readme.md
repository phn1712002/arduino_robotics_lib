# Thư viện Robot của Arduino
    * Thư viện được viết để sử dụng với PlatformIO
    * Hãy tạo thư mục đã "pio init" và truy cập vào "src" để cài đặt.

## Cách sử dụng
```c++
    #include <Arduino.h>
    #include <Pid..hpp>
    // #include <[name_file].hpp>
```

## Cài đặt trên windowns (CMD)

```bash
git clone https://github.com/phn1712002/arduino_robotics_lib.git
for %I in (arduino_robotics_lib\*.*) do (
    if /I not "%~xI"==".md" move /Y "%I" .
)
rmdir /s /q arduino_robotics_lib
exit
```

## Cài đặt trên linux (BASH)

```bash
git clone https://github.com/phn1712002/arduino_robotics_lib.git
shopt -s extglob
mv arduino_robotics_lib/!(**.md) .
rm -r arduino_robotics_lib
```
