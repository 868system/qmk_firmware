SRC += muse.c

SRC += user_layers.c
SRC += user_rgb_functions.c
SRC += user_rgb_layers.c

# Overrides for rev3_drop/rules.mk
COMMAND_ENABLE = no
DIP_SWITCH_ENABLE = no
ENCODER_ENABLE = no
MOUSEKEY_ENABLE = no

# Feature overrides
EEPROM_DRIVER = transient
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no

# Link-time optimization
LTO_ENABLE = no

# Separate USB endpoints
KEYBOARD_SHARED_EP = no
MOUSE_SHARED_EP = no
NKRO_SHARED_EP = no
