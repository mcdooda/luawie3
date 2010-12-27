local Classic = Classic
local CC = CC
local pressed = Classic.button.pressed
local left_joystick = Classic.left_joystick.cartesian
local right_joystick = Classic.right_joystick.cartesian
local left_shoulder = Classic.shoulder.left
local right_shoulder = Classic.shoulder.right

function Classic.debug()
	-- buttons
	for button, code in pairs(CC) do
		print(button, pressed(code) and '[pressed]' or '('..code..')')
	end
	
	-- joysticks
	print('left joystick', left_joystick())
	print('right joystick', right_joystick())
	
	-- shoulders
	print('left shoulder', left_shoulder())
	print('right shoulder', right_shoulder())
end

