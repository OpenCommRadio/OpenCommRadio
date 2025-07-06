# OpenCommsRadio

**OpenCommRadio** is a modular, cross-platform radio firmware framework designed for digital communications, message routing, and simple UI interaction. It supports multiple handheld radios and simulation targets via a clean hardware abstraction layer (HAL).

---

##  Features

- Pluggable HAL for different radios (Quansheng UV-K5, RT3S, etc.)
- Simple AT-style command mode over UART
- Support for AFSK/FFSK modulation
- Modular FSM, protocol, and display architecture
- Optional SDL/GNU Radio emulator
- Cross-compile friendly with clean Makefile build system

---

##  Project Structure

```

.
├── hal/               # HAL interface and shared logic
│   ├── include/       # hal.h
│   ├── src/           # hal.c (weak stubs, polling)
│   └── rules.mk
├── core/              # OpenCommsRadio FSM, protocol, UI
│   ├── include/
│   ├── src/
│   └── rules.mk
├── platforms/         # Platform-specific HAL backends
│   └── uv-k5/
│       ├── include/
│       ├── src/
│       └── rules.mk
├── build/             # Output directory (generated)
├── Makefile           # Top-level build orchestrator
└── README.md

```

---

##  Building

To build the core and platform HAL into static libraries:

```bash
make PLATFORM=uv-k5
```

This produces:

* `build/libhal.a`
* `build/libopencommsradio.a`
* `build/platform-radio-uv-k5.a`

The per-platform makefile rules will then link these into a final firmware image

---

##  Adding New Platforms

1. Create a new folder under `platforms/`:

   ```
   platforms/<your_platform>/
   ├── include/
   ├── src/
   └── rules.mk
   ```
2. Implement the required HAL functions in `hal_platform_<your_platform>.c`
3. Add `rules.mk` - you can use the UV-K5 as an example

---

##  License

Licensed under **GPL-2.0-or-later**
See [LICENSE](./LICENSE) for details.

---

##  Author

Gwen Nelson – (https://github.com/GwenNelson)

