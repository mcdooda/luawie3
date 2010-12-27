local click = Mouse.button.click
local button_states = {}

function Mouse.press(button)
	if not button_states[button] then
		button_states[button] = true
		click(button, true)
	end
end

function Mouse.release(button)
	if button_states[button] then
		button_states[button] = nil
		click(button, false)
	end
end
