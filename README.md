## Planned Features
* **Real-time Monitoring:** Displays Volts, Amps, and Battery Temp.
* **State of Charge:** Calculates Battery % based on energy in/out (Ah).
* **Solar Auto-Sync:** Automatically resets drift to 100% when battery hits full charge voltage.
* **Safety:** Includes temperature monitoring for battery health.
* **Low Power:** Uses a high-efficiency Buck Converter to power the logic.

## Component List So Far

| **Category**        | **Product Name**                             | **Cat No** | **Price**    | **Notes**                                               |
| ------------------- | -------------------------------------------- | ---------- | ------------ | ------------------------------------------------------- |
| **Microcontroller** | Duinotech Nano Board                         | **XC4414** | $45.95       | The "Brain". Comes with a Mini-USB cable.               |
| **Power**           | Mini DC-DC Step Down Converter Module        | **XC4514** | $10.25       | **Crucial.** Drops 12V to 5V to power the Nano safely.  |
| **Current**         | Arduino Compatible 30A Current Sensor Module | **XC4610** | $12.50       | Measures Amps. **Limit 30A.**                           |
| **Temp**            | Keyes Temperature Sensor Module              | **XC4653** | $9.95        | Waterproof probe for battery temp.                      |
| **Display**         | 0.96 Inch OLED Display Module 128x64         | **XC3728** | $19.95       | Small screen to show Volts/Amps/%.                      |
| **Breadboard**      | 170 Tie Point Mini Breadboard                | **PB8817** | $6.25        | Stick the Nano on this to wire it up without soldering. |
| **Wires**           | Socket to Plug Jumper Leads (40 Pack)        | **WC6028** | $11.25       | Wires to connect sensors to the breadboard.             |
| **Fuse Holder**     | Waterproof Blade Fuse Holder                 | **SZ2042** | $4.95        | **Mandatory** safety for the battery line.              |
| **Fuse**            | 30A Blade Fuse (Green)                       | **SF2128** | $1.00        | Put this inside the fuse holder.                        |
| **Box**             | Jiffy Box (130 x 68 x 44mm)                  | **HB6013** | $4.50        | A decent size box to fit the Nano and messy wires.      |
| **Resistor R1**     | 33k Ohm 0.5 Watt Metal Film Resistors (Pk 8) | **RR0608** | $0.85        | Part of Voltage Divider (Yellow-Orange-Black-Red band). |
| **Resistor R2**     | 10k Ohm 0.5 Watt Metal Film Resistors (Pk 8) | **RR0596** | $0.85        | Part of Voltage Divider (Brown-Black-Black-Red band).   |
| **Safety Diode**    | 5.1V 1 Watt Zener Diode                      | **ZR1403** | $0.65        | Protects Arduino Input A0 from voltage spikes.          |
| **Total**           |                                              |            | **~$128.00** |                                                         |
