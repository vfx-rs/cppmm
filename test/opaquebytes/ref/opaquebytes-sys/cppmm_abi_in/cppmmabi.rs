#[repr(C, align(%ALIGNobyte::Foo%))]
#[derive(Clone)]
pub struct obyte__Foo_t {
    _inner: [u8; %SIZEobyte::Foo%]
}

impl Default for obyte__Foo_t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEobyte::Foo%] }
    }
}
