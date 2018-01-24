# Bitcoin Rollercoaster Guy

This is the complete set of assets/sources to make your own Bitcoin Rollercoaster Guy desk toy. It is based on the awesome 3D model by rgremill (https://www.thingiverse.com/thing:2523635). I addded a stand, servo and some electronics to make it read current BTC price and position the cart accordingly.

Please follow the guidelines below to build and setup the toy. Have fun on the Bitcoin rollercoaster!

Any donations to this address will be much appreciated: 1LAJ6Aa1gvv5B4MRmAoizPNHKHsTvC9iGt

## Parts

1. 1x D1 Mini NodeMCU ESP8266 ESP-12 module (I got one from eBay, and I believe it's a clone of https://wiki.wemos.cc/products:d1:d1_mini)
2. DIYmall 0.96" Yellow& Blue 128X64 OLED display (http://www.diymalls.com/OLED/0.96-blue-and-yellow-oled-display)
3. SG90 9g servo (TP-SG90)
4. Some small screws
5. Access to 3D printer or 3D printing service

## How to print

Download .stl files from the models folder. Most of the cart parts a printed as they are in rgremill's project (so technically you can download from there). Only the wheel platform is modified to accept the servo. Note you may need to print with supports and/or post process the part.
The top of the base is best printed upside down and it should not require supports.

Once printed, you may want to test that the halves of the horizontal bar between the stands can more or less easily be connected together. You may need file one of them a bit. Also try plugging the stands into the base and see if they fit. Some filing may be needed here too.

For the parts that I designed, I provided Autodesk Fusion 360 (free) source files. Feel free to modify them if you need to adjust for the actual hardware you have.

## Electronics

I'm gonna have to come back and maybe add a diagram, but here are the connections than need to be made on the MCU/screen/servo

ESP8266 D1 -> OLED SCL
ESP8266 D2 -> OLED SDA
ESP8266 3.3v -> OLED VCC
ESP8266 GND -> OLED GND

ESP8266 5v -> Servo +
ESP8266 GND -> Servo GND
ESP8266 D7 -> Servo Signal

## Software

The MCU we're working with is very nice in that it has onboard USB, so you can reprogram it later without disassembling the base. Just follow https://wiki.wemos.cc/tutorials:get_started:get_started_in_arduino#using_boards_manager to set up your Arduino environment with NodeMCU and then load the code from the src folder. 

The code is using some libraries you can download from their respective websites, or from the included archive.

More details TBD

## How to assemble

The assembly should be pretty straightforward if a bit awkward. The trickiest part is probably routing the cable from servo into the base.

This is the method I found to be the easiest. It's better to install the servo into the platform first. One of the stands has a channel inside it. You will have to cut off the connector from the servo, make sure you cut close to the connector, so you have enough length. Now route the cable through the "ring" in the platform (going from inside out). Tie a piece of fishing line to the wire and route it through the channel in the stand (from top end to bottom). By carefully pulling on the fishing line, route the wire through the stand's channel.

The other stand has the slot for servo's arm. You can either glue the arm inside the slot or use some heated thin wire to pin it down. You can also just put it there as is, you'll use a screw to tie it down later. This however may result in a bit of play.

Before fully assembling the top part, you'll need to solder the servo wire onto the board (see if you want to route the cable into the base at this step, or you're ok resoldering it later), and (with all code loaded) turn the ESP8266 on. The first instruction in the script is to "zero" the platform. This will move the servo into intial position, you can turn the board off now. 

Now some coordinated actions will be needed. Hold the platform level and the non-hollow stand vertically. Plug servo's shaft into the arm's socket. Don't worry about being a couple degrees off. Now put in a screw and tighten. Don't let go of the assembly. Take the other stand and plug its horizontal into its counterpart on the first stand. You may also need to pull on the wire to remove any slack to let the top "bearing" on the stand to get into the "ring" on the platform. If your wire is not routed into the base yet, do it now. You can now plug the stands into the base. You can glue them in with acetone if your parts are from ABS. alternatively, use some plastic-friendly glue.

The OLED panel should fit behind its window, and you'll need something to lock its bottom part there. I used pieces of filament that I melted with soldering iron.

The bottom of the base should snap into place and you can secure it with a screw in the middle.

I would recommend attaching the card only after these steps and after confirming that the toy works as expected. Simply glue it on top of the platform. Note: the axis of the servo is not perfectly in the middle of the platform. Make sure Bitcoin Guy sits on the short side of the platform, this helps with balance.




