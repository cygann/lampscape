# lampscape 🔆
<p align="center">
  <img src="https://github.com/cygann/lampscape/blob/main/assets/lampscape_mtm.png?raw=true" alt="Picture of lamp"/>
</p>
Lampscape is a sandcasted and 3D printed lamp with fully programmable RGBW LEDs. I created this during winter quarter 2022 as my final project for Stanford's ME 203: Design and Manufacturing class.

---

### Code
This repository is primarily for the code running on the lamp's [Arduino Metro Mini](https://www.adafruit.com/product/2590). Instructions for use:
1. Install platformio with `pip install -U platformio`. Alternate install options [here](https://docs.platformio.org/en/latest/core/installation.html).
2. Clone the repository, navigate inside, and run `pio run`, which compiles the code.
3. Upload to device with `pio run -t upload`

### Electronics
Lampscape uses an [Arduino Metro Mini](https://www.adafruit.com/product/2590) as a mircocontroller. The lighting used is [an RGBW LED strip from Adafruit](https://www.adafruit.com/product/4913). I strongly recommend warm white LEDs only as they make for much more pleasant lighting.
For lighting control, I used two [metal pushbuttons](https://www.adafruit.com/product/558) from adafruit, one latching (power on/off) and one momentary (for changing color profiles). 

### CAD Files & 3D Printing
I used fuison 360 to create both the base and lampshade. The files can be found here:
- [Base](https://a360.co/3EMOnpk)
- [Lampshade](https://a360.co/3MrfjNY)

The lampshade was 3D printed using [Form Lab's](https://formlabs.com) white resin. The lamp shade thickness is 0.05 inches with the wave grooves being about 50% thicker.

The base was printed with standard PLA filament. I then heavily sanded it, applied Bondo & sanded it again (for smoothness), and then applied a thin layer of Shellac before using it as a sandcasting pattern.
