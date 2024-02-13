# Keywords list for Lena programming language ver 0.0.1

## Flow

* if
* else
* elif

* default
* as
* with

* try
* except

* while
* for
* loop

## Examples of use

``` lena
/* For Windows */
#ifdef _WIN32



#else /* LINUX */

#endif
; ...

if (a > 10) {

} elif (a > 0) {

} else if (a == 0) {

} else {

}

; ...

try (file("myfile.txt") >> string) {

} except (file::FILE_NOT_FOUND) {

}

; ...

loop {

}

while (a > 10) {
    a = my_magic_func()
}

for (i, 0..100) {

}

repeat 100 {
    
}

```
