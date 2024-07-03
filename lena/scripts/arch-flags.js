
const os = require("os");

const arch = os.arch();

let answer = "";
switch (arch) {
    case 'x64':
        answer = "-m64 '-DLENA_BUILD_ARCH_STR=X(\"x64_86\")'";
        break;
    case 'ia32':
        answer = "-m32 '-DLENA_BUILD_ARCH_STR=X(\"x86\")'";
        break;
}

console.log(answer);
