local set_state = Keyboard.set_state
local key_states = {}

function Keyboard.press(key)
	if not key_states[key] then
		key_states[key] = true
		set_state(key, true)
	end
end

function Keyboard.release(key)
	if key_states[key] then
		key_states[key] = nil
		set_state(key, false)
	end
end
