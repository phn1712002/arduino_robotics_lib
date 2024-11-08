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

## Tác giả, lời cảm ơn
    * Người tổng hợp, hiệu chỉnh: 
    
    Phạm Hoàng Nam 
    phn1712002@gmail.com

    * Đây là thư viện được tổng hợp lại trong quá trình nghiên cứu phát triển Robot của bản thân tôi nhằm mục đích tận dụng lưu trữ lại cho các lần sau.

    * Nội dung của mã nguồn này được lấy từ nhiều tác giả và đôi chút có sửa đổi để phù hợp với tôi.

    * Cảm ơn tất cả các tác giả đã viết mã nguồn giúp tôi nghiên cứ phát triển Robot trong thời gian qua.
