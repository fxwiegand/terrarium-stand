# terrarium-stand
This repository works as a template for new pedals created for the [terrarium](https://www.pedalpcb.com/product/pcb351/) from [PedalPCB](https://www.pedalpcb.com).
To create a new pedal, simply create a new git repository using this template and start out with the basic structure in the `your_pedal` directory. Change the name of the directory to whatever you like but make sure you also change `TARGET = your_pedal` in `your_pedal/Makefile`.

## Getting started
Build the daisy libraries with:
```
cd DaisySP
make
cd ../libDaisy
make
```

Then flash your terrarium with:
```
cd your_pedal
# using USB (after entering bootloader mode)
make program-dfu
# using JTAG/SWD adaptor (like STLink)
make program
```

Note: The template pedal only turns the LED of the terrarium on and off and does no audio processing at all.