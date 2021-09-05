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
#[repr(C, align(%ALIGNstd::vector<std::string>%))]
#[derive(Clone)]
pub struct std__vector_std__string__t {
    _inner: [u8; %SIZEstd::vector<std::string>%]
}

impl Default for std__vector_std__string__t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEstd::vector<std::string>%] }
    }
}
