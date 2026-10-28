# xgetscr

Simple x11 utility for determining what screen your cursor is on.

Originally made for use with [xnap](https://github.com/uint23/xnap)

## Building

Requires libX11 and libXinerama.

```bash
./build.sh
```

## Usage

```bash
xnap -s "$(xgetscr)" > screen.ppm
```
