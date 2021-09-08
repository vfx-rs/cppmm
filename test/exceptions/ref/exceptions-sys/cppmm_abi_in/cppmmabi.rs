#[repr(C, align(%ALIGNex::Struct%))]
#[derive(Clone)]
pub struct ex__Struct_t {
    _inner: [u8; %SIZEex::Struct%]
}

impl Default for ex__Struct_t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEex::Struct%] }
    }
}
