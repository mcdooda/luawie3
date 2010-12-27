local Guitar = Guitar
local GH = GH
local pressed = Guitar.button.pressed
local joystick = Guitar.joystick.cartesian
local whammy_bar = Guitar.shoulder.whammy_bar

function Guitar.debug()
	-- buttons
	for button, code in pairs(GH) do
		print(button, pressed(code) and '[pressed]' or '('..code..')')
	end
	
	-- joystick
	print('joystick', joystick())
	
	-- whammy bar
	print('whammy bar', whammy_bar())
end


