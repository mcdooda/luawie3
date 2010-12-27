if not initialized then
	initialized = true
	Wiimote.led.on(1)
	Wiimote.accel.enable()
	print 'Press A to initialize your hand position'
else
	local x, y = Wiimote.accel.orient()
	if not hand then
		if Wiimote.A then
			hand = {
				x = x,
				y = y,
				speed = 1
			}
			Luawie.clear()
			print 'A: left click'
			print 'B: right click'
			print 'Home: quit'
			print 'Plus: move faster'
			print 'Minus: move slower'
		end
	else
		Mouse.cursor.move(hand.speed * (x - hand.x), hand.speed * (y - hand.y))
		Mouse.LEFT  = Wiimote.A
		Mouse.RIGHT = Wiimote.B
		Wiimote.PLUS = function()
			hand.speed = hand.speed + 1
			if hand.speed > 4 then
				hand.speed = 4
			end
			Wiimote.led.on(hand.speed)
		end
		Wiimote.MINUS = function()
			hand.speed = hand.speed - 1
			if hand.speed < 1 then
				hand.speed = 1
			end
			Wiimote.led.off(hand.speed + 1)
		end
	end
end
Luawie.sleep(10)
