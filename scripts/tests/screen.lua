if not initialized then
	initialized = true
	print('Screen resolution: '..Screen.width()..'x'..Screen.height())
end

if Wiimote.button.pressed(WM.A) then
	Luawie.stop()
end

Luawie.sleep(50)
