local Wiimote = Wiimote
local Nunchuk = Nunchuk
local NC = NC
local pressed = Nunchuk.button.pressed
local accel = Nunchuk.accel
local joystick = Nunchuk.joystick

function Nunchuk.debug()
	Wiimote.accel.enable()
	
	-- buttons
	for button, code in pairs(NC) do
		print(button, pressed(code) and '[pressed]' or '('..code..')')
	end
	
	-- accel
	print('orient', accel.orient())
	print('gforce', accel.gforce())
	print('accel',  accel.accel())
	
	-- joystick
	print('joystick', joystick.cartesian())
end
