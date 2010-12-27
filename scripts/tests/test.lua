return function (f)
	Luawie.clear()
	if Wiimote.button.pressed(WM.A, WM.B) then
		Luawie.stop()
	end
	f()
	Luawie.sleep(5)
end
