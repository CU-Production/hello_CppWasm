use wasm_bindgen::prelude::wasm_bindgen;

extern "C" {
    fn sum(a: i32, b: i32) -> i32;
}

static mut COUNTER: i32 = 0;

#[wasm_bindgen]
pub unsafe extern "C" fn test(arg1: i32, arg2: i32) -> i32 {
    let x = arg1 + arg2;
    let y = arg1 - arg2;
    return sum(x, y) / 2;
}

#[wasm_bindgen]
pub unsafe fn test_counter_get() -> i32 {
    return COUNTER;
}

#[wasm_bindgen]
pub unsafe fn test_counter_inc() {
    COUNTER += 1;
}

#[wasm_bindgen]
pub unsafe fn test_counter_add(inc_value: i32) {
    COUNTER += inc_value;
}

#[wasm_bindgen]
pub fn test_add(a: i32, b: i32) -> i32 {
    return a + b;
}

#[wasm_bindgen]
pub fn test_mul(a: i32, b: i32) -> i32 {
    return a * b;
}
