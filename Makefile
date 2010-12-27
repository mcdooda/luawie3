LUAWIE_LIBS = -llua5.1 -lXtst -lpthread
LUAWIE_SRC_DIR = src/
LUAWIE_OBJ_DIR = objs/
LUAWIE_OBJECTS = newlib.o main.o signals.o wiimote.o nunchuk.o classic.o guitar.o mouse.o keyboard.o screen.o devices.o lua.o primitives.o luawie.o pollmode.o runscript.o
LUAWIE_OBJECTS := $(addprefix $(LUAWIE_OBJ_DIR), $(LUAWIE_OBJECTS))

WIIUSE_LIBS = -lbluetooth
WIIUSE_SRC_DIR = src/wiiuse_v0.12/src/
WIIUSE_OBJ_DIR = objs/wiiuse/
WIIUSE_OBJECTS = classic.o dynamics.o events.o guitar_hero_3.o io.o io_nix.o io_win.o ir.o nunchuk.o wiiuse.o
WIIUSE_OBJECTS := $(addprefix $(WIIUSE_OBJ_DIR), $(WIIUSE_OBJECTS))

all: mkdir wiiuse luawie
	gcc $(WIIUSE_LIBS) $(LUAWIE_LIBS) $(WIIUSE_OBJECTS) $(LUAWIE_OBJECTS) -o luawie3

mkdir:
	-mkdir $(LUAWIE_OBJ_DIR) $(WIIUSE_OBJ_DIR)
	
wiiuse: $(WIIUSE_OBJECTS)

luawie: $(LUAWIE_OBJECTS)

$(WIIUSE_OBJ_DIR)%.o: $(WIIUSE_SRC_DIR)%.c
	gcc -c $(WIIUSE_LIBS) $< -o $@

$(LUAWIE_OBJ_DIR)%.o: $(LUAWIE_SRC_DIR)%.c
	gcc -c -g $(LUAWIE_LIBS) -Wall $< -o $@

clean:
	-rm luawie3
	-rm -r $(LUAWIE_OBJ_DIR)

