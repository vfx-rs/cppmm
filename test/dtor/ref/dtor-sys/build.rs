
fn main() {
    let dst = cmake::Config::new("/home/anders/code/cppmm/build/test/dtor/output/dtor-sys/dtor-c").build();
    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=dylib=dtor-c-0_1");

    let out_dir = std::env::var("OUT_DIR").unwrap();
    let output = std::process::Command::new("python")
        .args(&["dtor-c/abigen/insert_abi.py", 
            "cppmm_abi_in", 
            &format!("{}/cppmm_abi_out", out_dir), 
            &format!("{}/build/abigen.txt", out_dir)])
        .output().expect("couldn't do the thing");

    if !output.status.success() {
        for line in std::str::from_utf8(&output.stderr).unwrap().lines() {
            println!("cargo:warning={}", line);
        }
        panic!("failed");
    }




    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}
    