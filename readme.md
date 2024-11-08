## Installation in windowns (CMD)

```bash
git clone https://github.com/phn1712002/arduino_robotics_lib.git
for %I in (arduino_robotics_lib\*.*) do (
    if /I not "%~xI"==".md" move /Y "%I" .
)
rmdir /s /q arduino_robotics_lib
exit
```

## Installation in linux (BASH)

```bash
git clone https://github.com/phn1712002/arduino_robotics_lib.git
shopt -s extglob
mv arduino_robotics_lib/!(**.md) .
rm -r arduino_robotics_lib
```
