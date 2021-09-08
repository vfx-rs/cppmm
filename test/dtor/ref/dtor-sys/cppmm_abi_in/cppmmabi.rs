#[repr(C, align(%ALIGNstd::__cxx11::basic_string<char>%))]
#[derive(Clone)]
pub struct std____cxx11__basic_string_char__t {
    _inner: [u8; %SIZEstd::__cxx11::basic_string<char>%]
}

impl Default for std____cxx11__basic_string_char__t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEstd::__cxx11::basic_string<char>%] }
    }
}
