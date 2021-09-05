#[repr(C, align(%ALIGNstd::set<std::string>%))]
#[derive(Clone)]
pub struct std__set_std__string__t {
    _inner: [u8; %SIZEstd::set<std::string>%]
}

impl Default for std__set_std__string__t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEstd::set<std::string>%] }
    }
}
#[repr(C, align(%ALIGNstd::string%))]
#[derive(Clone)]
pub struct std__string_t {
    _inner: [u8; %SIZEstd::string%]
}

impl Default for std__string_t {
    fn default() -> Self {
        Self { _inner: [0u8; %SIZEstd::string%] }
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
