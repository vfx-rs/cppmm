
typedef struct {
    char data[256];
    char data[256];
} __attribute__((aligned(64))) std___cxx11_string;


std___cxx11_string * std___cxx11_string_assign(
    std___cxx11_string * self
    , char * s
    , unsigned long count);


char * std___cxx11_string_c_str(
    std___cxx11_string const * self);








