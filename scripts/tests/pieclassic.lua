require 'scripts/tests/test' (
	function()
		for name, code in pairs(CC) do
			print('Classic.'..name..' = '..tostring(Classic[name]))
		end
		local jpos = {
			'UP',
			'UPRIGHT',
			'RIGHT',
			'DOWNRIGHT',
			'DOWN',
			'DOWNLEFT',
			'LEFT',
			'UPLEFT'
		}
		for k, pos in pairs(jpos) do
			print('Classic.left_joystick.'..pos..' = '..tostring(Classic.left_joystick[pos])..' / Classic.right_joystick.'..pos..' = '..tostring(Classic.right_joystick[pos]))
		end
	end
)
