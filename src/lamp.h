#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int DEBOUN_DUR = 20;
const int N_PROFILES = 10;

class Lamp {
    public:
        Lamp();
        Lamp(int pwr_pin, int ctrl_pin, int led_pin, int led_count);
        void loop_turn();
        bool is_pwr_pressed();
        bool is_ctrl_pressed();
        void lamp_begin();

    private:
        /* State Variables */
        bool on;
        bool on_prev;
        uint32_t active_prof;
        unsigned long timer; // Used by lighting profiles
        unsigned long last_color;

        /* Internal device variables */
        int pwr_pin;
        int ctrl_pin;
        int led_pin;
        int led_count;
        Adafruit_NeoPixel strip;

        /* Private Functions */
        void turn_off(int wait=5);
        void color_wipe(uint32_t color, int wait);
        void profile_on(uint32_t prof);
        void do_tick(uint32_t prof);

        /* Profile-specific functions */
        void rainbow(int wait);

};
