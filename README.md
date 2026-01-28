# 📂 STM32 SD Card Read/Write Using SDIO (STM32CubeIDE)

This guide explains **how to configure, build, and run an STM32 project that reads and writes data to an SD card using SDIO and FATFS**.
It follows ControllersTech-style workflow and works for **STM32F4 + FreeRTOS or bare-metal**.

---

## ⚙️ 1. Hardware Requirements

- 🖥️ STM32F4 MCU (STM32F407 / STM32F429 recommended)
- 💾 SD card (≤ 32 GB, FAT32)
- 🔌 SD card socket (onboard or external)
- ⚡ 3.3V power supply
- 🔧 Pull-up resistors (10kΩ) on CMD and D0–D3 (if not onboard)

### 🗺️ Typical SDIO Pin Mapping

| SD Card | STM32 |
|---------|-------|
| CLK     | PC12  |
| CMD     | PD2   |
| D0      | PC8   |
| D1      | PC9   |
| D2      | PC10  |
| D3      | PC11  |

---

## 💻 2. Software Requirements

- 🛠️ STM32CubeIDE (latest)
- 📚 STM32 HAL drivers
- 🗄️ FATFS middleware
- 🧩 (Optional) FreeRTOS (CMSIS-RTOS v2)

---

## 💾 3. SD Card Preparation

1. Insert SD card into PC
2. Format using **SD Card Formatter**
3. File system: **FAT32**
4. Allocation unit size: Default

⚠️ **exFAT and NTFS will NOT work**

---

## 🔧 4. STM32CubeIDE Configuration

### 🔹 Enable SDIO
- Mode: SD 1-bit (start here)
- Clock Divider: 8 (safe)
- Disable hardware flow control

### 🔹 Enable DMA
- SDIO_RX → DMA2 Stream3
- SDIO_TX → DMA2 Stream6
- Priority: Very High

### 🔹 Enable FATFS
- Interface: SD Card
- Long file names: Optional

### 🔹 NVIC
- Enable SDIO global interrupt

### 🔹 FreeRTOS (Optional)
- SD task stack ≥ 4096 bytes
- FATFS reentrancy enabled (`FF_FS_REENTRANT 1`)

---

## 🚀 5. Build & Flash

1. Generate code from `.ioc`
2. Build project
3. Flash firmware
4. Insert SD card before reset

---

## 📜 6. Example Sequence

1. MCU initializes SDIO + DMA
2. FATFS mounts SD card
3. File is opened or created
4. Data is written
5. File is closed (forces flush)
6. Data can be read back

---


## ⚠️ 7. Common Errors & Fixes

### FR_NOT_READY
- 🕑 SDIO clock too fast → lower ClockDiv
- 🔌 No pull-ups on SD lines
- 💽 SD card not FAT32
- ⏱️ Mounting before RTOS scheduler

### Empty File
- ❌ Missing `f_close()`
- ❌ File opened with `FA_CREATE_ALWAYS` in loop
- ❌ Task stack too small
- ❌ No delay after mount

---

## 🔍 8. Debug Tips

- ✅ Check return values of `f_mount`, `f_open`, `f_write`
- ✅ Verify `bytesWritten > 0`
- ✅ Start with 1-bit SDIO, then switch to 4-bit
- ✅ Use logic analyzer on CMD/CLK lines if needed

---

## 💡 9. Tested Configuration

- STM32F407VG
- SDIO 1-bit → 4-bit
- FATFS + FreeRTOS
- ClockDiv = 8
- FAT32 SD card (8 GB)

---

## 📚 10. References

- STM32 HAL SDIO documentation
- FATFS official documentation
- [ControllersTech SDIO tutorials](https://controllerstech.com/interface-sd-card-with-sdio-in-stm32/)

Prepared for STM32 SDIO + FATFS projects using STM32CubeIDE.


