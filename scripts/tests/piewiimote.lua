require 'scripts/tests/test' (
	function()
		for name, code in pairs(WM) do
			print('Wiimote.'..name..' = '..tostring(Wiimote[name]))
		end
	end
)
