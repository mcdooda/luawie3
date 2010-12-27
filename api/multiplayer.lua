local devices = {'Wiimote', 'Nunchuk'}
local select = Wiimote.select

for k, device in pairs(devices) do

	local devs = {}
	_G[device..'s'] = devs
	
	for i = 1, Luawie.num_devices() do
		local d = _G[device]
		
		local dev = {}
		_G[device..i] = dev
		
		devs[i] = dev
	
		setmetatable(dev, {
		
			__index = function(dev0, k)
				select(i)
				return d[k]
			end,
			
			__newindex = function(dev0, k, v)
				d[k] = v
			end,
			
			__call = function()
				select(i)
			end
		
		})
	end
end
