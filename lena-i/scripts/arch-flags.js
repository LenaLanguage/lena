
const os = require("os");

const arch = os.arch();

let answer = "";
switch (arch) {
    case 'x64':
        answer = "-m64";
        break;
    case 'ia32':
        answer = "-m32";
        break;
}

console.log(answer);
