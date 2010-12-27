if not initialized then
	initialized = true
	Wiimote1.led.on(1)
	Wiimote2.led.on(2)
end

Keyboard.Up    = Wiimote1.RIGHT
Keyboard.Left  = Wiimote1.UP
Keyboard.Down  = Wiimote1.LEFT
Keyboard.Right = Wiimote1.DOWN

Keyboard.Z = Wiimote1.TWO
Keyboard.A = Wiimote1.ONE
Keyboard.D = Wiimote1.B

Keyboard.Return  = Wiimote1.PLUS
Keyboard.Shift_R = Wiimote1.MINUS


