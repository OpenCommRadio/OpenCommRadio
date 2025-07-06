# OpenCommRadio

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
├── core/              # OpenCommRadio FSM, protocol, UI
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
git submodule update --init --recursive
make PLATFORM=uv-k5
```

This produces:

* `build/libhal.a`
* `build/libopencommsradio.a`
* `build/platform-radio-uv-k5.a`

The per-platform makefile rules will then link these into a final firmware image

---
## Testing with the emulator

Currently a simple emulator is provided in the linux/ platform, it builds a CLI-based emulator that will allow
virtual inputs as commands and optionally supports GNU radio for connecting up HackRF

---

##  Adding New Platforms

1. Create a new git repository and add it as a submodule under platforms/ with the following structure:

   ```
   platforms/<your_platform>/
   ├── include/
   ├── src/
   └── rules.mk
   ```
2. Implement the required HAL functions in `src/hal_platform_<your_platform>.c`
3. Add `rules.mk` - you can use the UV-K5 and linux platforms as examples

Pull requests to add platforms MUST use submodules to be accepted. The only exception is "native" platforms, such as
the current linux platform - if anyone wants to contribute support for Windows or MacOS please do so.

---

##  License

Licensed under **GPL-2.0-or-later**
See [LICENSE](./LICENSE) for details.

---

##  Author

Gwen Nelson – (https://github.com/GwenNelson)

