# CHRONOS – 2KB Real-Time Kernel for Cortex-M

> **No heap. No bloat. 8 tasks. Total control.**

**CHRONOS** is a **minimalist, deterministic, static RTOS** designed for **bare-metal Cortex-M** systems — perfect for **STM32, RP2040, nRF52**, and any MCU with **less than 64KB Flash**.

Born from many years of embedded systems frustration with bloated kernels, **CHRONOS** gives you **full control** over RAM, timing, and code size — **without sacrificing usability**.

---

## Features

| Feature | Details |
|-------|--------|
| **2KB Flash, less than 2KB RAM** | Fits in the smallest STM32F0 |
| **8 static tasks** | Configurable at compile-time |
| **Zero-copy queues** | Lock-free, ISR-safe |
| **1ms tick, deterministic** | No dynamic allocation |
| **Dual-platform** | Runs on **PC (Windows/Linux)** and **MCU** |
| **Console-ready** | `printf()` on host + UART |
| **STM32CubeMX compatible** | Drop-in `chronos/` folder |
| **Zero heap, zero surprises** | No `malloc`, no fragmentation |

---

## Why CHRONOS?

| FreeRTOS | **CHRONOS** |
|---------|------------|
| 25–40KB Flash | **1.4KB Flash** |
| Dynamic tasks | **Static, predictable** |
| Heap allocation | **No heap** |
| Complex config | **One header** |

> **"If you can blink an LED, you can run CHRONOS."**

---

## Quick Start (STM32CubeMX)

1. Generate your project with **STM32CubeMX**
2. Copy the `chronos/` folder into your project root
3. Add to `main.c`:

```c
#include "chronos/chronos.h"