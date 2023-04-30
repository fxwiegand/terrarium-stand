#include "daisy_petal.h"
#include "daisysp.h"
#include "terrarium.h"

using namespace daisy;
using namespace daisysp;
using namespace terrarium;

// Declare a global daisy_petal for hardware access
DaisyPetal  hw;

bool        bypass, switch1;
Led         led1, led2;
Parameter   knob1;
// ReverbSc    verb;

/*
 * Process terrarium knobs and switches
 */
void processTerrariumControls() {
  // update switch values
  // https://electro-smith.github.io/libDaisy/classdaisy_1_1_switch.html
  if(hw.switches[Terrarium::FOOTSWITCH_1].RisingEdge()) {
    bypass = !bypass;
  }

  switch1 = hw.switches[Terrarium::SWITCH_1].Pressed();

  // update knob values
  // https://electro-smith.github.io/libDaisy/classdaisy_1_1_analog_control.html
  knob1.Process();

  led1.Set(bypass ? 0.0f : 1.0f);
}

/*
 * This runs at a fixed rate, to prepare audio samples
 */
void callback(
    AudioHandle::InterleavingInputBuffer  in,
    AudioHandle::InterleavingOutputBuffer out,
    size_t                                size
    )
{
    hw.ProcessAllControls();
    processTerrariumControls();
    led1.Update();
    led2.Update();

    for(size_t i = 0; i < size; i += 2)
    {
        // Process your signal here
        if(bypass)
        {
            out[i] = in[i];
        }
        else
        {
            // processed signal
            // Using knob1 as volume here
            out[i] = in[i] * knob1.Value();
        }
    }
}

int main(void)
{
    // float samplerate;

    hw.Init();
    // samplerate = hw.AudioSampleRate();

    led1.Init(hw.seed.GetPin(Terrarium::LED_1), false);
    led2.Init(hw.seed.GetPin(Terrarium::LED_2), false);

    // Initialize your knobs here like so:
    // https://electro-smith.github.io/libDaisy/classdaisy_1_1_parameter.html
    knob1.Init(hw.knob[Terrarium::KNOB_1], 0.0f, 0.999f, Parameter::LINEAR);

    // Set samplerate for your processing like so:
    // verb.Init(samplerate);

    bypass = true;

    hw.StartAdc();
    hw.StartAudio(callback);

    while(1)
    {
        // Do lower priority stuff infinitely here
        System::Delay(10);
    }
}
