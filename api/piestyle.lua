do
	-- wiimote and expansions
	
	local devices = {
		[Wiimote] = WM,
		[Nunchuk] = NC,
		[Classic] = CC,
		[Guitar]  = GH
	}

	for dev, buttons in pairs(devices) do
		setmetatable(dev, {
			__index = function(d, button)
				return d.button.pressed(buttons[button])
			end,

			__newindex = function(d, button, func)
				if d.button.pressed(buttons[button]) then
					func()
				end
			end
		})
	end
end

do
	-- joysticks
	
	local joysticks = {
		Nunchuk.joystick,
		Classic.left_joystick,
		Classic.right_joystick,
		Guitar.joystick
	}
	
	local function in_position(joystick, min_magnitude, min_angle, max_angle)
		local magnitude, angle = joystick()
		return magnitude >= min_magnitude and (
			(min_angle <= max_angle and angle >= min_angle and angle <= max_angle)
			or (max_angle < min_angle and (angle >= min_angle or angle <= max_angle))
		)
	end
	
	local positions = {
		UP        = {315, 45 },
		UPRIGHT   = {45,  45 },
		RIGHT     = {45,  135},
		DOWNRIGHT = {135, 135},
		DOWN      = {135, 225},
		DOWNLEFT  = {225, 255},
		LEFT      = {225, 315},
		UPLEFT    = {315, 315}
	}
	
	local mt = {
	
		__index = function(j, position)
			local p = positions[position]
			local threshold = 22.5
			return p and in_position(j.polar, 0.3, p[1] - threshold, p[2] + threshold)
		end,
		
		__newindex = function(j, position, func)
			local p = positions[position]
			local threshold = 22.5
			if p and in_position(j.polar, 0.3, p[1] - threshold, p[2] + threshold) then
				func()
			end
		end
	}
	
	for k, joystick in pairs(joysticks) do
		setmetatable(joystick, mt)
	end
	
end

do
	-- keyboard
	
	local press = Keyboard.press
	local release = Keyboard.release

	setmetatable(Keyboard, {
	
		__newindex = function(kb, key, state)
			if state then
				press(key)
			else
				release(key)
			end
		end
	
	})
end

do
	-- mouse

	local press = Mouse.press
	local release = Mouse.release
	local MS = MS

	setmetatable(Mouse, {
	
		__newindex = function(ms, button, state)
			if state then
				press(MS[button])
			else
				release(MS[button])
			end
		end
	
	})
end
