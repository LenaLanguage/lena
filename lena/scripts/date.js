const now = new Date();
const buildTime = now.toISOString();

console.log("'-DLENA_BUILD_TIME_STR=X(\"" + buildTime + "\")'");