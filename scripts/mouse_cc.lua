local x, y = Classic.left_joystick.cartesian()
local speed = 5
Mouse.cursor.move(x * speed, y * speed)
Mouse.LEFT  = Classic.A
Mouse.RIGHT = Classic.B
Mouse.WHEELUP   = Classic.right_joystick.UP
Mouse.WHEELDOWN = Classic.right_joystick.DOWN
