local Wiimote = Wiimote
local WM = WM
local pressed = Wiimote.button.pressed
local accel = Wiimote.accel
local ir = Wiimote.ir

function Wiimote.debug()
	accel.enable()
	ir.enable()
	
	-- buttons
	for button, code in pairs(WM) do
		print(button, pressed(code) and '[pressed]' or '('..code..')')
	end
	
	-- accel
	print('orient', accel.orient())
	print('gforce', accel.gforce())
	print('accel',  accel.accel())
	
	-- ir
	for i = 1, 4 do
		print('dot #'..i, ir.dot(i))
	end
end

