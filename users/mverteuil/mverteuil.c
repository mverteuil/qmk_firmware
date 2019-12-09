#include "mverteuil.h"

void register_left_brace() {
  register_code(KC_LSHIFT);
  register_code(KC_LBRACKET);
}

void register_left_paren() {
  register_code(KC_LSHIFT);
  register_code(KC_9);
}

void register_right_brace() {
  register_code(KC_LSHIFT);
  register_code(KC_RBRACKET);
}

void register_right_paren() {
  register_code(KC_LSHIFT);
  register_code(KC_0);
}

void unregister_left_brace() {
   unregister_code(KC_LBRACKET);
   unregister_code(KC_LSHIFT);
}

void unregister_left_paren() {
   unregister_code(KC_9);
   unregister_code(KC_LSHIFT);
}

void unregister_right_brace() {
   unregister_code(KC_RBRACKET);
   unregister_code(KC_LSHIFT);
}

void unregister_right_paren() {
   unregister_code(KC_0);
   unregister_code(KC_LSHIFT);
}
