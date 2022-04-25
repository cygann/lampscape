#include <lamp.h>
#include <Adafruit_NeoPixel.h>

Lamp::Lamp() {}

Lamp::Lamp(int pwr_pin, int ctrl_pin, int led_pin, int led_count) {
    Serial.println("init");
    this->pwr_pin = pwr_pin;
    this->ctrl_pin = ctrl_pin;
    this->led_pin = led_pin;
    this->led_count = led_count;
    this->strip = Adafruit_NeoPixel(led_count, led_pin, NEO_RGBW);
}

/* Must be called in setup(), after lamp object is initialized.
 * */
void Lamp::lamp_begin() {
    strip.begin();
    strip.show();
    strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255
    turn_off(1);

    on = false;
    timer = millis();
    active_prof = 0;
}

void Lamp::loop_turn() {
    // Read from power button
    on = is_pwr_pressed();

    if (on_prev && !on) turn_off(); // Turn off the lamp
    else if (!on_prev && on) { // Turn on the lamp for the first time
        profile_on(active_prof);
    }

    // Read from mode button
    bool change_prof = is_ctrl_pressed();
    if (change_prof && on) { // Only change profile when powered on
        active_prof = (active_prof + 1) % N_PROFILES;
        profile_on(active_prof);
    }

    do_tick(active_prof);

    // Serial.println("Is on  : " + String(on));
    // Serial.println("Is ctrl: " + String(change_prof));
    // Serial.println("Profile: " + String(active_prof));
    Serial.println("On prev: " + String(on_prev));

    on_prev = on;
}

void Lamp::profile_on(uint32_t prof) {

    switch(prof) {
        case 0: // Red
            color_wipe(strip.Color(20,   200,   20, 255), 20);
            return;
        case 1: // Rainbow init
            // color_wipe(strip.Color(0,   255,   0, 255), 20);
            turn_off();
            return;
        case 2: //
            color_wipe(strip.Color(180,   252,   70, 255), 20);
            return;
        case 3: //
            color_wipe(strip.Color(0,   100,   0, 255), 20);
            return;
        case 4: //
            // TODO: make smooth
            strip.setBrightness(10);
            color_wipe(strip.Color(0,   200,   0, 100), 20);
            return;
        case 5: //
            color_wipe(strip.Color(0,   200,   255, 255), 20);
            return;
        case 6: //
            color_wipe(strip.Color(0,   0,   250, 255), 20);
            return;
        case 7:
            last_color = 0;
            return;
        default:
            color_wipe(strip.Color(20,   200,   20, 255), 20);
    }
}

void Lamp::do_tick(uint32_t prof) {
    switch(prof) {
        case 1:
            if (millis() - timer < 20) break;
            rainbow(20);
            timer = millis();
        default: return; // Static color profiles
    }
}

bool Lamp::is_pwr_pressed() {
    int read = digitalRead(pwr_pin);
    if (read == HIGH) {
        delay(DEBOUN_DUR);
        read = digitalRead(pwr_pin);

        if (read == HIGH) return true;

    }
    return false;
}

bool Lamp::is_ctrl_pressed() {
    int read = digitalRead(ctrl_pin);
    if (read == HIGH) {
        delay(DEBOUN_DUR);
        read = digitalRead(ctrl_pin);

        if (read == HIGH) return true;
    }
    return false;
}

void Lamp::turn_off(int wait=5) {
  for(int i = strip.numPixels(); i >= 0; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
    strip.show();
    delay(wait);
  }
}

void Lamp::color_wipe(uint32_t color, int wait) {
  for(int i = strip.numPixels(); i >= 0; i--) {
  // for(int i = 0; i <= strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void Lamp::rainbow(int wait) {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    // for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {

    for(int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = last_color + (i * 65536L / strip.numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
    last_color = last_color + 256;
    if (last_color > 5 * 65536) last_color = 0;
}
