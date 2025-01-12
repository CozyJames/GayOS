#ifndef KBD_H
#define KBD_H

#include "stdio.h"
#include "tty.h"
#include "io.h"

#define KBD_DATA_PORT 0x60   // порт для данных клавиатуры
#define KBD_STATUS_PORT 0x64 // порт для статуса клавиатуры
#define KEYS_SIZE 95 // под вопросом

enum {
    KEYBOARD_PRESS_ESCAPE = 0x01,
    KEYBOARD_PRESS_1 = 0x02,
    KEYBOARD_PRESS_2 = 0x03,
    KEYBOARD_PRESS_3 = 0x04,
    KEYBOARD_PRESS_4 = 0x05,
    KEYBOARD_PRESS_5 = 0x06,
    KEYBOARD_PRESS_6 = 0x07,
    KEYBOARD_PRESS_7 = 0x08,
    KEYBOARD_PRESS_8 = 0x09,
    KEYBOARD_PRESS_9 = 0x0A,
    KEYBOARD_PRESS_0 = 0x0B,
    KEYBOARD_PRESS_DASH = 0x0C, /* '-' */
    KEYBOARD_PRESS_EQUALS = 0x0D, /* '=' */
    KEYBOARD_PRESS_BACKSPACE = 0x0E,
    KEYBOARD_PRESS_TAB = 0x0F,
    KEYBOARD_PRESS_Q = 0x10,
    KEYBOARD_PRESS_W = 0x11,
    KEYBOARD_PRESS_E = 0x12,
    KEYBOARD_PRESS_R = 0x13,
    KEYBOARD_PRESS_T = 0x14,
    KEYBOARD_PRESS_Y = 0x15,
    KEYBOARD_PRESS_U = 0x16,
    KEYBOARD_PRESS_I = 0x17,
    KEYBOARD_PRESS_O = 0x18,
    KEYBOARD_PRESS_P = 0x19,
    KEYBOARD_PRESS_SQUARE_BRACKET_LEFT = 0x1A, /* ' [ ' */
    KEYBOARD_PRESS_SQUARE_BRACKET_RIGHT = 0x1B, /* ' ] ' */
    KEYBOARD_PRESS_ENTER = 0x1C,
    KEYBOARD_PRESS_LEFT_CONTROL = 0x1D,
    KEYBOARD_PRESS_A = 0x1E,
    KEYBOARD_PRESS_S = 0x1F,
    KEYBOARD_PRESS_D = 0x20,
    KEYBOARD_PRESS_F = 0x21,
    KEYBOARD_PRESS_G = 0x22,
    KEYBOARD_PRESS_H = 0x23,
    KEYBOARD_PRESS_J = 0x24,
    KEYBOARD_PRESS_K = 0x25,
    KEYBOARD_PRESS_L = 0x26,
    KEYBOARD_PRESS_SEMICOLON = 0x27, /* ' ; ' */
    KEYBOARD_PRESS_SINGLE_QUOTE = 0x28, /* ' ' ' */
    KEYBOARD_PRESS_BACKTICK = 0x29, /* ' ` ' */
    KEYBOARD_PRESS_LEFT_SHIFT = 0x2A,
    KEYBOARD_PRESS_BACKSLASH = 0x2B, /* '\' */
    KEYBOARD_PRESS_Z = 0x2C,
    KEYBOARD_PRESS_X = 0x2D,
    KEYBOARD_PRESS_C = 0x2E,
    KEYBOARD_PRESS_V = 0x2F,
    KEYBOARD_PRESS_B = 0x30,
    KEYBOARD_PRESS_N = 0x31,
    KEYBOARD_PRESS_M = 0x32,
    KEYBOARD_PRESS_COMMA = 0x33, /* ' , ' */
    KEYBOARD_PRESS_PERIOD = 0x34, /* ' . ' */
    KEYBOARD_PRESS_NUM_SLASH = 0x35, /* ' / ' */
    KEYBOARD_PRESS_RIGHT_SHIFT = 0x36,
    KEYBOARD_PRESS_NUM_ASTERISK = 0x37, /* ' * ' */
    KEYBOARD_PRESS_LEFT_ALT = 0x38,
    KEYBOARD_PRESS_SPACE = 0x39,
    KEYBOARD_PRESS_CAPSLOCK = 0x3A,
    KEYBOARD_PRESS_F1 = 0x3B,
    KEYBOARD_PRESS_F2 = 0x3C,
    KEYBOARD_PRESS_F3 = 0x3D,
    KEYBOARD_PRESS_F4 = 0x3E,
    KEYBOARD_PRESS_F5 = 0x3F,
    KEYBOARD_PRESS_F6 = 0x40,
    KEYBOARD_PRESS_F7 = 0x41,
    KEYBOARD_PRESS_F8 = 0x42,
    KEYBOARD_PRESS_F9 = 0x43,
    KEYBOARD_PRESS_F10 = 0x44,
    KEYBOARD_PRESS_NUMBER_LOCK = 0x45,
    KEYBOARD_PRESS_SCROLL_LOCK = 0x46,
    KEYBOARD_PRESS_NUM_7 = 0x47,
    KEYBOARD_PRESS_HOME = 0x47,
    KEYBOARD_PRESS_NUM_8 = 0x48,
    KEYBOARD_PRESS_ARROW_UP = 0x48,
    KEYBOARD_PRESS_NUM_9 = 0x49,
    KEYBOARD_PRESS_PG_UP = 0x49,
    KEYBOARD_PRESS_NUM_DASH = 0x4A, /* ' - ' */
    KEYBOARD_PRESS_NUM_4 = 0x4B,
    KEYBOARD_PRESS_ARROW_LEFT = 0x4B,
    KEYBOARD_PRESS_NUM_5 = 0x4C,
    KEYBOARD_PRESS_NUM_6 = 0x4D,
    KEYBOARD_PRESS_ARROW_RIGHT = 0x4D,
    KEYBOARD_PRESS_NUM_PLUS = 0x4E, /* ' + ' */
    KEYBOARD_PRESS_NUM_1 = 0x4F,
    KEYBOARD_PRESS_END = 0x4F,
    KEYBOARD_PRESS_NUM_2 = 0x50,
    KEYBOARD_PRESS_ARROW_DOWN = 0x50,
    KEYBOARD_PRESS_NUM_3 = 0x51,
    KEYBOARD_PRESS_PG_DOWN = 0x51,
    KEYBOARD_PRESS_NUM_0 = 0x52,
    KEYBOARD_PRESS_INSERT = 0x52,
    KEYBOARD_PRESS_NUM_PERIOD = 0x53, /* ' . ' */
    KEYBOARD_PRESS_DELETE = 0x53,
    KEYBOARD_PRESS_F11 = 0x57,
    KEYBOARD_PRESS_F12 = 0x58
};

char key_reader(uint8_t key) {
	switch(key) {
		case (uint8_t)KEYBOARD_PRESS_ESCAPE: return false;
		case (uint8_t)KEYBOARD_PRESS_1: return('1');
		case (uint8_t)KEYBOARD_PRESS_2: return('2');
		case (uint8_t)KEYBOARD_PRESS_3: return('3');
		case (uint8_t)KEYBOARD_PRESS_4: return('4');
		case (uint8_t)KEYBOARD_PRESS_5: return('5');
		case (uint8_t)KEYBOARD_PRESS_6: return('6');
		case (uint8_t)KEYBOARD_PRESS_7: return('7');
		case (uint8_t)KEYBOARD_PRESS_8: return('8');
		case (uint8_t)KEYBOARD_PRESS_9: return('9');
		case (uint8_t)KEYBOARD_PRESS_0: return('0');
		case (uint8_t)KEYBOARD_PRESS_DASH: return('-');
		case (uint8_t)KEYBOARD_PRESS_EQUALS: return('=');
        case (uint8_t)KEYBOARD_PRESS_BACKSPACE: (terminal_column == 0) ? remove_char(terminal_column, terminal_row) : remove_char(--terminal_column, terminal_row); return 0;
        case (uint8_t)KEYBOARD_PRESS_TAB: break; // хз
        case (uint8_t)KEYBOARD_PRESS_Q: return('q');
        case (uint8_t)KEYBOARD_PRESS_W: return('w');
        case (uint8_t)KEYBOARD_PRESS_E: return('e');
        case (uint8_t)KEYBOARD_PRESS_R: return('r');
        case (uint8_t)KEYBOARD_PRESS_T: return('t');
        case (uint8_t)KEYBOARD_PRESS_Y: return('y');
        case (uint8_t)KEYBOARD_PRESS_U: return('u');
        case (uint8_t)KEYBOARD_PRESS_I: return('i');
        case (uint8_t)KEYBOARD_PRESS_O: return('o');
        case (uint8_t)KEYBOARD_PRESS_P: return('p');
        case (uint8_t)KEYBOARD_PRESS_SQUARE_BRACKET_LEFT: return('[');
        case (uint8_t)KEYBOARD_PRESS_SQUARE_BRACKET_RIGHT: return(']');
        case (uint8_t)KEYBOARD_PRESS_ENTER: return('\n');
        case (uint8_t)KEYBOARD_PRESS_LEFT_CONTROL: break; // хз
        case (uint8_t)KEYBOARD_PRESS_A: return('a');
        case (uint8_t)KEYBOARD_PRESS_S: return('s');
        case (uint8_t)KEYBOARD_PRESS_D: return('d');
        case (uint8_t)KEYBOARD_PRESS_F: return('f');
        case (uint8_t)KEYBOARD_PRESS_G: return('g');
        case (uint8_t)KEYBOARD_PRESS_H: return('h');
        case (uint8_t)KEYBOARD_PRESS_J: return('j');
        case (uint8_t)KEYBOARD_PRESS_K: return('k');
        case (uint8_t)KEYBOARD_PRESS_L: return('l');
        case (uint8_t)KEYBOARD_PRESS_SEMICOLON: return(';');
        case (uint8_t)KEYBOARD_PRESS_SINGLE_QUOTE: return('\'');
        case (uint8_t)KEYBOARD_PRESS_BACKTICK: return('`');
        case (uint8_t)KEYBOARD_PRESS_LEFT_SHIFT: break; // хз
        case (uint8_t)KEYBOARD_PRESS_BACKSLASH: return('\\');
        case (uint8_t)KEYBOARD_PRESS_Z: return('z');
        case (uint8_t)KEYBOARD_PRESS_X: return('x');
        case (uint8_t)KEYBOARD_PRESS_C: return('c');
        case (uint8_t)KEYBOARD_PRESS_V: return('v');
        case (uint8_t)KEYBOARD_PRESS_B: return('b');
        case (uint8_t)KEYBOARD_PRESS_N: return('n');
        case (uint8_t)KEYBOARD_PRESS_M: return('m');
        case (uint8_t)KEYBOARD_PRESS_COMMA: return(',');
        case (uint8_t)KEYBOARD_PRESS_PERIOD: return('.');
        case (uint8_t)KEYBOARD_PRESS_NUM_SLASH: return('/');
        case (uint8_t)KEYBOARD_PRESS_RIGHT_SHIFT: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUM_ASTERISK: return('*');
        case (uint8_t)KEYBOARD_PRESS_LEFT_ALT: break; // хз
        case (uint8_t)KEYBOARD_PRESS_SPACE: return(' ');
        case (uint8_t)KEYBOARD_PRESS_CAPSLOCK: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F1: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F2: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F3: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F4: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F5: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F6: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F7: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F8: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F9: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F10: break; // хз
        case (uint8_t)KEYBOARD_PRESS_F11: break; // хз
        case (uint16_t)KEYBOARD_PRESS_F12: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUMBER_LOCK: break; // хз
        case (uint8_t)KEYBOARD_PRESS_SCROLL_LOCK: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_HOME: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_ARROW_UP: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_PG_UP: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUM_DASH: return '-';
        //case (uint8_t)KEYBOARD_PRESS_ARROW_LEFT: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_ARROW_RIGHT: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUM_PLUS: return '+';
        //case (uint8_t)KEYBOARD_PRESS_END: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_ARROW_DOWN: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_PG_DOWN: break; // хз
        //case (uint8_t)KEYBOARD_PRESS_INSERT: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUM_PERIOD: return '.';
        // case (uint8_t)KEYBOARD_PRESS_DELETE: break; // хз
        case (uint8_t)KEYBOARD_PRESS_NUM_0: return '0';
        case (uint8_t)KEYBOARD_PRESS_NUM_1: return '1';
        case (uint8_t)KEYBOARD_PRESS_NUM_2: return '2';
        case (uint8_t)KEYBOARD_PRESS_NUM_3: return '3';
        case (uint8_t)KEYBOARD_PRESS_NUM_4: return '4';
        case (uint8_t)KEYBOARD_PRESS_NUM_5: return '5';
        case (uint8_t)KEYBOARD_PRESS_NUM_6: return '6';
        case (uint8_t)KEYBOARD_PRESS_NUM_7: return '7';
        case (uint8_t)KEYBOARD_PRESS_NUM_8: return '8';
        case (uint8_t)KEYBOARD_PRESS_NUM_9: return '9';
	}
}

// функция для чтения данных с клавиатурного порта
uint8_t read_kbd_data() {
    while ((inb(KBD_STATUS_PORT) & 0x01) == 0); // ожидание, пока не будет готово новое значение
    return inb(KBD_DATA_PORT); // чтение данных с порта
}

// обработчик прерывания для клавиатуры
void keyboard_interrupt_handler() {
    uint8_t scan_code = read_kbd_data(); // получаем скан-код

    if (scan_code < KEYS_SIZE) {
        char key = key_reader(scan_code);
        if (key != 0) {
            printf("%c", key);
        }
    }
}

#endif /* KBD_H */